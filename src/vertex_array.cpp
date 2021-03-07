#include <GL/glew.h>
#include "graphics_object.hpp"

namespace Snake
{
	unsigned int sizeofGLType(GLenum type) {
		switch (type) {
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_INT:
			return sizeof(GLint);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
		}
		return 0;
	}

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &vao);
	}

	VertexArray::~VertexArray() {
		unbind();
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}

	void VertexArray::enabledAttributes(const VertexBuffer& vb, const VertexLayout& layout) {
		bind();
		vb.bind();
		unsigned int offset = 0;
		for (unsigned int index = 0; index < layout.attributes.size(); index++) {
			const auto& attribute = layout.attributes[index];
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, attribute.count, attribute.type, attribute.normalized, layout.stride, (const void*) offset);
			offset += attribute.count * sizeofGLType(attribute.type);
		}
	}

	void VertexArray::bind() const {
		glBindVertexArray(vao);
	}

	void VertexArray::unbind() const {
		glBindVertexArray(0);
	}
}
