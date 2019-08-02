#include "Camera.h"
#include <iostream>
#define PI 3.141592653f
using namespace glm;

Camera::Camera() {
	radius = 45.0f;
	theta = 0.0f;
	phi = 0.0f;

	updatePosition();
}

Camera::Camera(float r, float t, float p) {
	radius = r;
	theta = t;
	phi = p;

	updatePosition();
}

void Camera::updatePosition() {

	if (theta >= 360)
		theta = theta - 360;
	if (theta <= -360)
		theta = theta + 360;

	if (phi >= 360)
		phi = phi - 360;
	if (phi <= -360)
		phi = phi + 360;

	pos = vec3(	radius * cos(theta * PI / 180) * cos(phi * PI / 180),
				radius * sin(theta * PI / 180),
				radius * cos(theta * PI / 180) * sin(phi * PI / 180)
	);
	//dir = vec3(0.0f, 0.0f, 0.0f) - pos;

	if (cos(theta * PI / 180) > 0)
		up = vec3(0, 1, 0);
	else
		up = vec3(0, -1, 0);
}

void Camera::moveRight() {
	phi -= 1;
	updatePosition();
}

void Camera::moveLeft() {
	phi += 1;
	updatePosition();
}

void Camera::moveUp() {
	theta += 1;
	updatePosition();
}

void Camera::moveDown() {
	theta -= 1;
	updatePosition();
}

void Camera::focusStar(glm::mat4 matrix) {
	vec4 newPos = (matrix * vec4(pos.x, pos.y, pos.z, 1.0f));
	//pos = vec3(newPos.x, newPos.y, newPos.z);
	std::cout << newPos.x << ", " << newPos.y << ", " << newPos.z << std::endl;
	std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
}