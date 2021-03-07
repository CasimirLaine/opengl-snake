#version 460

layout(location = 0) in vec4 position;

uniform mat4 uMVP;
uniform vec4 uTranslation;

void main() {
	gl_Position = uMVP * (position + uTranslation);
}
