#pragma once

#include<g/program.hxx>
#include<g/camera.hxx>
#include<g3d/mesh.hxx>
#include<g3d/model.hxx>

namespace RENDERER {

void BEGIN(Camera* c);
void USE(Program* p);
void DRAW(Mesh* m);
void DRAW(Model* m);
void END(void);
}
