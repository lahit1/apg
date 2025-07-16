#pragma once

#include<istream>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Material {
	GLuint diffuseTexture = 0;
        GLuint specularTexture = 0;
        GLuint normalTexture = 0;

        glm::vec3 diffuseColor = glm::vec3(1.0f);
        glm::vec3 specularColor = glm::vec3(1.0f);
        float shininess = 32.0f;
};


namespace Materials {


GLuint loadTexture(std::istream& s);


}
