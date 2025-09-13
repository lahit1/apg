#pragma once

#include<ape/g/shader.hxx>
#include<vector>

namespace Programs {

	extern char *vpULoc,
		*modelULoc,
		*normalULoc,
		*viewPosULoc;

}

struct Program {

	GLuint vpULoc_ptr;
	GLuint modelULoc_ptr;
	GLuint normalULoc_ptr;
	GLuint viewPosULoc_ptr;

	GLuint ptr;
};

struct ShaderProgram : public Program {

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

	static std::shared_ptr<ShaderProgram> mk();

};

class ProgramGroup : public Program {
	std::vector<GLuint> ptr_ls;

	public:
	inline void with(const size_t i) {
		ptr = ptr_ls[i];
	};

	inline void add(Program& p) {
		ptr_ls.push_back(p.ptr);
	};

	static std::shared_ptr<ProgramGroup> mk();
};
