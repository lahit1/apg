#include<g3d/renderable.hxx>
#include<g3d/model.hxx>
#include<g3d/renderer.hxx>
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

void DRAW(Model* m) {
	glm::mat4 mvp = c_cam->vp * m->matrix;

	glUniformMatrix4fv(c_p->mvpULoc_ptr, 1, GL_FALSE, glm::value_ptr(mvp));

        glBindVertexArray(m->VAO);

        glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);
}

void END(void) {};

}
