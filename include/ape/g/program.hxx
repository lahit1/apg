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

	GLuint *vpULoc_ptr;
	GLuint *modelULoc_ptr;
	GLuint *normalULoc_ptr;
	GLuint *viewPosULoc_ptr;

	GLuint ptr;

	virtual void use() = 0;
};

struct ShaderProgram : public Program {

	ShaderProgram() {
		vpULoc_ptr = new GLuint();
		modelULoc_ptr = new GLuint();
		normalULoc_ptr = new GLuint();
		viewPosULoc_ptr = new GLuint();
	}

	inline void attach(std::shared_ptr<Shader> s) {
        	glAttachShader(ptr, s->ptr);
	}

	inline void link() {
        	glLinkProgram(ptr);
		*vpULoc_ptr = glGetUniformLocation(ptr, Programs::vpULoc);
		*modelULoc_ptr = glGetUniformLocation(ptr, Programs::modelULoc);
		*normalULoc_ptr = glGetUniformLocation(ptr, Programs::normalULoc);
		*viewPosULoc_ptr = glGetUniformLocation(ptr, Programs::viewPosULoc);
	}

	static std::shared_ptr<ShaderProgram> mk();

	void use() override;
};

class ProgramGroup : public Program {
	std::vector<std::shared_ptr<Program>> pr_ls;
	std::shared_ptr<Program> c_pr;

	public:
	inline void with(const size_t i) {
		c_pr = pr_ls[i];
		vpULoc_ptr = c_pr->vpULoc_ptr;
		modelULoc_ptr = c_pr->modelULoc_ptr;
		normalULoc_ptr = c_pr->normalULoc_ptr;
		viewPosULoc_ptr = c_pr->viewPosULoc_ptr;
	};

	inline void add(std::shared_ptr<Program> p) {
		pr_ls.push_back(p);
		if(!c_pr) with(0);
	};

	static std::shared_ptr<ProgramGroup> mk();

	void use() override;
};
