#pragma once
#include <GL/glew.h>
#include "graphics_object.hpp"

namespace Snake
{
	IndexBuffer::IndexBuffer(const unsigned char* indices, const unsigned int& count)
		: count(count) {
		glGenBuffers(1, &indexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned char), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer() {
		unbind();
		glDeleteBuffers(1, &indexBufferId);
		indexBufferId = 0;
	}

	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	}

	void IndexBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
