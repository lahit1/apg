#include<g3d/program.hxx>

namespace Programs {

Program* create() {
	Program* ret = new Program();
	ret->ptr = glCreateProgram();
	return ret;
}

}
