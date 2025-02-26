#include "LecturEH.h"

LecturEH::LecturEH(TextureManager* tm)
{
	setTexture(&tm->getTexture("lecturEH"));

	still.addFrame(sf::IntRect(0, 0, 32, 32));
	still.setFrameSpeed(1.f);

	hop.addFrame(sf::IntRect(32, 0, 32, 32));
	hop.addFrame(sf::IntRect(96, 0, 32, 32));
	hop.addFrame(sf::IntRect(64, 0, 32, 32));
	hop.addFrame(sf::IntRect(96, 0, 32, 32));
	hop.setFrameSpeed(1.f / 4.f);

	currentAnimation = &still;
}

LecturEH::~LecturEH()
{
}

void LecturEH::update(float dt)
{
	timeSinceHop += dt;

	if (timeSinceHop > HOP_DELAY + 1)
	{
		// hop over.
		hop.reset();
		timeSinceHop = 0.f;
		currentAnimation = &still;
	}
	else if (timeSinceHop > HOP_DELAY)
	{
		currentAnimation = &hop;
	}

	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());
}

