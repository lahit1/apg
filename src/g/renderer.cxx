#include<ape/g3d/renderable.hxx>
#include<ape/g/renderer.hxx>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace RENDERER {

Camera* c_cam;
std::shared_ptr<Program> c_p;

void BEGIN(Camera* c) {
	c_cam = c;
};

void USE(std::shared_ptr<Program> p) {
	p->use();
	c_p = p;
}

void DRAW(std::shared_ptr<Model> mod) {
        glUniformMatrix4fv(c_p->vpULoc_ptr(), 1, GL_FALSE, glm::value_ptr(c_cam->vp));

	glUniform3fv(c_p->viewPosULoc_ptr(), 1, glm::value_ptr(c_cam->pos));

	mod->render(c_p);
}

void END(void) {};

}
