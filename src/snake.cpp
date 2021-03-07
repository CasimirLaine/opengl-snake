#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
#include "snake.hpp"

namespace Snake
{

	void SnakeModel::grow() {
		cells.push_back(Cell());
	}

	void SnakeModel::cut(const unsigned int& index) {
		cells.erase(cells.begin() + index, cells.end());
	}

	void SnakeModel::moveHead(const float& x, const float& y) {
		if (cells.size() > 0) {
			Cell& head = cells[0];
			head.position.x += x;
			head.position.y += y;
		}
	}

	void SnakeModel::move(const float& x, const float& y) {
		for (unsigned int index = cells.size() - 1; index > 0; index--) {
			Cell& cell = cells[index];
			Cell& nextCell = cells[index - 1];
			cell.position = nextCell.position;
		}
		moveHead(x, y);
	}

	void SnakeModel::turn(const bool& clockwise) {
		if (clockwise) {
			++direction;
		} else {
			--direction;
		}
	}

	void Game::newTreat() {
		static std::default_random_engine engine;
		engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
		static std::uniform_real_distribution<float> distribution(0, 1);
		const float randomX = distribution(engine);
		const float randomY = distribution(engine);
		treat = Vector2(
			randomX * (size.x - 1),
			randomY * (size.y - 1)
		);
	}

	bool Game::checkCollision(const Vector2& moveVector) {
		const auto& cells = snakePtr->getCells();
		if (cells.empty()) {
			return false;
		}
		const Cell& head = cells[0];
		const Vector2& movedHead = head.position + moveVector;
		if (movedHead.x < 0 || movedHead.y < 0
			|| movedHead.x + cellWidth > size.x || movedHead.y + cellWidth >size.y) {
			return true;
		}
		return false;
	}

	void Game::checkClip(const Vector2& headPrevious) {
		const auto& cells = snakePtr->getCells();
		if (cells.empty()) {
			return;
		}
		const Vector2& headVector = cells[0].position;
		const Rectangle& headSquare = {
			Vector2(std::min(headPrevious.x, headVector.x),
			std::max(headPrevious.y + snakePtr->speed, headVector.y + snakePtr->speed)),
			Vector2(std::max(headPrevious.x + snakePtr->speed, headVector.x + snakePtr->speed),
			std::max(headPrevious.y + snakePtr->speed, headVector.y + snakePtr->speed)),
			Vector2(std::max(headPrevious.x + snakePtr->speed, headVector.x + snakePtr->speed),
			std::min(headPrevious.y, headVector.y)),
			Vector2(std::min(headPrevious.x, headVector.x),
			std::min(headPrevious.y, headVector.y))
		};
		for (unsigned int index = 4; index < cells.size(); index++) {
			const Rectangle& square = createSquare(cells[index].position, snakePtr->speed);
			if (headSquare.collides(square)) {
				snakePtr->cut(index);
				break;
			}
		}
		const Rectangle& treatSquare = createSquare(treat, snakePtr->speed);
		if (headSquare.collides(treatSquare)) {
			snakePtr->grow();
			newTreat();
		}
	}

	Game::Game(const Vector2& size, const float& cellWidth, const Direction& direction, const Vector2& startingPoint)
		: size(size), cellWidth(cellWidth) {
		snakePtr = new SnakeModel(direction, cellWidth);
		snakePtr->cells[0].position = startingPoint;
		newTreat();
	}

	Game::~Game() {
		delete snakePtr;
	}

	void Game::update() {
		if (gameOver) {
			return;
		}
		if (checkCollision(snakePtr->getMoveVector())) {
			gameOver = true;
			return;
		}
		const Vector2 headPrevious = snakePtr->cells[0].position;
		const unsigned int size = snakePtr->cells.size();
		const Vector2 lastPrevious = snakePtr->cells[size - 1].position;
		snakePtr->move();
		checkClip(headPrevious);
		if (size < snakePtr->cells.size()) {
			snakePtr->cells[snakePtr->cells.size() - 1].position = lastPrevious;
		}
	}
}
