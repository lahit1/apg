#include<g3d/renderable.hxx>
#include<g/renderer.hxx>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace RENDERER {

Camera* c_cam;
Program* c_p;

void BEGIN(Camera* c) {
	c_cam = c;
};

void USE(Program* p) {
	glUseProgram(p->ptr);
	c_p = p;
}

void DRAW(std::shared_ptr<Model> mod) {
        glUniformMatrix4fv(c_p->vpULoc_ptr, 1, GL_FALSE, glm::value_ptr(c_cam->vp));
        glUniformMatrix4fv(c_p->modelULoc_ptr, 1, GL_FALSE, glm::value_ptr(mod->matrix));
        glUniformMatrix4fv(c_p->normalULoc_ptr, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(mod->matrix))));

	glUniform3fv(c_p->viewPosULoc_ptr, 1, glm::value_ptr(c_cam->pos));

	mod->render();
}

void END(void) {};

}
