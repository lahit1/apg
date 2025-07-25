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
	if(c_p->materialDiffuseCLoc_ptr)
	        glUniform3fv(c_p->materialDiffuseCLoc_ptr, 1, glm::value_ptr(mat->diffuseColor));
	if(c_p->materialSpecularCLoc_ptr)
	        glUniform3fv(c_p->materialSpecularCLoc_ptr, 1, glm::value_ptr(mat->specularColor));
	if(c_p->materialShininessLoc_ptr)
	        glUniform1f(c_p->materialShininessLoc_ptr, mat->shininess);

	if(c_p->materialDiffuseTLoc_ptr) {
                glUniform1i(c_p->materialDiffuseTLoc_ptr, 0);
		mat->diffuseTexture.bind(0);
	}
        if(c_p->materialSpecularTLoc_ptr) {
                glUniform1i(c_p->materialSpecularTLoc_ptr, 1);
		mat->specularTexture.bind(1);
	}
        if(c_p->materialNormalTLoc_ptr) {
                glUniform1i(c_p->materialNormalTLoc_ptr, 2);
		mat->normalTexture.bind(2);
	}

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
