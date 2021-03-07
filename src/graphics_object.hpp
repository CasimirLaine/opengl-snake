#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace Snake
{
	struct LayoutAttribute {
		unsigned int type;
		unsigned int count;
		unsigned int normalized;
	};

	class VertexLayout {
	private:
		std::vector<LayoutAttribute> attributes;
		unsigned int stride;
	public:
		VertexLayout() : stride(0) {}

		template <typename T>
		void add(const unsigned int& count);

		template <>
		void add<float>(const unsigned int& count) {
			attributes.push_back({GL_FLOAT, count, GL_FALSE});
			stride += sizeof(float) * count;
		}

		friend class VertexArray;
	};

	class Shader {
	private:
		unsigned int program;
		mutable std::unordered_map<std::string, int> uniformCache;
	public:
		Shader(
			const std::string& vertexShader,
			const std::string& fragmentShader
		);
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		~Shader();
		void use() const;
		void unuse() const;
		int getLocation(const std::string& attribute) const;
	};

	class VertexBuffer {
	private:
		unsigned int vbo;
	public:
		VertexBuffer();
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		~VertexBuffer();
		void update(const void* data, const unsigned int& size) const;
		void bind() const;
		void unbind() const;
		friend class Drawable;
	};

	class VertexArray {
	private:
		unsigned int vao;
	public:
		VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		~VertexArray();
		void enabledAttributes(const VertexBuffer& vb, const VertexLayout& layout);
		void bind() const;
		void unbind() const;
	};

	class IndexBuffer {
	private:
		unsigned int indexBufferId;
		unsigned int count;
	public:
		IndexBuffer(const unsigned char* indices, const unsigned int& count);
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		~IndexBuffer();
		void bind() const;
		void unbind() const;
		friend class Drawable;
	};
}
