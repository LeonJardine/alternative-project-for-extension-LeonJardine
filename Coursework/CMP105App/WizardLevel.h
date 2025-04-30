#pragma once
#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "TextureManager.h"
#include "StageGrid.h"
#include "Player.h"
#include "LecturEH.h"
#include "TitleScreen.h"
#include <random>
#include <algorithm>

class WizardLevel : public BaseLevel
{
public:
	WizardLevel(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm, int stage);
	~WizardLevel();

	void update(float dt) override;
	void handleInput(float dt) override;
	void render() override;

	void selectedmode(int selectedmode, bool modechange);
	void randomiseControls();

	void reset();
	void resetPlayer();

private:
	enum actions {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
		FAIL
	};

	enum modes {
		EASY,
		NORMAL,
		HARD
	};

	int selectedMode;
	TextureManager* textMan;
	LecturEH* lecturer;
	StageGrid grid;
	Player player;
	GameObject gridBoard;
	GameObject target;
	GameObject moveSelected;
	GameObject progressInStep;
	GameObject targetZone;
	GameObject progressInStepBG;
	GameObject levelBG;
	GameObject controlBG;
	TitleScreen title;
	std::pair<int, int> playerPosition;
	actions selectedAction;
	actions lastAction;
	std::vector<GameObject> indicators;
	sf::Font font;
	std::vector<sf::Text> controls;
	sf::Vector2i start = { 0,0 };
	sf::Vector2i end = { 19, 9 };
	sf::Vector2i checkPoint{ 10, 4 };
	sf::Vector2i manMadeCheckPoint{ 19, 0 };
	sf::Vector2i boardDimensions{ 20,10 };
	sf::Vector2i skipCherry = { 13,7 };
	bool checkPointEnabled = false;
	bool manMadeEnabled = false;
	bool easyMode;
	bool hardMode;
	bool stepFailed = false;
	bool cherryActive;
	int beatsRemaining = -1;
	bool cherryPicked;
	std::vector<char> currentControls = { 'W', 'A', 'S', 'D' };

	// Default variables for level class.
	const float GRID_Y_MAX_PROPORTION = 0.6f;
	const float TIME_PER_STEP = 0.96f;
	const float TIME_FOR_ACTION = 0.32f;
	const float TIME_BUFFER = 0.32f;
	const float RESET_TIME = 1.0f;
	const float TIME_BETWEEN_CHANGES = 2.92f;
	float timeInStep = 0.f;
	bool soundPlayed = false;
	float cellDim;
	int beatsPlayed = 0;
	float damagedTimer = 0.f;
	float lastControlChange = 0.f;
	float boardTop, boardRight, boardBottom, boardLeft;

	// analytics values
	float timeTaken = 0.f;
	int misses = 0;
	int deaths = 0;
};

