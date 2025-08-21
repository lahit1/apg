#include<g/camera.hxx>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	updateView();
	updateProjection();
	updateVP();
}

void Camera::updateView() {
	view = glm::lookAt(pos + dist, pos, up);
}

void Camera::updateProjection() {
	proj = glm::perspective(fov, aspect, nearPlane, farPlane);
}

void Camera::updateVP() {
	vp = proj * view;
}
