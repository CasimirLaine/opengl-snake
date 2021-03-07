#include <string>
#include <iostream>
#include <GL/glew.h>
#include "logger.hpp"

namespace Snake
{

	std::string getSourceString(const GLenum& source) {
		switch (source) {
		case GL_DEBUG_SOURCE_API:
			return "GL_DEBUG_SOURCE_API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			return "GL_DEBUG_SOURCE_SHADER_COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			return "GL_DEBUG_SOURCE_THIRD_PARTY";
		case GL_DEBUG_SOURCE_APPLICATION:
			return "GL_DEBUG_SOURCE_APPLICATION";
		case GL_DEBUG_SOURCE_OTHER:
			return "GL_DEBUG_SOURCE_OTHER";
		default:
			return "Unknown source " + source;
		}
	}

	std::string getTypeString(const GLenum& type) {
		switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			return "GL_DEBUG_TYPE_ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY:
			return "GL_DEBUG_TYPE_PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE:
			return "GL_DEBUG_TYPE_PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER:
			return "GL_DEBUG_TYPE_MARKER";
		case GL_DEBUG_TYPE_PUSH_GROUP:
			return "GL_DEBUG_TYPE_PUSH_GROUP";
		case GL_DEBUG_TYPE_POP_GROUP:
			return "GL_DEBUG_TYPE_POP_GROUP";
		case GL_DEBUG_TYPE_OTHER:
			return "GL_DEBUG_TYPE_OTHER";
		default:
			return "Unknown type " + type;
		}
	}

	std::string getSeverityString(const GLenum& severity) {
		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			system("Color 04");
			return "GL_DEBUG_SEVERITY_HIGH";
		case GL_DEBUG_SEVERITY_MEDIUM:
			system("Color 05");
			return "GL_DEBUG_SEVERITY_MEDIUM";
		case GL_DEBUG_SEVERITY_LOW:
			system("Color 06");
			return "GL_DEBUG_SEVERITY_LOW";
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			system("Color 0F");
			return "GL_DEBUG_SEVERITY_NOTIFICATION";
		default:
			return "Unknown severity " + severity;
		}
	}

	void GLAPIENTRY errorCallbackGL(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam
	) {
		std::string output =
			"{"
			"\n\t[SOURCE]: " + getSourceString(source) +
			"\n\t[TYPE]: " + getTypeString(type) +
			"\n\t[ID]: " + std::to_string(id) +
			"\n\t[SEVERITY]: " + getSeverityString(severity) +
			"\n\t[MESSAGE]: " + message +
			"\n\t[USER_PARAM]: " + "0" +
			"\n}"
			;
		log(output);
	}

	void errorCallbackGLFW(int error, const char* description) {
		log("[GLWF]: ", error, " ", description);
	}
}
