#include<g3d/renderable.hxx>
#include<g3d/renderer.hxx>

namespace RENDERER {

void BEGIN(Camera* p) {};
void RENDER(void) {};
void END(void) {};

void Pool::link(Ball *b) {
	if(!start) start = end = b;
	if(end == b) return;
	else {
		end->next = b;
		end = b;
	}
	b->next = nullptr;
}

void Pool::unlink(Ball *b) {
	b->renderable = nullptr;
}

}
