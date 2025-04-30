#include "Sidekick.h"
#include <iostream>

Sidekick::Sidekick()
{
	setPosition(sf::Vector2f(100, 100));
	setSize(sf::Vector2f(100, 100));

	sidekick.loadFromFile("gfx/sidekick.png");

	setTexture(&sidekick); // set that texture to this object.
	for (int i = 0; i < 2; ++i)
	{
		bite.addFrame(sf::IntRect(i * 100, 0.f, 100.f, 100.f));
	}
	damaged.addFrame(sf::IntRect(0, 0.f, 100.f, 100.f));
	

	for (int i = 3; i < 6; i++)
	{
		walk.addFrame(sf::IntRect(i * 100, 0.f, 100.f, 100.f));
	}

	damaged.setFrameSpeed(1.f / 4.f);
	walk.setFrameSpeed(1.f / 10.f);
	currentAnimation = &walk;

	velocity = { 0,0 };
}

Sidekick::~Sidekick()
{
}



void Sidekick::setJumping(float jumpH, float jumpLength)
{
	jumpTime = jumpLength;
	jumpTimeElapsed = 0;
	jumpHeight = jumpH;
}

bool Sidekick::isKicking()
{
	return kickTimeElapsed > 0 && kickTimeElapsed < kickTime;
}

void Sidekick::setKicking(float t)
{
	bite.setFrameSpeed(t / bite.getSize());
	bite.reset();
	currentAnimation = &bite;
	kickTime = t;
	kickTimeElapsed = 0.f;
}

bool Sidekick::canJump() const
{
	return jumpTime == 0;
}

void Sidekick::setFlipped(bool f)
{
	currentAnimation->setFlipped(f);
}

void Sidekick::handleInput(float dt)
{

}

bool Sidekick::isDamaged()
{
	return currentAnimation == &damaged;
}

void Sidekick::setDamaged(float timer)
{
	currentAnimation = &damaged;
	damageLength = timer;
}

void Sidekick::update(float dt)
{
	if (currentAnimation == &damaged)
		damagedTimer += dt;
	if (damagedTimer > damageLength)
	{
		currentAnimation = &walk;
		damagedTimer = 0.f;
	}

	// check for jump
	if (jumpTimeElapsed < jumpTime)
	{

		jumpTimeElapsed += dt;
		// go up.
		if (jumpTimeElapsed < jumpTime * 0.2)
		{
			move(0, -jumpHeight * dt / (jumpTime * 0.2));
		}
		// hover for a bit
		// go down.
		if (jumpTimeElapsed > jumpTime * 0.7)
		{
			move(0, jumpHeight * dt / (jumpTime * 0.3));
		}

	}
	else
	{
		jumpHeight = 0;
		jumpTimeElapsed = 0.f;
		jumpTime = 0.f;
	}

	// check for kick status.
	if (kickTime != 0)
	{
		if (kickTimeElapsed < kickTime) kickTimeElapsed += dt;
		else
		{
			currentAnimation = &walk;
			kickTime = 0.f;
			kickTimeElapsed = 0.f;
		}
	}

	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());

}