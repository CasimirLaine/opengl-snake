#define GLEW_STATIC
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "const.hpp"
#include "logger.hpp"
#include "io.hpp"
#include "drawable.hpp"
#include "snake.hpp"
#include "model.hpp"
#include "graphics_object.hpp"
#include "input_manager.hpp"

static constexpr const unsigned int& WINDOW_WIDTH = 640;
static constexpr const unsigned int& WINDOW_HEIGHT = 480;

static const std::string& VERTEX_SHADER_PATH = "res/shader/default.vert";
static const std::string& FRAGMENT_SHADER_PATH = "res/shader/default.frag";

static constexpr const float& SPEED = 1;
static constexpr const float& FIELD_SIZE = SPEED * 20;
static constexpr const double& UPDATER_INTERVAL_MS = 500;

static void enableDebug() {
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(Snake::errorCallbackGL, 0);
	Snake::log("OpenGL version: ", glGetString(GL_VERSION));
}

glm::mat4& projectionMatrix = glm::ortho(0.0F, FIELD_SIZE, 0.0F, FIELD_SIZE);

void setProjectionMatrix(float width, float height) {
	const float widthOffset = std::max((width - height) * 0.5F, 0.0F);
	const float heightOffset = std::max((height - width) * 0.5F, 0.0F);
	projectionMatrix = glm::ortho(-widthOffset, width - widthOffset, -heightOffset, height - heightOffset);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	const float aspect = (float) width / (float) height;
	if (height > width) {
		setProjectionMatrix(FIELD_SIZE, FIELD_SIZE / aspect);
	} else if (width > height) {
		setProjectionMatrix(FIELD_SIZE * aspect, FIELD_SIZE);
	} else {
		setProjectionMatrix(FIELD_SIZE, FIELD_SIZE);
	}
}

void setGLFWHints() {
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, SNAKE_DEBUG ? GLFW_TRUE : GLFW_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
	glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
	glfwWindowHint(GLFW_STEREO, GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, SNAKE_DEBUG ? GLFW_TRUE : GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, SNAKE_DEBUG ? GLFW_FALSE : GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

double getTimeMS() {
	return glfwGetTime() * 1000;
}

Snake::Drawable* createDrawable(const Snake::Rectangle& square) {
	const Snake::Shader* shader = new Snake::Shader(
		Snake::readShader(VERTEX_SHADER_PATH),
		Snake::readShader(FRAGMENT_SHADER_PATH)
	);
	const GLubyte indices[6] = {
		0, 1, 2,
		2, 3, 0,
	};
	const Snake::IndexBuffer* indexBuffer = new Snake::IndexBuffer(indices, 6);
	Snake::VertexArray* const vertexArray = new Snake::VertexArray();
	Snake::VertexLayout layout;
	layout.add<float>(2);
	const Snake::VertexBuffer* const vertexBuffer = new Snake::VertexBuffer();
	vertexArray->enabledAttributes(*vertexBuffer, layout);
	vertexBuffer->bind();
	vertexBuffer->update(&square.vectors, sizeof(square.vectors));
	return new Snake::Drawable(shader, indexBuffer, vertexArray, vertexBuffer);
}

int main(void) {
	glfwSetErrorCallback(Snake::errorCallbackGLFW);
	if (glfwInit() != GLFW_TRUE) {
		return -1;
	}
	setGLFWHints();
	GLFWwindow* const window = glfwCreateWindow(
		WINDOW_WIDTH, WINDOW_HEIGHT, Snake::APP_NAME.c_str(), NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	framebufferSizeCallback(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetWindowSizeLimits(window, WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5, -1, -1);
	glfwSetWindowOpacity(window, 1.0);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}
	if (SNAKE_DEBUG) {
		enableDebug();
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Snake::Game game({FIELD_SIZE, FIELD_SIZE}, SPEED, Snake::UP, {FIELD_SIZE * 0.5F, FIELD_SIZE * 0.5F});
	Snake::Drawable* snakeCellDrawablePtr = createDrawable(Snake::createSquare(SPEED));
	Snake::Drawable* fieldDrawablePtr = createDrawable(Snake::createSquare(FIELD_SIZE));
	Snake::InputManager inputManager(window);
	glClearColor(0, 0, 0, 1);
	double lastUpdate = getTimeMS();
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		double now = getTimeMS();
		double timeDelta = now - lastUpdate;
		if (!game.gameOver && timeDelta >= UPDATER_INTERVAL_MS) {
			lastUpdate = now;
			game.update();
		}
		Snake::SnakeModel* snake = game.getSnakeModel();
		if (inputManager.isPressed(GLFW_KEY_LEFT)) {
			snake->turnLeft();
		} else if (inputManager.isPressed(GLFW_KEY_RIGHT)) {
			snake->turnRight();
		}
		fieldDrawablePtr->setColor({1.0, 1.0, 1.0, 1.0});
		fieldDrawablePtr->draw({0, 0}, projectionMatrix);
		snakeCellDrawablePtr->setColor({0.0, 1.0, 0.0, 1.0});
		snakeCellDrawablePtr->draw(game.getTreat(), projectionMatrix);
		const std::vector<Snake::Cell>& cells = snake->getCells();
		for (int index = cells.size() - 1; index >= 0; index--) {
			if (index == 0) {
				snakeCellDrawablePtr->setColor({1.0, 0.0, 0.0, 1.0});
			} else {
				snakeCellDrawablePtr->setColor({0.0, 0.0, 1.0, 1.0});
			}
			snakeCellDrawablePtr->draw(cells[index].position, projectionMatrix);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete snakeCellDrawablePtr;
	delete fieldDrawablePtr;
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
