#pragma once

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include <iostream>
#include <fstream>
#include <array>
#include <memory>
#include <vector>
#include <array>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "FileLocations.h"
#include "Variables.h"
#include "GLWindow.h"
#include "Random.h"

#include "Player.h"
#include "Terrain.h"
#include "Friends.h"
#include "Lava.h"


class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, GLWindow& window, bool replace = true);

		void keyboardInputs(sf::Keyboard::Key& key, bool isPressed);

		void checkWin();
		void removeEntities();

		bool outOfBounds(std::unique_ptr<Friends>& friends);
	
		void updateEvents();
		void update();
		void render();

		glm::mat4 getProjectionMatrix() { return glm::perspective(glm::radians(45.f), 
			(GLfloat)window.getWindow().getSize().x / window.getWindow().getSize().y, 0.1f, 100.f); }

	private:

		int friendsAmount = 20;

		glm::vec3 terrainScaleValue;

		GLWindow& window;
		sf::Event sfEvent;
		sf::Clock clock;
		GLfloat deltaTime = 0, lastFrame = 0;
		bool setSad = false;

		std::array<Random<>, 2> random;
		std::unique_ptr<Player> player = nullptr;
		std::unique_ptr<Terrain> terrain = nullptr;
		std::unique_ptr<Lava> lava = nullptr;
		std::vector<std::unique_ptr<Friends>> friendsVector;
};
