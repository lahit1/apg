#pragma once

#include<g3d/shader.hxx>

struct Program;

namespace Programs {

	extern const char *vpULoc,
		*modelULoc,
		*normalULoc;

	extern const char
                *materialDiffuseLoc,
                *materialSpecularLoc,
                *materialShininessLoc;
	extern const char *viewPosULoc;

	Program* create();
}

struct Program {

	GLuint vpULoc_ptr;
	GLuint modelULoc_ptr;
	GLuint normalULoc_ptr;

	GLuint materialDiffuseLoc_ptr;
	GLuint materialSpecularLoc_ptr;
	GLuint materialShininessLoc_ptr;

	GLuint viewPosULoc_ptr;

	unsigned int ptr;
	inline void attach(Shader* s) {
        	glAttachShader(ptr, s->ptr);
	}

	inline void link() {
        	glLinkProgram(ptr);
		vpULoc_ptr = glGetUniformLocation(ptr, Programs::vpULoc);
		modelULoc_ptr = glGetUniformLocation(ptr, Programs::modelULoc);
		normalULoc_ptr = glGetUniformLocation(ptr, Programs::normalULoc);

		materialDiffuseLoc_ptr = glGetUniformLocation(ptr, Programs::materialDiffuseLoc);
		materialSpecularLoc_ptr = glGetUniformLocation(ptr, Programs::materialSpecularLoc);
		materialShininessLoc_ptr = glGetUniformLocation(ptr, Programs::materialShininessLoc);

		viewPosULoc_ptr = glGetUniformLocation(ptr, Programs::viewPosULoc);
	}
};
