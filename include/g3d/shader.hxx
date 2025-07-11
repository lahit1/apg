#pragma once

struct Shader {
	unsigned int ptr;
	Shader* next;

	inline Shader* compile() {
        	glCompileShader(ptr);
        	return this;
	}

	inline Shader* del() {
	        glDeleteShader(ptr);
	        return this;
	}
};

namespace Shaders {


inline Shader *first, *last;

inline Shader* create(const GLchar* const* code, GLenum shaderType) {
        Shader *ret = new Shader();
	if(first == nullptr) first = last = ret;
	else {
		last->next = ret;
		last = ret;
	}

        ret->ptr = glCreateShader(shaderType);
        glShaderSource(ret->ptr, 1, code, NULL);
        return ret;
}

inline void freeAll() {
	Shader *cur=first, *ref;
	while(cur != nullptr) {
		ref = cur;
		cur = ref->next;
		ref->del(); // Delete opengl object
		delete ref;
	};
}

}
