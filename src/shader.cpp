#include <GL/glew.h>
#include "graphics_object.hpp"
#include "logger.hpp"

namespace Snake
{
	GLuint compileShader(const GLuint& type, const std::string& source) {
		const GLuint& shaderId = glCreateShader(type);
		const char* const src = source.c_str();
		glShaderSource(shaderId, 1, &src, nullptr);
		glCompileShader(shaderId);
		int result;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int lenght;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &lenght);
			GLchar* const message = new char[lenght * sizeof(GLchar)];
			glGetShaderInfoLog(shaderId, lenght, &lenght, message);
			Snake::log(message);
			delete[] message;
		}
		return shaderId;
	}

	Shader::Shader(
		const std::string& vertexShader,
		const std::string& fragmentShader
	) {
		const GLuint& vs = compileShader(GL_VERTEX_SHADER, vertexShader);
		const GLuint& fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
		program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);
		glDetachShader(program, vs);
		glDetachShader(program, fs);
	}

	Shader::~Shader() {
		glDeleteProgram(program);
		program = 0;
	}

	void Shader::use() const {
		glUseProgram(program);
	}

	void Shader::unuse() const {
		glUseProgram(0);
	}

	int Shader::getLocation(const std::string& attribute) const {
		if (uniformCache.find(attribute) != uniformCache.end()) {
			return uniformCache[attribute];
		}
		const int& location = glGetUniformLocation(program, attribute.c_str());
		uniformCache[attribute] = location;
		return location;
	}
}
