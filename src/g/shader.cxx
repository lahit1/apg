#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<ape/g/shader.hxx>

namespace Shaders {

std::shared_ptr<Shader> create(const GLchar* const* code, GLenum shaderType) {
        std::shared_ptr<Shader> ret = std::make_shared<Shader>();
        ret->ptr = glCreateShader(shaderType);
        glShaderSource(ret->ptr, 1, code, NULL);
        return ret;
}

}
