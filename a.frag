#version 450 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader_int64 : enable

in vec2 vUv;
flat in uint64_t vHandle;

out vec4 FragColor;

void main() {
    sampler2D myTex = sampler2D(vHandle);
    FragColor = texture(myTex, vUv);
}