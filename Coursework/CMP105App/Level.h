#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "TextureManager.h"
#include "StageGrid.h"
#include "Player.h"
#include "Lecturer.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm);
	~Level();

	void handleInput(float dt) override;
	void update(float dt);
	void render();
	void reset();
	void resetPlayer();

private:

	// constant declarations
	const float GRID_Y_MAX_PROPORTION = 0.6f;	// how wide, as a proportion of the window, can the grid be
	const float TIME_PER_STEP = 1.0f;	// time for each step (time between claps)
	const float TIME_FOR_ACTION = 0.25f;	// how long (seconds) does the player have to act
	const float TIME_BUFFER = 0.25f;	// time between end of action window and end of step.
	const float RESET_TIME = 1.0f;		// time for 'reset' state where player cannot move.
	const float TIME_TO_DISPLAY_ALERT = 0.5f;	// how long (seconds) an alert is displayed for.

	// possible actions chosen.
	enum actions {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE, 
		FAIL
	};

	TextureManager* textMan;
	GameObject gridBoard;
	Player player;
	GameObject target;
	GameObject moveSelected;
	GameObject progressInStep;
	GameObject targetZone;
	GameObject progressInStepBG;
	GameObject levelBG;
	GameObject controlBG;
	std::pair<int, int> playerPosition;
	actions selectedAction;
	std::vector<GameObject> indicators;
	sf::Font font;
	std::vector<sf::Text> controls;
	sf::Text alert;
	StageGrid grid;
	Lecturer lecturer;
	sf::Vector2i start = { 0,3 };
	sf::Vector2i end = { 0, 8 };
	sf::Vector2i checkPoint = { 19, 5 };
	sf::Vector2i boardDimensions{ 20,10 };
	bool checkPointEnabled;
	float timeInStep = 0.f;
	bool soundPlayed = false;
	float cellDim;
	int beatsPlayed = 0;
	float damagedTimer = 0.f;
	float alertHasBeenActiveFor = TIME_TO_DISPLAY_ALERT;
	float boardTop, boardRight, boardBottom, boardLeft;
	
	// analytics values
	float timeTaken = 0.f;
	int misses = 0;
	int deaths = 0;
};

