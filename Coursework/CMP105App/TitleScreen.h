#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Framework/BaseLevel.h"


class TitleScreen : BaseLevel {
public:
	TitleScreen();
	TitleScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm);
	~TitleScreen();
	void setSelectedMode(int selectedMode);
	int  getSelectedMode();

	void handleInput(float dt) override;
	void update(float dt);
	void render();

	// Default functions for rendering to the screen.

	// Default variables for level class.
	TextureManager* textMan;

	GameObject fan;			// sadBear
	GameObject bg;
	sf::Text explanationText;
	sf::Text titleText;
	sf::Text singleRunText;
	sf::Text difficultyText;
	sf::Font montsFont;
	int selectedMode;

	void checkDifficulty();

	float animTimer;
	
	

};