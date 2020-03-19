#include "Friends.h"

Friends::Friends(GLWindow& window, std::string const& filePath) 
	: model(filePath, window), Object(window) {
}

void Friends::update(GLfloat deltaTime, glm::vec3 playerPosition, glm::vec3 playerUp) {
	this->playerXYZ = playerPosition;
	this->playerUp = playerUp;
}

void Friends::render(const glm::mat4 viewMatrix, const glm::mat4& projection) {
	program->useProgram();

	glm::mat4 matrix = glm::inverse(glm::lookAt(getPosition(), playerXYZ, playerUp));
	matrix[0][0] = -matrix[0][0];
	matrix[0][1] = -matrix[0][1];
	matrix[0][2] = -matrix[0][2];
	matrix[2][0] = -matrix[2][0];
	matrix[2][1] = -matrix[2][1];
	matrix[2][2] = -matrix[2][2];


	// Model matrix
	glm::mat4 modelMatrix(1.f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, scaleValue);
	
	// Uniforms
	program->setMat4("model", matrix);
	program->setMat4("view", viewMatrix);
	program->setMat4("projection", projection);

	// Model rendering
	model.renderModel(program);
}

void Friends::calculateMovement() {
	glm::vec3 playerPosition = playerXYZ;
	glm::vec3 friendPosition = getPosition();

	directionalVector = friendPosition - playerPosition;
}

void Friends::moveFriend() {
	move(glm::normalize(directionalVector) * glm::vec3(0.02));
}

bool Friends::isFriendDead() {
	if (isDead) {
		return true;
	}
	return false;
}

void Friends::setDead() {
	isDead = true;
}
