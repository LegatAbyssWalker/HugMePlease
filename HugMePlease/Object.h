#pragma once

#include "Mesh.h"
#include "Program.h"
#include "Variables.h"
#include "State.h"
#include "Model.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

struct Object {
	public:
		Object() = default;
		Object(GLWindow& window) : window(window) { program = std::make_unique<Program>(BASIC_VERTEX_SHADER, BASIC_FRAGMENT_SHADER); }

		void setPosition(glm::vec3 position) { this->position = position; }
		void setScale(glm::vec3 scaleValue) { this->scaleValue = scaleValue; }
		
		void move(glm::vec3 offset) { setPosition(glm::vec3(getPosition().x + offset.x, getPosition().y + offset.y, getPosition().z + offset.z)); }

		glm::vec3 getPosition() const { return position; }
		glm::vec3 getSize() const { return scaleValue; }

	protected:
		GLWindow& window;
		std::unique_ptr<Program> program = nullptr;

		glm::f32 rotationAngle = 0;
		glm::vec3 rotationAxis = glm::vec3(0, 1, 0);

		glm::vec3 position = glm::vec3(0);
		glm::vec3 scaleValue = SCALE_VALUE;
};
