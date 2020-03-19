#pragma once

#include "State.h"
#include "Camera.h"
#include "GLWindow.h"
#include "Variables.h"
#include "Program.h"
#include "Mesh.h"
#include "FileLocations.h"
#include "Object.h"

#include <iostream>
#include <memory>

class Player : public Object {
	public:
		Player(GLWindow& window, glm::vec3 cameraPosition, glm::mat4 projection);

		void keyboardUpdate(Movement movement, GLfloat deltaTime);

		void update();

		glm::mat4 getViewMatrix() { return camera.calculateViewMatrix(); }
		const glm::vec3 getCameraPosition() { return camera.getPosition(); }

		glm::vec3 getUp() const { return camera.getUp(); }
		glm::f32 getYaw() const { return camera.getYaw(); }

	private:
		Movement movement;
		GLWindow& window;
		Model model;

		Camera camera;
		GLfloat lastX = window.getWindow().getSize().x / 2.f;
		GLfloat lastY = window.getWindow().getSize().y / 2.f;
		bool firstMouse = true;
};
