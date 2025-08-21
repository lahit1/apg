#include<g3d/program.hxx>

namespace Programs {
	const char *vpULoc = "vpU",
                *modelULoc = "modelU",
                *normalULoc = "normalU";

        const char 
                *materialAmbientCLoc = "materialAmbientC",
                *materialDiffuseCLoc = "materialDiffuseC",
                *materialSpecularCLoc = "materialSpecularC",
                *materialShininessLoc = "materialShininess";

	const char
                *materialDiffuseTLoc = "materialDiffuseT",
                *materialSpecularTLoc = "materialSpecularT",
                *materialNormalTLoc = "materialNormalT";

        const char *viewPosULoc = "viewPos";

Program* create() {
	Program* ret = new Program();
	ret->ptr = glCreateProgram();
	return ret;
}

}
