#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <g3d/texture.hxx>
#include <unordered_map>

struct uniformfv {
	void (*binder_funcfv)(
		GLint location,
		GLsizei count,
		const GLfloat *value);

	GLfloat *value;

	inline uniformfv() = default;

	inline uniformfv(void (*binder_funcfv)(
		GLint location,
		GLsizei count,
		const GLfloat *value), GLfloat *value) : value(value), binder_funcfv(binder_funcfv) {}
};

struct Material {
	std::unordered_map<GLuint, uniformfv> uniforms_f;
	std::unordered_map<GLuint, Texture> textures;

	inline Material* add(GLuint target, glm::vec3 value) {
		uniforms_f[target] = { glUniform3fv, glm::value_ptr(value) };
		return this;
	}
	inline Material* add(GLuint target, glm::vec2 value) {
		uniforms_f[target] = uniformfv{ glUniform2fv, glm::value_ptr(value) };
		return this;
	}
	inline Material* add(GLuint target, float value) {
		uniforms_f[target] = uniformfv{ glUniform1fv, new float(value) };
		return this;
	}

	inline Material* add(GLuint target, Texture tex) {
		textures[target] = tex;
		return this;
	}
};
