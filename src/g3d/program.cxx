#include<g3d/program.hxx>

namespace Programs {
	const char *vpULoc = "vpU",
                *modelULoc = "modelU",
                *normalULoc = "normalU";

        const char 
                *materialDiffuseLoc = "material.diffuse",
                *materialSpecularLoc = "material.specular",
                *materialShininessLoc = "material.shininess";

        const char *viewPosULoc = "viewPos";

Program* create() {
	Program* ret = new Program();
	ret->ptr = glCreateProgram();
	return ret;
}

}
