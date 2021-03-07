#pragma once

namespace Snake
{
	struct Vector2 {
		float x;
		float y;
		Vector2() : x(0), y(0) {}
		Vector2(const float& x, const float& y) : x(x), y(y) {}

		inline Vector2& operator +(const Vector2& other) const {
			return Vector2(x + other.x, y + other.y);
		}
	};

	struct Vector4 {
		union {
			float x;
			float r;
		};
		union {
			float y;
			float g;
		};
		union {
			float z;
			float b;
		};
		union {
			float w;
			float a;
		};
	};

	struct Rectangle {
		union {
			Snake::Vector2 vectors[4];
			struct {
				Snake::Vector2 topLeft;
				Snake::Vector2 topRight;
				Snake::Vector2 bottomRight;
				Snake::Vector2 bottomLeft;
			};
		};

		bool collides(const Rectangle& other) const;
	};

	Rectangle createSquare(const float& width);

	Rectangle createSquare(const Snake::Vector2&, const float& width);
}
