#pragma once

#include<g/program.hxx>
#include<g/camera.hxx>
#include<g3d/mesh.hxx>
#include<g3d/model.hxx>

namespace RENDERER {

void BEGIN(Camera* c);
void USE(std::shared_ptr<Program> p);
void DRAW(std::shared_ptr<Model> m);
void END(void);
}
