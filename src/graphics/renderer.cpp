#include <graphics/renderer.hpp>

#include <core/transform.hpp>
#include <graphics/data.hpp>
#include <math/constants.hpp>
#include <math/matrix4.hpp>
#include <math/vector2.hpp>

#include <core/debug.hpp>
#include <graphics/gl.hpp>
#include <core/input.hpp>

#define MAX_INSTANCES 160000
#define MAX_MESHES 1024
#define MAX_MATERIALS 1024

namespace gl = Lux::Graphics::gl;

Lux::Graphics::Renderer::Renderer(Platform::Window& window, u8 num_buffers)
    : default_shader_("src/shaders/default.vert", "src/shaders/default.frag")
    , resource_manager(MAX_MESHES, MAX_MATERIALS)
    , render_table(MAX_MESHES)
    , window_(window)
    , current_buffer_(0)
    , instances_usage(0)
{
    LUX_VERIFY(num_buffers > 0 && num_buffers < 4, "invalid buffering number (min 1 : max 3)");

    num_buffers_ = num_buffers;

    default_shader_.use();
    default_shader_.set_uniform_matrix4f(Lux::Math::Matrix4::ortho(0,window.width_,window.height_,0,-1.0f,1.0f), "u_Projection");
    //default_shader_.set_uniform_matrix4f(Lux::Math::Matrix4::perspective(60, static_cast<f32>(window_.width_)/static_cast<f32>(window_.height_), 0.1, 1000), "u_Projection");

    // vertex locations/binding index configuration
    vao.bind();
    vao.set_location_format(0, VertexType::Float32, 3, 0);
    vao.set_location_binding(0, 0);

    vao.set_location_format(1, VertexType::Float32, 3, 3);
    vao.set_location_binding(1, 0);

    vao.set_location_format(2, VertexType::Float32, 2, 6);
    vao.set_location_binding(2, 0);

    // instancing locations/binding index configuration
    vao.set_location_format(3, VertexType::Float32, 4, 0);
    vao.set_location_format(4, VertexType::Float32, 4, 4);
    vao.set_location_format(5, VertexType::Float32, 4, 8);
    vao.set_location_format(6, VertexType::Float32, 4, 12);

    vao.set_location_binding(3, 1);
    vao.set_location_binding(4, 1);
    vao.set_location_binding(5, 1);
    vao.set_location_binding(6, 1);

    vao.set_binding_divisor(1, 1);

    vao.link_vbo(transform_vbo_, sizeof(Math::Matrix4), 1);

    //alloc shared gpu memory and add to an arena
    transform_instances_ptr_ = (Math::Matrix4*) transform_vbo_.alloc_shared_memory(MAX_INSTANCES * sizeof(Math::Matrix4) * num_buffers_);
    transform_arena_.use((u8*)transform_instances_ptr_, MAX_INSTANCES * sizeof(Math::Matrix4) * num_buffers_);
    
    setup_default_meshes();
}

Lux::Graphics::Renderer::~Renderer() = default;

void Lux::Graphics::Renderer::setup_default_meshes(){

    // Quad
    VertexData quad_vertices[] = {
        {0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f},
        {0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f}
    };

    IndexData quad_indices[] = {
        0,1,2,
        2,3,0
    };

    quad_ = load_mesh(
        quad_vertices,
        quad_indices,
        4,
        6,
        500
    );


    // Circle

    constexpr u32 segments = 80;
    constexpr f32 radius = 1.0f;

    std::vector<VertexData> circle_vertices;
    std::vector<IndexData>  circle_indices;

    circle_vertices.push_back({
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.5f, 0.5f
    });

    for(u32 i = 0; i <= segments; i++){
        f32 angle = (2.0f * Math::PI * i) / segments;

        f32 x = radius * cosf(angle);
        f32 y = radius * sinf(angle);

        circle_vertices.push_back({
            x, y, 0.0f,
            0.0f, 0.0f, 1.0f,
            (x / radius + 1.0f) * 0.5f,
            (y / radius + 1.0f) * 0.5f
        });
    }

    for(u32 i = 1; i <= segments; i++){
        circle_indices.push_back(0);
        circle_indices.push_back(i);
        circle_indices.push_back(i + 1);
    }

    circle_ = load_mesh(
        circle_vertices.data(),
        circle_indices.data(),
        (u32)circle_vertices.size(),
        (u32)circle_indices.size(),
        500
    );
}

