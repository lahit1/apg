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

	virtual GLuint vpULoc_ptr() = 0;
	virtual GLuint modelULoc_ptr() = 0;
	virtual GLuint normalULoc_ptr() = 0;
	virtual GLuint viewPosULoc_ptr() = 0;

	GLuint ptr;

	virtual void use() = 0;
};

struct ShaderProgram : public Program {

	GLuint _vpULoc_ptr;
	GLuint _modelULoc_ptr;
	GLuint _normalULoc_ptr;
	GLuint _viewPosULoc_ptr;


	GLuint vpULoc_ptr() override;
	GLuint modelULoc_ptr() override;
	GLuint normalULoc_ptr() override;
	GLuint viewPosULoc_ptr() override;

	inline void attach(std::shared_ptr<Shader> s) {
        	glAttachShader(ptr, s->ptr);
	}

	inline void link() {
        	glLinkProgram(ptr);
		_vpULoc_ptr = glGetUniformLocation(ptr, Programs::vpULoc);
		_modelULoc_ptr = glGetUniformLocation(ptr, Programs::modelULoc);
		_normalULoc_ptr = glGetUniformLocation(ptr, Programs::normalULoc);
		_viewPosULoc_ptr = glGetUniformLocation(ptr, Programs::viewPosULoc);
	}

	static std::shared_ptr<ShaderProgram> mk();

	void use() override;
};

class ProgramGroup : public Program {
	std::vector<std::shared_ptr<Program>> pr_ls;
	std::shared_ptr<Program> c_pr;

	GLuint vpULoc_ptr() override;
	GLuint modelULoc_ptr() override;
	GLuint normalULoc_ptr() override;
	GLuint viewPosULoc_ptr() override;

	public:
	inline void with(const size_t i) {
		c_pr = pr_ls[i];
	}

	inline void add(std::shared_ptr<Program> p) {
		pr_ls.push_back(p);
		if(!c_pr) with(0);
	}

	static std::shared_ptr<ProgramGroup> mk();

	void use() override;
};
