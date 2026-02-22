#version 450 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : enable

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in uint64_t aHandle;

out vec2 vUv;
flat out uint64_t vHandle;

void main(){
    gl_Position = vec4(aPos, 0.0, 1.0);
    vUv = aUv;
    vHandle = aHandle;
}