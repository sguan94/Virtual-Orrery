/*
* Geometry.cpp
*
*  Created on: Sep 10, 2018
*      Author: John Hall
*/

#include "Geometry.h"
#include <iostream>
#define PI 3.141592653

Geometry::Geometry() : vao(0), vertexBuffer(0), normalBuffer(0), uvBuffer(0), colorBuffer(0) {
	//vectors are initially empty
	//Pointers are initially null
	//Call RenderingEngine::assignBuffers and RenderingEngine::setBufferData to fully initialize the geometry
	//Overload the constructor for more functionality or create subclasses for specific objects
}

Geometry::~Geometry() {

}

Geometry Geometry::starForger(int textureIndex, int level, float radius, float distanceToParent, float inclineAngle, float rotationSpeed, float revolutionSpeed, bool shading) {

	Geometry sphere;
	
	switch (textureIndex) {
	case 0: InitializeTexture(&sphere.texture, "8k_stars_milky_way.jpg", GL_TEXTURE_2D);; break;
	case 1: InitializeTexture(&sphere.texture, "8k_sun.jpg", GL_TEXTURE_2D);; break;
	case 2: InitializeTexture(&sphere.texture, "8k_mercury.jpg", GL_TEXTURE_2D); break;
	case 3: InitializeTexture(&sphere.texture, "8k_venus.jpg", GL_TEXTURE_2D); break;
	case 4: InitializeTexture(&sphere.texture, "8k_earth_daymap.jpg", GL_TEXTURE_2D); break;
	case 5: InitializeTexture(&sphere.texture, "8k_moon.jpg", GL_TEXTURE_2D); break;
	case 6: InitializeTexture(&sphere.texture, "8k_mars.jpg", GL_TEXTURE_2D); break;
	case 7: InitializeTexture(&sphere.texture, "8k_jupiter.jpg", GL_TEXTURE_2D); break;
	case 8: InitializeTexture(&sphere.texture, "2k_uranus.jpg", GL_TEXTURE_2D); break;
	case 9: InitializeTexture(&sphere.texture, "8k_saturn.jpg", GL_TEXTURE_2D); break;
	case 10: InitializeTexture(&sphere.texture, "2k_neptune.jpg", GL_TEXTURE_2D); break;
	}

	float unitAngle = 180.0f / level;
	glm::vec3 temp;

	for (float currentVerticalAngle = 0; currentVerticalAngle < 180; currentVerticalAngle = currentVerticalAngle + unitAngle) {
		for (float currentHorizontalAngle = 0; currentHorizontalAngle < 360; currentHorizontalAngle = currentHorizontalAngle + unitAngle) {
			
			temp = Geometry::getPoint(radius, currentVerticalAngle, currentHorizontalAngle);
			sphere.verts.push_back(temp);
			sphere.normals.push_back(glm::normalize(temp));
			sphere.uvs.push_back(glm::vec2(1 - currentHorizontalAngle / 360, 1 - currentVerticalAngle / 180));

			temp = Geometry::getPoint(radius, currentVerticalAngle, currentHorizontalAngle + unitAngle);
			sphere.verts.push_back(temp);
			sphere.normals.push_back(glm::normalize(temp));
			sphere.uvs.push_back(glm::vec2(1 - (currentHorizontalAngle + unitAngle) / 360, 1 - currentVerticalAngle / 180));

			temp = Geometry::getPoint(radius, currentVerticalAngle + unitAngle, currentHorizontalAngle + unitAngle);
			sphere.verts.push_back(temp);
			sphere.normals.push_back(glm::normalize(temp));
			sphere.uvs.push_back(glm::vec2(1 - (currentHorizontalAngle + unitAngle) / 360, 1 - (currentVerticalAngle + unitAngle) / 180));

			temp = Geometry::getPoint(radius, currentVerticalAngle, currentHorizontalAngle);
			sphere.verts.push_back(temp);
			sphere.normals.push_back(glm::normalize(temp));
			sphere.uvs.push_back(glm::vec2(1 - currentHorizontalAngle / 360, 1 - currentVerticalAngle / 180));

			temp = Geometry::getPoint(radius, currentVerticalAngle + unitAngle, currentHorizontalAngle);
			sphere.verts.push_back(temp);
			sphere.normals.push_back(glm::normalize(temp));
			sphere.uvs.push_back(glm::vec2(1 - currentHorizontalAngle / 360, 1 - (currentVerticalAngle + unitAngle) / 180));

			temp = Geometry::getPoint(radius, currentVerticalAngle + unitAngle, currentHorizontalAngle + unitAngle);
			sphere.verts.push_back(temp);
			sphere.normals.push_back(glm::normalize(temp));
			sphere.uvs.push_back(glm::vec2(1 - (currentHorizontalAngle + unitAngle) / 360, 1 - (currentVerticalAngle + unitAngle) / 180));
		}
	}

	sphere.drawMode = GL_TRIANGLES;

	sphere.shading = shading;
	sphere.hasParent = false;
	sphere.revolutionSpeed = revolutionSpeed;
	sphere.disToParent = distanceToParent;
	sphere.rotationSpeed = rotationSpeed;
	sphere.inclineAngle = inclineAngle;
	sphere.spinMatrix = glm::mat4();
	sphere.spinMatrix = glm::rotate(sphere.spinMatrix, inclineAngle, glm::vec3(1, 0, 0));

	return sphere;
}

glm::vec3 Geometry::getPoint(float radius, float v, float h) {
	return glm::vec3(	radius * sin(v * PI / 180) * cos(h * PI / 180),
						radius * cos(v * PI / 180),
						radius * sin(v * PI / 180) * sin(h * PI / 180));
}

void Geometry::setParent(Geometry* g) {
	hasParent = true;
	parent = g;
	g->children.push_back(this);
}

void Geometry::spin() {
	spinMatrix = glm::rotate(spinMatrix, rotationSpeed, glm::vec3(0, 1, 0));
}

void Geometry::revolution() {
	if (revolutionAngle >= 360 || revolutionAngle <= -360) {
		revolutionAngle = 0.0f;
	}
	revolutionAngle = revolutionAngle + revolutionSpeed;
	tempRevolutionMatrix = glm::mat4
		(1, 0, 0, 0,
		 0, 1, 0, 0,
		 0, 0, 1, 0,
		 disToParent * cos(revolutionAngle), 0, disToParent * sin(revolutionAngle), 1);
}