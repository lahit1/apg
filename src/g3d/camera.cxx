#include<g3d/camera.hxx>
#include <glm/gtc/matrix_transform.hpp>
//#include<glm/ext/matrix_transform.inl>

vec3 yaxis{0, 1, 0};
vec3 xaxis{1, 0, 0};

void Camera::rotate(float radians, vec2 scale) {

	float deltax = radians * scale.y;
	float rotxnew = rotx + deltax;
	if(glm::abs(rotxnew) <= LIMIT_X_ANGLE) {
		rot = glm::rotate(rot, deltax, xaxis); // X ekseni
		rotx = rotxnew;
	} else rotx = glm::sign(rotx) * LIMIT_X_ANGLE;

	rot = glm::rotate(rot, radians * scale.x, yaxis); // Y ekseni
}

void Camera::updateView() {
        view = mat4(1);
        view = glm::translate(view, dist) * rot * glm::translate(view, -pos);
}

void Camera::updateProjection() {
	proj = glm::perspective(fov, aspect, nearPlane, farPlane);
}

void Camera::updateVP() {
	vp = proj * view;
}
