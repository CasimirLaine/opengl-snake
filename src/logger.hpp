#pragma once
#include <iostream>
#include <GL/glew.h>

namespace Snake
{
	void GLAPIENTRY errorCallbackGL(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam
	);

	void errorCallbackGLFW(int error, const char* description);

	template <typename... T>
	inline void log(const T&... text) {
		(std::cout << ... << text) << std::endl;
	}
}
