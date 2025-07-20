#pragma once

#include<g3d/program.hxx>
#include<g3d/camera.hxx>

namespace RENDERER {

void BEGIN(Camera* c);
void USE(Program* p);
void DRAW(Mesh* m);
void END(void);
}
