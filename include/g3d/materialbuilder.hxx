#include <g3d/material.hxx>
#include <g/program.hxx>

class MaterialBuilder {

	std::unordered_map<std::string, std::string> reps;
	std::unordered_map<std::string, uniformfv> loads_uf;
	std::unordered_map<std::string, std::shared_ptr<Texture>> loads_tex;

public:
        inline MaterialBuilder* add(std::string target, glm::vec3 value) {
                loads_uf[target] = { glUniform3fv, glm::value_ptr(value) };
                return this;
        }
        inline MaterialBuilder* add(std::string target, glm::vec2 value) {
                loads_uf[target] = uniformfv{ glUniform2fv, glm::value_ptr(value) };
                return this;
        }
        inline MaterialBuilder* add(std::string target, float value) {
                loads_uf[target] = uniformfv{ glUniform1fv, new float(value) };
                return this;
        }

        inline MaterialBuilder* add(std::string target, std::shared_ptr<Texture> tex) {
                loads_tex[target] = tex;
                return this;
        }

	inline MaterialBuilder* rep(std::string first, std::string second) {
		reps[first] = second;
		return this;
	}

	inline Material* build(Program* p) {
		Material *mat = new Material();
		for(auto u: loads_uf) {
			std::string u_name;
			if(reps.find(u.first) != reps.end())
				u_name = reps[u.first];
			else u_name = u.first;
			mat->uniforms_f[glGetUniformLocation(p->ptr, u_name.c_str())] = u.second;
		}
		for(auto tex: loads_tex) {
			std::string u_name;
			if(reps.find(tex.first) != reps.end())
                                u_name = reps[tex.first];
                        else u_name = tex.first;
			mat->textures[glGetUniformLocation(p->ptr, u_name.c_str())] = tex.second;
		}
		return mat;
	}
};
