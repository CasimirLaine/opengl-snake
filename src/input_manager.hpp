#pragma once
#include <unordered_map>
#include <GLFW/glfw3.h>

namespace Snake
{
	class InputManager {
	private:
		GLFWwindow* window;
		std::unordered_map<int, bool> keysHeld;
	public:
		InputManager(GLFWwindow* window) : window(window) {}
		bool isPressed(const int& key);
	};
}
