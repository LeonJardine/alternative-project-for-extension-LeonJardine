#pragma once
#include "Framework/BaseLevel.h"
#include "TextureManager.h"
#include "Sidekick.h"
#include <random>
#include <iostream>

class SurferLevel : BaseLevel
{
public:
	SurferLevel(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm);
	~SurferLevel();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;
	bool colliding(GameObject obj);
	void reset();

private:
	TextureManager* textMan;
	Sidekick p;
	std::vector<GameObject> BGs;
	std::vector<GameObject> jumpables;
	std::vector<GameObject> kickables;
	std::vector<GameObject> explosions;
	std::vector<float> explosionTimer;

	GameObject progressLine;
	Sidekick progressP;
	sf::CircleShape destinationPoint;

	GameObject moon;
	GameObject finishLine;

	float distance;
	float travelled = 0.f;
	float speed;

	const float MAX_SPEED = 650;
	const float ACCELERATION = 250;

	int hits = 0;
	float time = 0.f;
	float objects = 0.f;
};