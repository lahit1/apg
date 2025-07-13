#include<g3d/renderable.hxx>
#include<g3d/model.hxx>
#include<g3d/renderer.hxx>

namespace RENDERER {

Camera* c_cam;

void BEGIN(Camera* p) {
	c_cam = p;
};

void DRAW(Model* m) {
        glBindVertexArray(m->VAO);
        glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);
}

void END(void) {};

}
