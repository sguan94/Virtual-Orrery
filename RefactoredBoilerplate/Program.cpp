/*
* Program.cpp
*
*  Created on: Sep 10, 2018
*      Author: John Hall
*/

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"

static bool button_down = false;
double xpos, ypos, newXpos, newYpos;
int speed = 5;

Program::Program() {
	setupWindow();
}

Program::~Program() {
	//Must be cleaned up in the destructor because these are allocated to the heap
	delete renderingEngine;
	delete scene;
}

void Program::start() {
	renderingEngine = new RenderingEngine();
	scene = new Scene(renderingEngine, window);

	//Main render loop
	while (!glfwWindowShouldClose(window)) {

		sec++;

		if (button_down) {
			Scene* s = getScene();
			glfwGetCursorPos(window, &newXpos, &newYpos);
			if (newXpos - xpos > 0) {
				if (s->camera->up.y == 1) {
					s->camera->moveLeft();
				}
				else if (s->camera->up.y == -1) {
					s->camera->moveRight();
				}
				
				xpos = newXpos;
			}else if (newXpos - xpos < 0) {
				if (s->camera->up.y == 1) {
					s->camera->moveRight();
				}
				else if (s->camera->up.y == -1) {
					s->camera->moveLeft();
				}
				
				xpos = newXpos;
			}
			if (newYpos - ypos > 0) {
				s->camera->moveUp();
				ypos = newYpos;
			}else if (newYpos - ypos < 0) {
				s->camera->moveDown();
				ypos = newYpos;
			}
		}

		scene->displayScene(sec, speed);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 1600;
	int height = 900;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetWindowUserPointer(window, this);
	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}



void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	Program* p = (Program*)glfwGetWindowUserPointer(window);
	Scene* s = p->getScene();
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		s->camera->moveLeft();
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		s->camera->moveRight();
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		s->camera->moveUp();
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		s->camera->moveDown();
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		if (speed > 1) {
			speed--;
		}
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (speed < 10) {
			speed++;
		}
	}
	/*
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		std::cout << s->mars.verts[0].x << std::endl;
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << s->mars.tempRevolutionMatrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
		//s->camera->focusStar(s->mars.revolutionMatrix);
	}
	*/
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	Program* p = (Program*)glfwGetWindowUserPointer(window);
	Scene* s = p->getScene();
	if (yoffset == 1 && s->camera->radius > 1.0f) {
		s->camera->radius -= 0.5f;
		s->camera->updatePosition();
	}
	else if (yoffset == -1 && s->camera->radius < 49.0f) {
		s->camera->radius += 0.5f;
		s->camera->updatePosition();
	}
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (GLFW_PRESS == action) {
			glfwGetCursorPos(window, &xpos, &ypos);
			button_down = true;
		}
		else if (GLFW_RELEASE == action) {
			button_down = false;
		}
	}
}