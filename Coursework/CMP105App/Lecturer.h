#pragma once

#include "Framework/GameObject.h"
#include "TextureManager.h"
#include "Framework/Animation.h"
#include "StageGrid.h"

class Lecturer : public GameObject
{
public:
	Lecturer();
	Lecturer(sf::RenderWindow* hwnd, TextureManager* tm);

	void update(float dt) override;
	sf::Text sizeTextToGrid(sf::Text t, float boardTop, float boardRight, float boardBottom, float boardLeft);
	sf::Text getMessageToDisplay(float boardTop, float boardRight, float boardBottom, float boardLeft);

	sf::RenderWindow* window;
	TextureManager* textMan;
	std::vector<std::string> motivationalMessages;
	int nextMessage;
	sf::Font font;
	float msgDisplayTime;
	float msgDisplayTargetTime;
	Animation speak;
	Animation* currentAnimation;
	float timeAlive;
	float animSpeed;
	int maxSize = 200;
};

