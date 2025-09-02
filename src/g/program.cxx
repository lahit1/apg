#include<g/program.hxx>

namespace Programs {
	const char *vpULoc = "vpU",
                *modelULoc = "modelU",
                *normalULoc = "normalU",
		*viewPosULoc = "viewPos";
}

Program* Program::create() {
	Program* ret = new Program();
	ret->ptr = glCreateProgram();
	return ret;
}
