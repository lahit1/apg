#include<g/program.hxx>

namespace Programs {
	char *vpULoc = "vpU",
                *modelULoc = "modelU",
                *normalULoc = "normalU",
		*viewPosULoc = "viewPos";
}

Program* Program::create() {
	Program* ret = new Program();
	ret->ptr = glCreateProgram();
	return ret;
}
