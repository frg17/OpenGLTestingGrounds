#version 330

layout(location = 0) in vec4 pos;
out vec4 vColor;

uniform mat4 mv;
uniform vec4 color;

void main() {
    vColor = color;

    gl_Position = mv * pos;
}