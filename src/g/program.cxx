#include<ape/g/program.hxx>

namespace Programs {
	char *vpULoc = "vpU",
                *modelULoc = "modelU",
                *normalULoc = "normalU",
		*viewPosULoc = "viewPos";
}

std::shared_ptr<ShaderProgram> ShaderProgram::mk() {
	std::shared_ptr<ShaderProgram> ret = std::make_shared<ShaderProgram>();
	ret->ptr = glCreateProgram();
	return ret;
}
GLuint ShaderProgram::vpULoc_ptr() {
	return _vpULoc_ptr;
}
GLuint ShaderProgram::modelULoc_ptr() {
	return _modelULoc_ptr;
}
GLuint ShaderProgram::normalULoc_ptr() {
	return _normalULoc_ptr;
}
GLuint ShaderProgram::viewPosULoc_ptr() {
	return _viewPosULoc_ptr;
}

void ShaderProgram::use() {
	glUseProgram(ptr);
}



std::shared_ptr<ProgramGroup> ProgramGroup::mk() {
	std::shared_ptr<ProgramGroup> ret = std::make_shared<ProgramGroup>();
	return ret;
}

GLuint ProgramGroup::vpULoc_ptr() { return c_pr->vpULoc_ptr();};
GLuint ProgramGroup::modelULoc_ptr() { return c_pr->modelULoc_ptr();};
GLuint ProgramGroup::normalULoc_ptr() { return c_pr->normalULoc_ptr();};
GLuint ProgramGroup::viewPosULoc_ptr() { return c_pr->viewPosULoc_ptr();};

void ProgramGroup::use() {
	c_pr->use();
}
