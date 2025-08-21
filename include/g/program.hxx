#pragma once

#include<g/shader.hxx>

struct Program;

namespace Programs {

	extern const char *vpULoc,
		*modelULoc,
		*normalULoc;

	extern const char
                *materialAmbientCLoc,
                *materialDiffuseCLoc,
                *materialSpecularCLoc,
                *materialShininessLoc;

	extern const char
                *materialDiffuseTLoc,
                *materialSpecularTLoc,
                *materialNormalTLoc;

	extern const char *viewPosULoc;

	Program* create();
}

struct Program {

	GLuint vpULoc_ptr;
	GLuint modelULoc_ptr;
	GLuint normalULoc_ptr;

	GLuint materialDiffuseCLoc_ptr;
	GLuint materialSpecularCLoc_ptr;
	GLuint materialShininessLoc_ptr;

        GLuint materialDiffuseTLoc_ptr;
        GLuint materialSpecularTLoc_ptr;
        GLuint materialNormalTLoc_ptr;

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

		materialDiffuseCLoc_ptr = glGetUniformLocation(ptr, Programs::materialDiffuseCLoc);
		materialSpecularCLoc_ptr = glGetUniformLocation(ptr, Programs::materialSpecularCLoc);
		materialShininessLoc_ptr = glGetUniformLocation(ptr, Programs::materialShininessLoc);

		materialDiffuseTLoc_ptr = glGetUniformLocation(ptr, Programs::materialDiffuseTLoc);
                materialSpecularTLoc_ptr = glGetUniformLocation(ptr, Programs::materialSpecularTLoc);
                materialNormalTLoc_ptr = glGetUniformLocation(ptr, Programs::materialNormalTLoc);

		viewPosULoc_ptr = glGetUniformLocation(ptr, Programs::viewPosULoc);
	}
};