void Lux::Graphics::Renderer::begin(){
    gl::Clear(GL_COLOR_BUFFER_BIT);
    //default_shader_.set_uniform_matrix4f(Lux::Math::Matrix4::ortho(0,window_.width_,window_.height_,0,-1.0f,1.0f), "u_Projection");
    //view = Math::Matrix4::look_at(camera_position, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    view = Math::Matrix4::translate(camera_position * -1);
    default_shader_.set_uniform_matrix4f(view, "u_View");
    gl::Viewport(0,0,window_.width_,window_.height_);
}

void Lux::Graphics::Renderer::submit(u32 mesh_id, Core::Transform& transform){
    if(render_table.is_active(mesh_id)){
        RenderObject& object = render_table[mesh_id];

        if(object.instance_count == 0){
            active_ids.push_back(mesh_id);
        }
        if(object.instance_count + 1 <= object.max_instances){
            object.instance_count++;

            *(object.transform_arena_bucket_ptr + MAX_INSTANCES*current_buffer_ + object.transform_arena_bucket_offset) = transform.get_matrix();
            object.transform_arena_bucket_offset ++;
        }


    }else{
        LUX_ERROR("invalid mesh id");
    }
}

void Lux::Graphics::Renderer::end(){
    for(u32& id : active_ids){
        RenderObject& render_obj = render_table[id];
        Mesh& mesh = resource_manager.get_mesh(id);

        vao.link_vbo(mesh.get_vbo(), sizeof(VertexData), 0);
        vao.link_ebo(mesh.get_ebo());

        gl::DrawElementsInstancedBaseInstance(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, nullptr, render_obj.instance_count, render_obj.base_instance_index + MAX_INSTANCES*current_buffer_);
        
        render_obj.instance_count = 0;
        render_obj.transform_arena_bucket_offset = 0;

    }
    active_ids.clear();
    
    if(current_buffer_ < num_buffers_-1)
        current_buffer_++;
    else
        current_buffer_ = 0;
}

u32 Lux::Graphics::Renderer::load_mesh(VertexData* vertex_data, IndexData* index_data, u32 vertex_count, u32 index_count, u32 max_instances){
    LUX_VERIFY(instances_usage + max_instances <= MAX_INSTANCES, "ERROR: limit of instances exceeded");
    instances_usage += max_instances;

    u32 id = render_table.add();
    render_table[id].instance_count = 0;
    render_table[id].max_instances = max_instances;
    render_table[id].transform_arena_bucket_ptr = transform_arena_.alloc<Math::Matrix4>(max_instances);
    render_table[id].transform_arena_bucket_offset = 0;
    render_table[id].base_instance_index = render_table[id].transform_arena_bucket_ptr - transform_instances_ptr_;
    return resource_manager.load_mesh(vertex_data, index_data, vertex_count, index_count);
}

void Lux::Graphics::Renderer::unload_mesh(u32 mesh_id){
    instances_usage -= render_table[mesh_id].max_instances; 
    render_table.remove(mesh_id);
    resource_manager.unload_mesh(mesh_id);
}

void Lux::Graphics::Renderer::draw_rect(const Math::Vector2& position, u32 width, u32 height, f32 rotation, const Math::Vector2& pivot){
    Core::Transform transform;

    rotation = Math::to_radians(rotation);

    transform.set_position(Math::Vector3{position.x, position.y, 0.0f});
    transform.set_scale(Math::Vector3{(f32)width, (f32)height, 1.0f});
    transform.set_rotation({0, 0, rotation});
    transform.set_pivot({pivot.x, pivot.y,0});

    submit(quad_, transform);
}

void Lux::Graphics::Renderer::draw_circle(const Math::Vector2& position, u32 width, u32 height, f32 rotation, const Math::Vector2& pivot){
    Core::Transform transform;

    rotation = Math::to_radians(rotation);

    transform.set_position(Math::Vector3{position.x, position.y, 0.0f});
    transform.set_scale(Math::Vector3{(f32)width, (f32)height, 1.0f});
    transform.set_rotation({0, 0, rotation});
    transform.set_pivot({pivot.x, pivot.y,0});

    submit(circle_, transform);
}

void Lux::Graphics::Renderer::resize(u32 width, u32 height){
    default_shader_.set_uniform_matrix4f(Lux::Math::Matrix4::ortho(0,width,height,0,-1.0f,1.0f), "u_Projection");
}

void Lux::Graphics::Renderer::set_camera_position(Math::Vector3& position){
    camera_position = position;
}