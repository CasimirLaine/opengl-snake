#include <GL/glew.h>
#include "drawable.hpp"

namespace Snake
{
	void Drawable::draw(const Vector2& translation, const glm::mat4& mvp) const {
		shaderPtr->use();
		glUniform4f(shaderPtr->getLocation("uColor"), color.r, color.g, color.b, color.a);
		glUniform4f(shaderPtr->getLocation("uTranslation"), translation.x, translation.y, 0, 0);
		glUniformMatrix4fv(shaderPtr->getLocation("uMVP"), 1, GL_FALSE, &mvp[0][0]);
		vertexArrayPtr->bind();
		indexBufferPtr->bind();
		glDrawElements(GL_TRIANGLES, indexBufferPtr->count, GL_UNSIGNED_BYTE, nullptr);
		shaderPtr->unuse();
		vertexArrayPtr->unbind();
		indexBufferPtr->unbind();
	}
}
