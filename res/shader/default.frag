#version 460

layout(location = 0) out vec4 color;

uniform vec4 uColor;

void main() {
	color = uColor;
}
