#include<g3d/camera.hxx>
#include <glm/gtc/matrix_transform.hpp>
//#include<glm/ext/matrix_transform.inl>

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
