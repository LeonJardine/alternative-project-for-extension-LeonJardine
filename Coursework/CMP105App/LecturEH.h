// lecturer + Erin Hughes = LecturEH. 
// class used to add planned functionality.
// never got around to it though. Sad.

#pragma once
#include "Framework/GameObject.h"
#include "TextureManager.h"
#include "Framework/Animation.h"

class LecturEH : public GameObject
{
public:
	LecturEH(TextureManager* tm);
	~LecturEH();

	void update(float dt);

	Animation* currentAnimation;
	Animation hop;
	Animation still;

	float timeSinceHop = 0.f;
	float HOP_DELAY = 5.0f;
};

