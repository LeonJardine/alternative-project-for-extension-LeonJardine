#include "WizardLevel.h"

WizardLevel::WizardLevel(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm, int stage)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;
	textMan = tm;

	// initialise game objects
	selectedAction = NONE;
	lastAction = NONE;
	beatsPlayed = 0;

	

	// seed RNG
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	// initialise background. base size: 5760, 3240
	levelBG.setTexture(&textMan->getTexture("redSkyBG"));
	float bgScalar = std::max(hwnd->getSize().x / 5760.f, hwnd->getSize().y / 3240.f);
	levelBG.setSize(sf::Vector2f(5760 * bgScalar, 3240 * bgScalar));

	// initialise grid board
	// .. first calculate size. 
	float windowWidth = window->getSize().x;
	float windowHeight = window->getSize().y;
	boardTop = windowHeight * 0.05;	// the board is as wide as can be with the given constants.
	boardLeft = boardTop;	// uniform top and side padding.
	boardRight = windowWidth - boardLeft;
	int numRows = 10;
	int numCols = 20;
	cellDim = (boardRight - boardLeft) / numCols;
	boardBottom = numRows * cellDim + boardTop;
	// ensure grid does not take up too much of the sapce
	float maxHeight = boardTop + windowHeight * GRID_Y_MAX_PROPORTION;
	while (boardBottom > maxHeight)
	{
		// reduce cell size by 2px, reducing cells by 1px from each edge anchored at top. gridTop remains constant.
		cellDim -= 2;
		boardLeft += numCols;
		boardRight -= numCols;
		boardBottom -= numRows * 2;
	}

	playerPosition = { start.x, start.y };

	// .. Then setup board
	gridBoard.setFillColor(sf::Color::White);
	gridBoard.setSize(sf::Vector2f(boardRight - boardLeft, boardBottom - boardTop));
	gridBoard.setPosition(boardLeft, boardTop);

	// setup player component.
	player.setPosition(sf::Vector2f(
		gridBoard.getPosition().x + cellDim * start.x,
		gridBoard.getPosition().y + cellDim * start.y)
	);
	player.setSize(sf::Vector2f(cellDim, cellDim));

	// Setup progress bar component.
	progressInStep.setPosition(sf::Vector2f(900, 800));
	progressInStep.setSize(sf::Vector2f(0, 200));
	progressInStepBG.setPosition(sf::Vector2f(900, 790));
	progressInStepBG.setSize(sf::Vector2f(500, 220));
	progressInStepBG.setFillColor(sf::Color::Black);
	targetZone.setPosition(sf::Vector2f(
		progressInStepBG.getPosition().x + progressInStepBG.getSize().x * (TIME_PER_STEP - TIME_FOR_ACTION - TIME_BUFFER) / TIME_PER_STEP,
		790
	));
	targetZone.setSize(sf::Vector2f(
		progressInStepBG.getSize().x * (TIME_FOR_ACTION / TIME_PER_STEP),
		220
	));
	targetZone.setFillColor(sf::Color::Blue);

	// setup controls component.
	font.loadFromFile("font/montS.ttf");
	controls.push_back(sf::Text());
	controls[0].setPosition(boardLeft, boardBottom);
	controls[0].setCharacterSize(30);
	controls[0].setFont(font);
	controlBG.setPosition(boardLeft, boardBottom);
	controlBG.setSize(sf::Vector2f(380, 280));
	controlBG.setFillColor(sf::Color::Red);

	// setup grid component.
	grid = StageGrid(
		sf::Vector2i(numCols, numRows),
		cellDim,
		gridBoard.getPosition(),
		start,
		end,
		checkPoint,
		manMadeCheckPoint,
		2,
		textMan,
		easyMode,
		hardMode,
		skipCherry
	);

	// setup indicators
	std::vector<std::string> indicatorNames = { "upIcon", "leftIcon", "downIcon", "rightIcon" };
	for (int i = 0; i < indicatorNames.size(); ++i)
	{
		GameObject icon;
		icon.setTexture(&textMan->getTexture(indicatorNames[i]));
		icon.setSize(sf::Vector2f(80, 80));
		icon.setPosition(boardLeft + i * 100, boardBottom + 100);
		indicators.push_back(icon);
		sf::Text iconText;
		iconText.setFont(font);
		iconText.setString(currentControls[i]);
		iconText.setPosition(boardLeft + i * 100 + 28, boardBottom + 200);
		controls.push_back(iconText);
	}

	lecturer = new LecturEH(textMan);
	lecturer->setSize(sf::Vector2f(window->getSize().y*0.2, window->getSize().y * 0.2));
	lecturer->setPosition(window->getSize().x * 0.7, window->getSize().y*0.65);
}

WizardLevel::~WizardLevel() {}

