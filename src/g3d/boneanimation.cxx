#include <ape/g3d/boneanimation.hxx>
#include <glm/gtc/matrix_transform.hpp>

constexpr glm::vec3 zaxis{0, 0, 1};
constexpr glm::vec3 yaxis{0, 1, 0};
constexpr glm::vec3 xaxis{1, 0, 0};

glm::mat4 BoneAnimation::interpolate(float current_time) {
	size_t loop_count = keyframes.size() - 1;
	for(size_t i; i < loop_count; // we'll gonna use a pre defined variable instead of direct call.
					// That should decrase jump table, or i don't know
					i++) {
		KeyFrame &fi = keyframes[i], &se = keyframes[i + 1];
		if(fi.time < current_time && se.time > current_time) {
			float elapsed = (current_time - fi.time) / (se.time - fi.time);

			glm::vec3 pos = (se.pos - fi.pos) * elapsed;
			glm::vec3 rot = (se.rot - fi.rot) * elapsed;
			glm::vec3 sca = (se.sca - fi.sca) * elapsed;

			glm::mat4 model_mat(1);

			model_mat = glm::translate(model_mat, pos);

			model_mat = glm::rotate(model_mat, rot.x, xaxis);
			model_mat = glm::rotate(model_mat, rot.y, yaxis);
			model_mat = glm::rotate(model_mat, rot.z, zaxis);

			model_mat = glm::scale(model_mat, sca);

			return model_mat;
		}
	}

	return glm::mat4(1);
}
