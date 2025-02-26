#pragma once

#include "Framework/GameObject.h"

class Background : public GameObject
{
public:
	Background();

	void handleInput(float dt);
	void setWindow(sf::RenderWindow* wnd);

	sf::Texture bg;
	sf::RenderWindow* window;
	Input* in;
};

