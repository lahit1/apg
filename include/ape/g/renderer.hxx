#pragma once

#include<ape/g/program.hxx>
#include<ape/g/camera.hxx>
#include<ape/g3d/mesh.hxx>
#include<ape/g3d/model.hxx>

namespace RENDERER {

void BEGIN(Camera* c);
void USE(std::shared_ptr<Program> p);
void DRAW(std::shared_ptr<Model> m);
void END(void);
}
