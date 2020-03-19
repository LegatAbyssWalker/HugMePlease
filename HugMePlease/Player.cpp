#include "Player.h"

Player::Player(GLWindow& window, glm::vec3 cameraPosition, glm::mat4 projection)
	: Object(window), window(window) {
	// Camera
	camera = Camera(cameraPosition, glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, (MOVEMENT_SPEED / 3), 0.3f);
}

void Player::keyboardUpdate(Movement movement, GLfloat deltaTime) {
	// Camera event updates
	camera.processKeyboard(movement, deltaTime);
}


void Player::update() {
	camera.processMouseMovement(window);
	setPosition(camera.getPosition());
}