void WizardLevel::handleInput(float dt)
{
	// user can't press buttons while resetting.
	if (damagedTimer > 0)
	{
		damagedTimer -= dt;
		return;
	}
	damagedTimer = 0.f;	// fix undersetting.

	// this bit is grim, but it it's basically just "press a button, try to set move".
	float timeLeft = TIME_PER_STEP - timeInStep;
	if (timeLeft > TIME_BUFFER && timeLeft < TIME_BUFFER + TIME_FOR_ACTION && !stepFailed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (currentControls[0] == 'A')
			{
				selectedAction = UP;
			}
			if (currentControls[1] == 'A')
			{
				selectedAction = LEFT;
			}
			if (currentControls[2] == 'A')
			{
				selectedAction = DOWN;
			}
			if (currentControls[3] == 'A')
			{
				selectedAction = RIGHT;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (currentControls[0] == 'W')
			{
				selectedAction = UP;
			}
			if (currentControls[1] == 'W')
			{
				selectedAction = LEFT;
			}
			if (currentControls[2] == 'W')
			{
				selectedAction = DOWN;
			}
			if (currentControls[3] == 'W')
			{
				selectedAction = RIGHT;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (currentControls[0] == 'D')
			{
				selectedAction = UP;
			}
			if (currentControls[1] == 'D')
			{
				selectedAction = LEFT;
			}
			if (currentControls[2] == 'D')
			{
				selectedAction = DOWN;
			}
			if (currentControls[3] == 'D')
			{
				selectedAction = RIGHT;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (currentControls[0] == 'S')
			{
				selectedAction = UP;
			}
			if (currentControls[1] == 'S')
			{
				selectedAction = LEFT;
			}
			if (currentControls[2] == 'S')
			{
				selectedAction = DOWN;
			}
			if (currentControls[3] == 'S')
			{
				selectedAction = RIGHT;
			}
		}
		if (selectedAction == LEFT) player.setFlipped(true);
	}
	else
	{
		// Timing incorrect, any attempted input is a fail.
		if(!stepFailed)	misses++;	// don't increment misses more than once/step
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			stepFailed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			stepFailed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			stepFailed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			stepFailed = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && easyMode)
	{
		manMadeCheckPoint = { playerPosition.first, playerPosition.second };
	}
}

void WizardLevel::update(float dt)
{
	// check for win
	if (playerPosition.first == end.x && playerPosition.second == end.y)
	{
		gameState->addResult("l3deaths", deaths);
		gameState->addResult("l3success", float(beatsPlayed - misses) / float(beatsPlayed));
		gameState->addResult("l3time", timeTaken);
		if (gameState->getSingleRun())
		{
			gameState->setCurrentState(State::ENDGAME);
		}
		else
		{
			gameState->setCurrentState(State::PRE_FOUR);
		}
		audio->playSoundbyName("success");
	}
	else
	{
		timeTaken += dt;
	}

	if (!cherryActive && playerPosition.second == skipCherry.y && playerPosition.first == skipCherry.x)
	{
		bool cherryPicked = true;
		cherryActive = true;
		skipCherry.x = 0;
		skipCherry.y = 0;
	}
	if (cherryActive && beatsRemaining == -1)
	{
		beatsRemaining = beatsPlayed + 2;
	}
	if (beatsRemaining == beatsPlayed)
	{
		cherryActive = false;
	}

	player.update(dt);
	lecturer->update(dt);

	// check if controls need to be changed
	if (timeTaken > TIME_BETWEEN_CHANGES + lastControlChange)
	{
		randomiseControls();
		lastControlChange = timeTaken;
	}

	if (!checkPointEnabled && playerPosition.second == checkPoint.y && playerPosition.first == checkPoint.x && !hardMode)
	{
		checkPointEnabled = true;
		manMadeEnabled = false;
		audio->playSoundbyName("success");
	}
	else if (!manMadeEnabled && playerPosition.second == manMadeCheckPoint.y && playerPosition.first == manMadeCheckPoint.x && easyMode)
	{
		checkPointEnabled = false;
		manMadeEnabled = true;
		audio->playSoundbyName("success");
	}

	// Play beat ONCE per step.
	if (!soundPlayed && timeInStep > TIME_PER_STEP - (TIME_FOR_ACTION / 2 + TIME_BUFFER))
	{
		audio->playSoundbyName("clap");
		soundPlayed = true;
	}

	// update UI
	switch (selectedAction)
	{
	case UP:
		controls[0].setString("up");
		break;
	case RIGHT:
		controls[0].setString("right");
		break;
	case DOWN:
		controls[0].setString("down");
		break;
	case LEFT:
		controls[0].setString("left");
		break;
	case FAIL:
		// don't update.
		break;
	case NONE:
		controls[0].setString("");
		break;
	}

	// update progress component
	timeInStep += dt;
	progressInStep.setSize(sf::Vector2f(
		(timeInStep / TIME_PER_STEP) * progressInStepBG.getSize().x,
		200
	));
	float timeLeft = TIME_PER_STEP - timeInStep;
	if (timeLeft > TIME_BUFFER && timeLeft < TIME_BUFFER + TIME_FOR_ACTION && selectedAction != FAIL)
	{
		progressInStep.setFillColor(sf::Color::Green);
	}
	else
	{
		progressInStep.setFillColor(sf::Color::Red);
	}

	// arrange arrow icons to show current controls
	std::vector<std::string> indicatorNames = { "upIcon", "leftIcon", "downIcon", "rightIcon" };
	std::vector<char> inOrder = { 'W','A','S','D' };
	for (int i = 0; i < 4; ++i)
	{
		// where is the next char in order in the list of current controls?
		int indexOfButton = 0;
		while (currentControls[indexOfButton] != inOrder[i])
		{
			indexOfButton++;
		}
		indicators[i].setTexture(&textMan->getTexture(indicatorNames[indexOfButton]));
	}

	// movement
	if (timeInStep >= TIME_PER_STEP)
	{
		// do a move.
		beatsPlayed++;
		stepFailed = false;
		grid.update(0);
		timeInStep = 0.f;
		soundPlayed = false;
		switch (selectedAction)
		{
		case UP:
			if (playerPosition.second == 0)
			{
				resetPlayer();
				break;
			}
			if (!cherryActive)
			{
				playerPosition.second--;// positive-y innit.
			}
			else if (cherryActive)
			{
				playerPosition.second--;
				playerPosition.second--;
			}
			break;
		case RIGHT:
			if (playerPosition.first == boardDimensions.x - 1)
			{
				resetPlayer();
				break;
			}
			if (!cherryActive)
			{
				playerPosition.first++;// positive-y innit.
			}
			else if (cherryActive)
			{
				playerPosition.first++;
				playerPosition.first++;
			}
			player.setFlipped(false);
			break;
		case DOWN:
			if (playerPosition.second == boardDimensions.y - 1)
			{
				resetPlayer();
				break;
			}
			if (!cherryActive)
			{
				playerPosition.second++;// positive-y innit.
			}
			else if (cherryActive)
			{
				playerPosition.second++;
				playerPosition.second++;
			}
			break;
		case LEFT:
			if (playerPosition.first == 0)
			{
				resetPlayer();
				break;
			}
			if (!cherryActive)
			{
				playerPosition.first--;// positive-y innit.
			}
			else if (cherryActive)
			{
				playerPosition.first--;
				playerPosition.first--;
			}
		}
		player.setPosition(sf::Vector2f(
			gridBoard.getPosition().x + cellDim * playerPosition.first,
			gridBoard.getPosition().y + cellDim * playerPosition.second)
		);
		if (grid.playerHit(playerPosition))
		{
			resetPlayer();
		}
	}
}

void WizardLevel::render()
{
	beginDraw();
	window->draw(levelBG);
	window->draw(controlBG);
	grid.render(window, checkPointEnabled,manMadeEnabled, cherryPicked);
	window->draw(controls[0]);
	window->draw(player);
	window->draw(progressInStepBG);
	window->draw(targetZone);
	window->draw(progressInStep);
	window->draw(*lecturer);
	for (GameObject ind : indicators)
	{
		window->draw(ind);
	}
	for (sf::Text label : controls)
	{
		window->draw(label);
	}
	endDraw();
}

void WizardLevel::selectedmode(int selectedmode, bool modechange)
{
	selectedMode = selectedmode;
	if (modechange)
	{
		for (int i = 0; i < 1; i++)
		{
			switch (selectedMode)
			{
			case EASY:
				easyMode = true;
				hardMode = false;
				grid = StageGrid(
					sf::Vector2i(20, 10),
					cellDim,
					gridBoard.getPosition(),
					start,
					end,
					checkPoint,
					manMadeCheckPoint,
					2,
					textMan,
					easyMode,
					hardMode,
					skipCherry
				);
				modechange = false;
				break;
			case NORMAL:
				easyMode = false;
				hardMode = false;
				grid = StageGrid(
					sf::Vector2i(20, 10),
					cellDim,
					gridBoard.getPosition(),
					start,
					end,
					checkPoint,
					manMadeCheckPoint,
					2,
					textMan,
					easyMode,
					hardMode,
					skipCherry
				);
				modechange = false;
				break;
			case HARD:
				easyMode = false;
				hardMode = true;
				grid = StageGrid(
					sf::Vector2i(20, 10),
					cellDim,
					gridBoard.getPosition(),
					start,
					end,
					checkPoint,
					manMadeCheckPoint,
					2,
					textMan,
					easyMode,
					hardMode,
					skipCherry
				);
				modechange = false;
				break;
			}
		}
	}
}

// change order of WASD controls
void WizardLevel::randomiseControls()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Shuffle the vector using std::shuffle
	std::shuffle(currentControls.begin(), currentControls.end(), gen);

}

void WizardLevel::reset()
{
	// initialise game objects
	selectedAction = NONE;
	beatsPlayed = 0;
	timeTaken = 0.f;
	misses = 0;
	deaths = 0;
	timeInStep = 0.f;
	soundPlayed = false;
	damagedTimer = 0.f;
	lastControlChange = 0.f;

	// seed RNG
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	// initialise background. base size: 5760, 3240
	levelBG.setTexture(&textMan->getTexture("redSkyBG"));
	float bgScalar = std::max(window->getSize().x / 5760.f, window->getSize().y / 3240.f);
	levelBG.setSize(sf::Vector2f(5760 * bgScalar, 3240 * bgScalar));

	// initialise grid board
	// .. first calculate size. 
	float windowWidth = window->getSize().x;
	float windowHeight = window->getSize().y;
	boardTop = windowHeight * 0.05;	// the board is as wide as can be with the given constants.
	boardLeft = boardTop;	// uniform top and side padding.
	boardRight = windowWidth - boardLeft;
	int numRows = 10;
	int numCols = 20;
	cellDim = (boardRight - boardLeft) / numCols;
	boardBottom = numRows * cellDim + boardTop;
	// ensure grid does not take up too much of the sapce
	float maxHeight = boardTop + windowHeight * GRID_Y_MAX_PROPORTION;
	while (boardBottom > maxHeight)
	{
		// reduce cell size by 2px, reducing cells by 1px from each edge anchored at top. gridTop remains constant.
		cellDim -= 2;
		boardLeft += numCols;
		boardRight -= numCols;
		boardBottom -= numRows * 2;
	}

	playerPosition = { start.x, start.y };

	// .. Then setup board
	gridBoard.setFillColor(sf::Color::White);
	gridBoard.setSize(sf::Vector2f(boardRight - boardLeft, boardBottom - boardTop));
	gridBoard.setPosition(boardLeft, boardTop);

	// setup player component.
	player.setPosition(sf::Vector2f(
		gridBoard.getPosition().x + cellDim * start.x,
		gridBoard.getPosition().y + cellDim * start.y)
	);
	player.setSize(sf::Vector2f(cellDim, cellDim));

	// Setup progress bar component.
	progressInStep.setPosition(sf::Vector2f(900, 800));
	progressInStep.setSize(sf::Vector2f(0, 200));
	progressInStepBG.setPosition(sf::Vector2f(900, 790));
	progressInStepBG.setSize(sf::Vector2f(500, 220));
	progressInStepBG.setFillColor(sf::Color::Black);
	targetZone.setPosition(sf::Vector2f(
		progressInStepBG.getPosition().x + progressInStepBG.getSize().x * (TIME_PER_STEP - TIME_FOR_ACTION - TIME_BUFFER) / TIME_PER_STEP,
		790
	));
	targetZone.setSize(sf::Vector2f(
		progressInStepBG.getSize().x * (TIME_FOR_ACTION / TIME_PER_STEP),
		220
	));
	targetZone.setFillColor(sf::Color::Blue);

	// setup controls component.
	font.loadFromFile("font/montS.ttf");
	controls[0].setPosition(boardLeft, boardBottom);
	controls[0].setCharacterSize(30);
	controls[0].setFont(font);
	controlBG.setPosition(boardLeft, boardBottom);
	controlBG.setSize(sf::Vector2f(380, 280));
	controlBG.setFillColor(sf::Color::Red);

	// setup grid component.
	grid = StageGrid(
		sf::Vector2i(numCols, numRows),
		cellDim,
		gridBoard.getPosition(),
		start,
		end,
		checkPoint,
		manMadeCheckPoint,
		2,
		textMan,
		easyMode,
		hardMode,
		skipCherry
	);

	checkPointEnabled = false;
	manMadeEnabled = false;
}

/*
Put player back to the starting space.
*/
void WizardLevel::resetPlayer()
{
	if (checkPointEnabled) playerPosition = { checkPoint.x, checkPoint.y };
	else if (manMadeEnabled) playerPosition = { manMadeCheckPoint.x , manMadeCheckPoint.y };
	else playerPosition = { start.x, start.y };
	audio->playSoundbyName("death");
	damagedTimer = RESET_TIME;
	player.setDamaged(damagedTimer);
	selectedAction = NONE;
	player.setFlipped(false);
	deaths++;
}

