/*
* Geometry.h
*	Class for storing geometry
*  Created on: Sep 10, 2018
*      Author: John Hall
*/

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Geometry {
public:
	Geometry();
	virtual ~Geometry();
	static Geometry starForger(int textureIndex, int level, float radius, float distanceToParent, float inclineAngle, float rotationSpeed, float revolutionSpeed, bool shading);
	static glm::vec3 getPoint(float radius, float theta, float phi);

	//Data structures for storing vertices, normals colors and uvs
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec2> uvs;

	//Pointers to the vao and vbos associated with the geometry
	GLuint vao;
	GLuint vertexBuffer;
	GLuint normalBuffer;
	GLuint uvBuffer;
	GLuint colorBuffer;

	//Draw mode for how OpenGL interprets primitives
	GLuint drawMode;

	//Texture for this geometry object
	MyTexture texture;

	//Tree structure for calculate world coordinate
	Geometry* parent;
	bool hasParent;
	std::vector<Geometry*> children;
	glm::mat4 spinMatrix;
	glm::mat4 tempRevolutionMatrix;
	glm::mat4 revolutionMatrix;

	bool shading;

	//Self rotation speed
	float inclineAngle;
	float rotationSpeed;

	//Revolution
	float revolutionSpeed;
	float revolutionAngle;
	float disToParent;

	void setParent(Geometry* g);
	void spin();
	void revolution();

};

#endif /* GEOMETRY_H_ */