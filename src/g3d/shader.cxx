#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<g3d/shader.hxx>

namespace Shaders {

Shader *first, *last;

Shader* create(const GLchar* const* code, GLenum shaderType) {
        Shader *ret = new Shader();
        if(first == nullptr) first = last = ret;
        else {
                last->next = ret;
                last = ret;
        }

        ret->ptr = glCreateShader(shaderType);
        glShaderSource(ret->ptr, 1, code, NULL);
        return ret;
}

void freeAll() {
        Shader *cur=first, *ref;
        while(cur != nullptr) {
                ref = cur;
                cur = ref->next;
                ref->del(); // Delete opengl object
                delete ref;
        }
}

}
