#include<g3d/renderable.hxx>
#include<g3d/renderer.hxx>

namespace RENDERER {

Camera* c_cam;

void BEGIN(Camera* p) {
	c_cam = p;
};

void END(void) {};

}
