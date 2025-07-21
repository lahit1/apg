#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <g3d/texture.hxx>


struct Material {
	Texture *diffuseTexture, *specularTexture, *normalTexture;

        glm::vec3 diffuseColor = glm::vec3(1.0f);
        glm::vec3 specularColor = glm::vec3(1.0f);
        float shininess = 32.0f;
};
