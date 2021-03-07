#include "input_manager.hpp"

namespace Snake
{
	bool InputManager::isPressed(const int& key) {
		const int& keyStatus = glfwGetKey(window, key);
		switch (keyStatus) {
		case GLFW_PRESS:
		{
			const bool returnValue = !keysHeld[key];
			keysHeld[key] = true;
			return returnValue;
		}
		case GLFW_RELEASE:
			keysHeld[key] = false;
			break;
		}
		return false;
	}
}