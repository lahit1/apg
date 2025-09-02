#include<g/program.hxx>

namespace Programs {
	char *vpULoc = "vpU",
                *modelULoc = "modelU",
                *normalULoc = "normalU",
		*viewPosULoc = "viewPos";
}

std::shared_ptr<Program> Program::mk() {
	std::shared_ptr<Program> ret = std::make_shared<Program>();
	ret->ptr = glCreateProgram();
	return ret;
}
