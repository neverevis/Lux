#include "core/transform.hpp"
#include "graphics/data.hpp"
#include "math/constants.hpp"
#include "math/matrix4.hpp"
#include "math/vector2.hpp"
#include <graphics/renderer.hpp>

#include <core/debug.hpp>
#include <graphics/gl.hpp>

#define MAX_INSTANCES 100000
#define MAX_MESHES 1024

namespace gl = Lux::Graphics::gl;

Lux::Graphics::Renderer::Renderer(Platform::Window& window)
    : default_shader_("src/shaders/default.vert", "src/shaders/default.frag")
    , resource_manager(MAX_MESHES)
    , render_table(MAX_MESHES)
{
    default_shader_.use();
    default_shader_.set_uniform_matrix4f(Lux::Math::Matrix4::ortho(0,window.width_,window.height_,0,-1.0f,1.0f), "u_Projection");

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
    transform_instances_ptr_ = (Math::Matrix4*) transform_vbo_.alloc_shared_memory(MAX_INSTANCES * sizeof(Math::Matrix4));
    transform_arena_.use((u8*)transform_instances_ptr_, MAX_INSTANCES * sizeof(Math::Matrix4));
    
    setup_default_meshes();
    gl::ClearColor(0,0,0,1);
}

Lux::Graphics::Renderer::~Renderer() = default;

void Lux::Graphics::Renderer::setup_default_meshes(){
    //quad
    VertexData vertices[] = {
        {0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f},
        {0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f}
    };

    IndexData indices[] = {
        0,1,2,
        2,3,0
    };

    quad_ = load_mesh(vertices, indices, sizeof(vertices) / sizeof(VertexData), sizeof(indices) / sizeof(IndexData), 1000);
}

void Lux::Graphics::Renderer::begin(){
    gl::Clear(GL_COLOR_BUFFER_BIT);
}

void Lux::Graphics::Renderer::submit(u32 mesh_id, Core::Transform& transform){
    if(render_table.is_active(mesh_id)){
        RenderObject& object = render_table[mesh_id];

        if(object.instance_count == 0){
            active_ids.push_back(mesh_id);
        }
        object.instance_count++;

        *(object.transform_arena_bucket_ptr + object.transform_arena_bucket_offset) = transform.get_matrix();
        object.transform_arena_bucket_offset ++;


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

        gl::DrawElementsInstancedBaseInstance(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, nullptr, render_obj.instance_count, render_obj.base_instance_index);
        
        render_obj.instance_count = 0;
        render_obj.transform_arena_bucket_offset = 0;

    }
    active_ids.clear();
}

u32 Lux::Graphics::Renderer::load_mesh(VertexData* vertex_data, IndexData* index_data, u32 vertex_count, u32 index_count, u32 max_instances){
    u32 id = render_table.add();
    render_table[id].instance_count = 0;
    render_table[id].transform_arena_bucket_ptr = transform_arena_.alloc<Math::Matrix4>(max_instances);
    render_table[id].transform_arena_bucket_offset = 0;
    render_table[id].base_instance_index = render_table[id].transform_arena_bucket_ptr - transform_instances_ptr_;
    return resource_manager.load_mesh(vertex_data, index_data, vertex_count, index_count);
}

void Lux::Graphics::Renderer::unload_mesh(u32 mesh_id){
    render_table.remove(mesh_id);
    resource_manager.unload_mesh(mesh_id);
}

void Lux::Graphics::Renderer::draw_rect(Math::Vector2 position, u32 width, u32 height, f32 rotation){
    Core::Transform transform;

    rotation = Math::to_radians(rotation);

    transform.set_position(Math::Vector3{position.x, position.y, 0.0f});
    transform.set_scale(Math::Vector3{(f32)width, (f32)height, 1.0f});
    transform.set_rotation({0, 0, rotation});

    submit(quad_, transform);
}