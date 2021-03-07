#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "graphics_object.hpp"
#include "model.hpp"

namespace Snake
{
	class Drawable {
	private:
		const Shader* const shaderPtr;
		const IndexBuffer* const indexBufferPtr;
		const VertexArray* const vertexArrayPtr;
		const VertexBuffer* const vertexBufferPtr;
		Vector4 color = {0, 0, 0, 1.0};
	public:
		Drawable(
			const Shader* const shaderPtr,
			const IndexBuffer* const indexBufferPtr,
			const VertexArray* const vertexArrayPtr,
			const VertexBuffer* const vertexBufferPtr
		)
			: shaderPtr(shaderPtr), indexBufferPtr(indexBufferPtr), vertexArrayPtr(vertexArrayPtr),
			vertexBufferPtr(vertexBufferPtr) {
		}
		~Drawable() {
			delete shaderPtr;
			delete indexBufferPtr;
			delete vertexArrayPtr;
			delete vertexBufferPtr;
		}
		void draw(const Vector2& translation, const glm::mat4& mvp) const;
		inline void setColor(const Vector4& color) {
			this->color = color;
		}
	};
}
