/*
* Scene.cpp
*
*  Created on: Sep 10, 2018
*  Author: John Hall
*/

#include "Scene.h"

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

Scene::Scene(RenderingEngine* renderer, GLFWwindow* window) : renderer(renderer), window(window), theta(0.f) {

	camera = new Camera();

	// radius = (log 2 (real size / 1500)) / 8
	// distance = real distance / 30,000,000
	// starForger:
	// textureIndex, level, radius, distanceToParent, 
	// inclineAngle, rotationSpeed, revolutionSpeed, shading

	space = Geometry::starForger(	0,	180,50.0f,			0.0f,	0.0f,	0.0f,	0.0f,	false);
	sun = Geometry::starForger(		1,	72,	8.86f / 8.0f,	0.0f,	0.01f,	0.0f,	0.0f,	false);
	mercury = Geometry::starForger(	2,	18,	0.7 / 8.0f,		1.9f,	-0.03f,	-0.15f,	0.006f, true);
	venus = Geometry::starForger(	3,	36,	2.01f / 8.0f,	3.3f,	0.02f,	0.1f,	-0.005f, true);
	earth = Geometry::starForger(	4,	36,	2.08f / 8.0f,	4.99f,	0.015f,	-0.1f,	0.004f, true);
	moon = Geometry::starForger(	5,	18,	0.58f/ 8.0f,	0.8f,	-0.01f,	0.02f,	-0.02f,	true);
	moon.setParent(&earth);
	mars = Geometry::starForger(	6,	36,	1.18f / 8.0f,	7.6f,	0.02f,	-0.08f,	-0.002f,true);
	jupiter = Geometry::starForger(	7,	54, 5.6 / 8.0f,		12.0f,	0.03f,	-0.02f,	0.0015f, true);
	saturn = Geometry::starForger(	8,	54, 5.28f / 8.0f,	20.0f,	-0.012f,0.05f,	-0.0012f, true);
	uranus = Geometry::starForger(	9,	54, 4.1f / 8.0f,	28.0f,	0.022f, -0.04f,0.001f, true);
	neptune = Geometry::starForger(	10, 54, 4.0f / 8.0f,	36.0f,	-0.025f,0.045f,	-0.0008f, true);

	mercury.revolutionAngle = 200;
	venus.revolutionAngle = 35;
	earth.revolutionAngle = 88;
	mars.revolutionAngle = 305;
	jupiter.revolutionAngle = 166;
	saturn.revolutionAngle = 233;
	uranus.revolutionAngle = 332;
	neptune.revolutionAngle = 270;

	addGeometry(space);
	addGeometry(sun);
	addGeometry(mercury);
	addGeometry(venus);
	addGeometry(earth);
	addGeometry(moon);
	addGeometry(mars);
	addGeometry(jupiter);
	addGeometry(saturn);
	addGeometry(uranus);
	addGeometry(neptune);

}

void Scene::addGeometry(Geometry g) {

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(g);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(g);

	//Add the triangle to the scene objects
	objects.push_back(g);

}

Scene::~Scene() {

}

void Scene::displayScene(int sec, int speed) {

	if (sec % speed == 0) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i].revolution();
			objects[i].spin();

			if (!objects[i].hasParent) {
				objects[i].revolutionMatrix = objects[i].tempRevolutionMatrix;
			}
			else {
				objects[i].revolutionMatrix = objects[i - 1].tempRevolutionMatrix * objects[i].tempRevolutionMatrix;
			}
		}
	}
	
	
	renderer->RenderScene(objects, window, camera);
}