
#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

class Camera {
public:

	float radius, theta, phi;
	glm::vec3 pos, dir, up;

	Camera();
	Camera(float r, float t, float p);
	void updatePosition();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	void focusStar(glm::mat4 matrix);

};

#endif