#include "Sidekick.h"
#include <iostream>

Sidekick::Sidekick()
{
	setPosition(sf::Vector2f(100, 100));
	setSize(sf::Vector2f(23, 23));

	sidekick.loadFromFile("gfx/Goomba.png");

	setTexture(&sidekick); // set that texture to this object.

}

Sidekick::~Sidekick()
{
}

void Sidekick::setJumping(float jumpH, float jumpLength)
{
	//jumpTime = jumpLength;
	//jumpTimeElapsed = 0;
	//jumpHeight = jumpH;
}



void Sidekick::setKicking(float t)
{
	//kick.setFrameSpeed(t / kick.getSize());
	//kick.reset();
	//currentAnimation = &kick;
	//kickTime = t;
	//kickTimeElapsed = 0.f;
}



void Sidekick::setFlipped(bool f)
{

}

void Sidekick::handleInput(float dt)
{

}



void Sidekick::setDamaged(float timer)
{
	//currentAnimation = &damaged;
	//damageLength = timer;
}

void Sidekick::update(float dt)
{
	//if (currentAnimation == &damaged)
	//	damagedTimer += dt;
//	if (damagedTimer > damageLength)
	//{
	//	currentAnimation = &walk;
	//	damagedTimer = 0.f;
	//}

	// check for jump
	//if (jumpTimeElapsed < jumpTime)
//	{

		//jumpTimeElapsed += dt;
		// go up.
		//if (jumpTimeElapsed < jumpTime * 0.2)
		//{
		//	move(0, -jumpHeight * dt / (jumpTime * 0.2));
		//}
		// hover for a bit
		// go down.
		//if (jumpTimeElapsed > jumpTime * 0.7)
		//{
			//move(0, jumpHeight * dt / (jumpTime * 0.3));
		//}

	//}
	//else
	//{
	//	jumpHeight = 0;
	//	jumpTimeElapsed = 0.f;
	//	jumpTime = 0.f;
	//}

	// check for kick status.
	//if (kickTime != 0)
	//{
		//if (kickTimeElapsed < kickTime) kickTimeElapsed += dt;
		//else
		//{
		//	currentAnimation = &walk;
		//	kickTime = 0.f;
		//	kickTimeElapsed = 0.f;
		//}
	//}

	

}