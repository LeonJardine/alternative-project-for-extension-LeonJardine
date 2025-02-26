#pragma once

#include <SFML/Graphics.hpp>
#include "Random"
#include "TextureManager.h"
#include "Framework/GameObject.h"

class StageGrid
{
public:
	StageGrid();
	StageGrid(sf::Vector2i dimensions, float cellSize, sf::Vector2f position, sf::Vector2i start, sf::Vector2i end, sf::Vector2i cp, int stage, TextureManager* tm);

	enum cellState
	{
		SAFE,
		PIT,			// a hazard that does not move.
		HAZARD_UP,
		HAZARD_DOWN,
		HAZARD_LEFT,
		HAZARD_RIGHT,
		START,
		END,
		CHECKPOINT
	};

	void update(int frames);
	void render(sf::RenderWindow* wnd, bool cp_on);
	bool playerHit(std::pair<int, int> pos);

private:
	TextureManager* textMan;
	std::vector<std::vector<cellState>> grid;
	std::vector<std::vector<GameObject>> board;
	float cellSize;
	sf::Vector2f position;
};


