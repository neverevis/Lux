#version 450 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aOffset;

void main(){
    gl_Position = vec4(aPos[0] + aOffset[0], aPos[1] + aOffset[1], 0.0, 1.0);
}