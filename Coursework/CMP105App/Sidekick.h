#pragma once

#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Sidekick : public GameObject
{
public:
	Sidekick();
	~Sidekick();

	void handleInput(float dt);
	void setDamaged(float timer);

	void update(float dt);
	void setFlipped(bool f);
	void setJumping(float h, float t);
	
	void setKicking(float t);
	

	sf::Texture sidekick;
	Input in;
	Animation walk;
	Animation damaged;
	Animation kick;
	Animation* currentAnimation;

	// jump component
	float jumpHeight;
	float jumpTimeElapsed = 0.f;
	float jumpTime = 0.f;

	float kickTime = 0.f;
	float kickTimeElapsed = 0.f;

	float damagedTimer = 0.f;
	float damageLength = 100.0f;
};