/*
* Scene.h
*	Class for storing objects in a scene
*  Created on: Sep 10, 2018
*      Author: cb-ha
*/

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "Geometry.h"
#include "Camera.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer, GLFWwindow* window);
	virtual ~Scene();

	//Send geometry to the renderer
	void displayScene(int sec, int speed);

	float theta;
	Camera* camera;

	Geometry space;
	Geometry sun;
	Geometry mercury;
	Geometry venus;
	Geometry earth;
	Geometry moon;
	Geometry mars;
	Geometry jupiter;
	Geometry saturn;
	Geometry uranus;
	Geometry neptune;

private:
	RenderingEngine * renderer;
	GLFWwindow* window;

	//list of objects in the scene
	std::vector<Geometry> objects;

	void addGeometry(Geometry g);

};

#endif /* SCENE_H_ */
