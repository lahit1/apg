#pragma once

#include<memory>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

struct Shader : std::enable_shared_from_this<Shader> {
	unsigned int ptr;

	inline std::shared_ptr<Shader> compile() {
	        glCompileShader(ptr);
		return shared_from_this();
	}

	inline void del() {
	        glDeleteShader(ptr);
	}
};

namespace Shaders {

std::shared_ptr<Shader> create(const GLchar* const* code, GLenum shaderType);

}
