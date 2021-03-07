#pragma once
#include <vector>
#include "model.hpp"

namespace Snake
{
	enum Direction : unsigned char {
		LEFT, UP, RIGHT, DOWN
	};

	inline Direction& operator++(Direction& direction) {
		switch (direction) {
		case Direction::LEFT:
			return direction = Direction::UP;
		case Direction::UP:
			return direction = Direction::RIGHT;
		case Direction::RIGHT:
			return direction = Direction::DOWN;
		case Direction::DOWN:
			return direction = Direction::LEFT;
		default:
			return direction;
		}
	}

	inline Direction& operator--(Direction& direction) {
		switch (direction) {
		case Direction::LEFT:
			return direction = Direction::DOWN;
		case Direction::DOWN:
			return direction = Direction::RIGHT;
		case Direction::RIGHT:
			return direction = Direction::UP;
		case Direction::UP:
			return direction = Direction::LEFT;
		default:
			return direction;
		}
	}

	struct Cell {
		Vector2 position = Vector2(0, 0);
	};

	class SnakeModel {
	private:
		static constexpr const unsigned int DEFAULT_CAPACITY = 100;
		std::vector<Cell> cells;
		Direction direction;
		const float speed;
		void moveHead(const float& x, const float& y);
		void move(const float& x, const float& y);
		void turn(const bool& clockwise);
	public:

		SnakeModel(const Direction& direction, const float& speed) : direction(direction), speed(speed) {
			cells.reserve(DEFAULT_CAPACITY);
			grow();
		}

		void grow();
		void cut(const unsigned int& index);

		void move() {
			const Vector2& moveVector = getMoveVector();
			move(moveVector.x, moveVector.y);
		}

		inline void turnLeft() {
			turn(false);
		}

		inline void turnRight() {
			turn(true);
		}

		inline Vector2 getMoveVector() const {
			switch (direction) {
			case LEFT:
				return Vector2(-speed, 0);
			case UP:
				return Vector2(0, speed);
			case RIGHT:
				return Vector2(speed, 0);
			case DOWN:
				return Vector2(0, -speed);
			default:
				return Vector2(0, 0);
			}
		}

		std::vector<Cell>& getCells() {
			return cells;
		}
		friend class Game;
	};

	class Game {
	private:
		SnakeModel* snakePtr;
		float cellWidth;
		Vector2 treat;
		Vector2 size;
		void newTreat();
		bool checkCollision(const Vector2& moveVector);
		void checkClip(const Vector2& headPrevious);
	public:
		bool gameOver = false;
		Game(const Vector2& size, const float& cellWidth, const Direction& direction, const Vector2& startingPoint);
		~Game();
		void update();
		inline SnakeModel* getSnakeModel() const {
			return snakePtr;
		}
		inline Vector2 getTreat() const {
			return treat;
		}
		inline Vector2 getSize() const {
			return size;
		}
	};
}
