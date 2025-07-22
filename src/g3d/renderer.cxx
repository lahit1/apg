#include<g3d/renderable.hxx>
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
/*
void DRAW(Mesh* m) {
	glUniformMatrix4fv(c_p->vpULoc_ptr, 1, GL_FALSE, glm::value_ptr(c_cam->vp));

        glBindVertexArray(m->VAO);
        glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);
}
*/

void DRAW(Model* mod) {
        glUniformMatrix4fv(c_p->vpULoc_ptr, 1, GL_FALSE, glm::value_ptr(c_cam->vp));
        glUniformMatrix4fv(c_p->modelULoc_ptr, 1, GL_FALSE, glm::value_ptr(mod->matrix));
        glUniformMatrix4fv(c_p->normalULoc_ptr, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(mod->matrix))));

	Material* mat = mod->material;
        glUniform3fv(c_p->materialDiffuseLoc_ptr, 1, glm::value_ptr(mat->diffuseColor));
        glUniform3fv(c_p->materialSpecularLoc_ptr, 1, glm::value_ptr(mat->specularColor));
        glUniform1f(c_p->materialShininessLoc_ptr, mat->shininess);

	glUniform3fv(c_p->viewPosULoc_ptr, 1, glm::value_ptr(c_cam->pos));

	mod->reset();
	while(mod->isAvailable()) {
		Mesh* m = mod->next();

		glBindVertexArray(m->VAO);
	        glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);
	}
}

void END(void) {};

}
