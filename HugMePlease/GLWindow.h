#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "GL/glew.h"

#include "FileLocations.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class GLWindow {
	public:
		GLWindow() = default;
		~GLWindow();

		void initWindow();
		void swapBuffers();
	
		bool isOpen() { return window.isOpen(); }

		sf::Window& getWindow() { return window; }

	private:
		sf::Window window;
};

