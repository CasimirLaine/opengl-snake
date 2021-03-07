#include <GL/glew.h>
#include "graphics_object.hpp"

namespace Snake
{
	VertexBuffer::VertexBuffer() {
		glGenBuffers(1, &vbo);
	}

	VertexBuffer::~VertexBuffer() {
		unbind();
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}

	void VertexBuffer::update(const void* data, const unsigned int& size) const {
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	void VertexBuffer::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
