#include "TitleScreen.h"

TitleScreen::TitleScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;
	textMan = tm;

	// set positions and textures.
	//   .. for the fan
	fan.setPosition(window->getSize().x * 0.7, window->getSize().y * 0.5);
	float fanProportion = textMan->getProportions("sadBear");
	fan.setSize(sf::Vector2f(window->getSize().x * 0.2, window->getSize().x * 0.2 * fanProportion));
	fan.setTexture(&textMan->getTexture("sadBear"));
	
	// .. for the text
	montsFont.loadFromFile("font/montS.ttf");
	explanationText.setFont(montsFont);
	explanationText.setString("The Forbidden Rhythms.\n\tYou must unleash them.\n\t\tYour fans are waiting.\n\t\t\tHit the space bar.\n\t\t\t\tBegin.");
	explanationText.setPosition(window->getSize().x * 0.3, window->getSize().y * 0.2);
	explanationText.setCharacterSize(40);
	titleText.setFont(montsFont);
	titleText.setString("FORBIDDEN\n\tRHYTHMS");
	titleText.setPosition(10, window->getSize().y * 0.2);
	titleText.setCharacterSize(60);
	singleRunText.setFont(montsFont);
	singleRunText.setCharacterSize(40);
	singleRunText.setPosition(window->getSize().x * 0.1, window->getSize().y * 0.8);
	singleRunText.setString("Press 1 to practice LECTURER.\nPress 2 to practice RUNNER.\nPress 3 to practice WIZARD.");


	// .. background
	// initialise background. base size: 1920, 1080
	bg.setTexture(&textMan->getTexture("titleBG"));
	float bgScalar = std::max(hwnd->getSize().x / 1920.f, hwnd->getSize().y / 1080.f);
	bg.setSize(sf::Vector2f(1920 * bgScalar, 1080* bgScalar));

	animTimer = 0.0f;
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::handleInput(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		gameState->setCurrentState(State::PRE_ONE);
		gameState->setSingleRun(false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		gameState->setCurrentState(State::PRE_ONE);
		gameState->setSingleRun(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		gameState->setCurrentState(State::PRE_TWO);
		gameState->setSingleRun(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		gameState->setCurrentState(State::PRE_THREE);
		gameState->setSingleRun(true);
	}

}

void TitleScreen::update(float dt)
{
	// update sizes to be dynamic.
	fan.setPosition(window->getSize().x * 0.7, window->getSize().y * 0.5);
	float fanProportion = textMan->getProportions("sadBear");
	fan.setSize(sf::Vector2f(window->getSize().x * 0.2, window->getSize().x * 0.2 * fanProportion));

	textMan->animate(&fan, "sadBear", animTimer);
	animTimer += dt;
	
}

void TitleScreen::render()
{
	beginDraw();
	window->draw(bg);
	window->draw(fan);
	window->draw(explanationText);
	window->draw(titleText);
	window->draw(singleRunText);
	endDraw();
}
