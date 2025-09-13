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

void ShaderProgram::use() {
	glUseProgram(ptr);
}

std::shared_ptr<ProgramGroup> ProgramGroup::mk() {
	std::shared_ptr<ProgramGroup> ret = std::make_shared<ProgramGroup>();
	return ret;
}

void ProgramGroup::use() {
	c_pr->use();
}
