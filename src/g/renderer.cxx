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
	for(auto ufor : mat->uniforms_f)
		if(ufor.first)
		        ufor.second.binder_funcfv(ufor.first, 1, ufor.second.value);

	int i;
	for(auto tex : mat->textures)
		if(tex.first) {
			glUniform1i(tex.first, i);
	                tex.second.bind(i++);
		}

	glUniform3fv(c_p->viewPosULoc_ptr, 1, glm::value_ptr(c_cam->pos));

	for(Mesh* m: mod->meshes) {
		glBindVertexArray(m->VAO);
	        glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);
	}
}

void END(void) {};

}
