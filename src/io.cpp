#include <string>
#include <fstream>
#include <sstream>
#include "io.hpp"

namespace Snake
{
	const std::string readShader(const std::string& filePath) {
		std::ifstream stream(filePath);
		std::string line;
		std::stringstream stringStream;
		while (std::getline(stream, line)) {
			stringStream << line << '\n';
		}
		return stringStream.str();
	}
}
