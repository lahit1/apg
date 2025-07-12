#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

struct Shader {
	unsigned int ptr;
	Shader* next;

	inline Shader* compile() {
	        glCompileShader(ptr);
		return this;
	}

	inline void del() {
	        glDeleteShader(ptr);
	}
};

namespace Shaders {

Shader* create(const GLchar* const* code, GLenum shaderType);

void freeAll();

}
