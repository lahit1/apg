#pragma once

#include<g3d/program.hxx>
#include<g3d/camera.hxx>

namespace RENDERER {

void BEGIN(Camera* p);
void RENDER(void);
void END(void);
}
