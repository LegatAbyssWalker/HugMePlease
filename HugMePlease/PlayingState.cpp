#include "PlayingState.h"

PlayingState::PlayingState(StateMachine& machine, GLWindow& window, bool replace)
	: State(machine, window, replace), window(window) {


	// Terrain
	terrain = std::make_unique<Terrain>(window, PLATFORM_MODEL_LOCATION);
	terrain->setPosition(glm::vec3(0, 0, 0));
	terrainScaleValue = glm::vec3(10, 1, 10);
	terrain->setScale(terrainScaleValue);
	
	// Lava
	lava = std::make_unique<Lava>(window, LAVA_MODEL_LOCATION);
	lava->setPosition(glm::vec3(0, -10, 0));
	lava->setScale(glm::vec3(100, 1, 100));

	GLfloat entityY = 1.4;

	// Player
	player = std::make_unique<Player>(window, glm::vec3(0, entityY, 0), getProjectionMatrix());

	// Friends
	for (int x = 0; x < friendsAmount; x++) {
		glm::vec3 friendsPosition;
		friendsPosition.x = random[0].getInt(-9, 9);
		friendsPosition.z = random[1].getFloat(-9, 9);
		friendsPosition.y = entityY;

		friendsVector.emplace_back(new Friends(window, FRIEND_MODEL_LOCATION));
		friendsVector[x]->setPosition(friendsPosition);
	}

}

void PlayingState::keyboardInputs(sf::Keyboard::Key& key, bool isPressed) {
	if (key == sf::Keyboard::Escape) { machine.quit(); }
}

void PlayingState::checkWin() {
	if (friendsVector.size() <= 0) {
		setSad = true;
	}
}

void PlayingState::removeEntities() {
	// Removing entities (primarily Friends)
	auto friendsEnd = std::remove_if(friendsVector.begin(), friendsVector.end(), [](std::unique_ptr<Friends>& friends) {
		return friends->isFriendDead();
	});
	friendsVector.erase(friendsEnd, friendsVector.end());
}

bool PlayingState::outOfBounds(std::unique_ptr<Friends>& friends) {
	if (friends->getPosition().x >= terrainScaleValue.x || friends->getPosition().x <= -terrainScaleValue.x ||
		friends->getPosition().z >= terrainScaleValue.z || friends->getPosition().z <= -terrainScaleValue.z) {
		return true;
	}
	return false;
}

void PlayingState::updateEvents() {
	while (window.getWindow().pollEvent(sfEvent)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { player->keyboardUpdate(Movement::FORWARD,  deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { player->keyboardUpdate(Movement::LEFT,     deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { player->keyboardUpdate(Movement::BACKWARD, deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { player->keyboardUpdate(Movement::RIGHT,    deltaTime); }

		auto keyCode = sfEvent.key.code;

		switch (sfEvent.type) { 
			case sf::Event::Closed:
				machine.quit();
				break;  

			case sf::Event::KeyPressed:
				keyboardInputs(keyCode, true);
				break;

			case sf::Event::KeyReleased:
				keyboardInputs(keyCode, false);
				break;
			}
	}
}

void PlayingState::update() {
	GLfloat now = clock.getElapsedTime().asSeconds();
	deltaTime = now - lastFrame;
	lastFrame = now;

	// Player
	player->update();

	// Friends
	for (auto& friends : friendsVector) {
		friends->update((GLfloat)deltaTime, player->getPosition(), player->getUp());
		friends->calculateMovement();

		// Checks vector length
		if (friends->getVectorLength() < friends->getBoundaryIndex(2.0, 5.0)) { friends->moveFriend(); }

		// Checks if friends are out of bounds
		if (outOfBounds(friends) == true) { friends->setDead(); }	
	}

	// Game checks
	checkWin();
	removeEntities();
}

void PlayingState::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!setSad) { glClearColor(0.f, 0.f, 0.1f, 1.f); }
	else { glClearColor(1.f, 0.2f, 0.f, 1.f); }

	terrain->render(player->getViewMatrix(), getProjectionMatrix());
	lava->render(player->getViewMatrix(), getProjectionMatrix());

	for (auto& friends : friendsVector) { friends->render(player->getViewMatrix(), getProjectionMatrix()); }

	window.swapBuffers();
}
