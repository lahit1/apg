#pragma once

#include<g/shader.hxx>

struct Program;

namespace Programs {

	extern char *vpULoc,
		*modelULoc,
		*normalULoc,
		*viewPosULoc;

}

class Program {
	Program(); // hide

	public:
	GLuint vpULoc_ptr;
	GLuint modelULoc_ptr;
	GLuint normalULoc_ptr;
	GLuint viewPosULoc_ptr;

	unsigned int ptr;
	inline void attach(std::shared_ptr<Shader> s) {
        	glAttachShader(ptr, s->ptr);
	}

	inline void link() {
        	glLinkProgram(ptr);
		vpULoc_ptr = glGetUniformLocation(ptr, Programs::vpULoc);
		modelULoc_ptr = glGetUniformLocation(ptr, Programs::modelULoc);
		normalULoc_ptr = glGetUniformLocation(ptr, Programs::normalULoc);
		viewPosULoc_ptr = glGetUniformLocation(ptr, Programs::viewPosULoc);
	}

	static std::shared_ptr<Program> mk();

};
