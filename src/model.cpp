#include "model.hpp"

namespace Snake
{
	bool checkX(const Vector2& point, const Rectangle& rect) {
		return point.x >= rect.topLeft.x && point.x < rect.topRight.x;
	}

	bool checkY(const Vector2& point, const Rectangle& rect) {
		return point.y >= rect.bottomLeft.y && point.y < rect.topLeft.y;
	}

	void checkCollisions(unsigned char* dimensionsCross, const Rectangle& first, const Rectangle& second) {
		for (unsigned int index = 0; index < 4; index++) {
			if (checkX(first.vectors[index], second)) {
				dimensionsCross[0]++;
			}
			if (checkY(first.vectors[index], second)) {
				dimensionsCross[1]++;
			}
		}
	}

	bool Rectangle::collides(const Rectangle& other) const {
		unsigned char dimensionsCross[2] = {0, 0};
		checkCollisions(dimensionsCross, *this, other);
		checkCollisions(dimensionsCross, other, *this);
		if (dimensionsCross[0] > 3 && dimensionsCross[1] > 3) {
			return true;
		}
		return false;
	}

	Rectangle Snake::createSquare(const float& width) {
		return createSquare({0, 0}, width);
	}

	Rectangle Snake::createSquare(const Snake::Vector2& position, const float& width) {
		return {
			position + Snake::Vector2(0, width),
			position + Snake::Vector2(width, width),
			position + Snake::Vector2(width, 0),
			position
		};
	}
}
