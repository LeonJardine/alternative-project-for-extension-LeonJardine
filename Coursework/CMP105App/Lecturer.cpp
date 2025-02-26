#include "Lecturer.h"
#include <SFML/Graphics/Text.hpp>

Lecturer::Lecturer()
{
}

Lecturer::Lecturer(sf::RenderWindow* hwnd, TextureManager* tm)
{
	textMan = tm;
	window = hwnd;
	setSize(sf::Vector2f(150, 150));
	setPosition(hwnd->getSize().x * 0.75, hwnd->getSize().y * 0.65);

	setTexture(&tm->getTexture("lecturer"));

	speak.addFrame(sf::IntRect(0, 0, 25, 25));
	speak.addFrame(sf::IntRect(25, 0, 25, 25));
	speak.addFrame(sf::IntRect(50, 0, 25, 25));
	speak.addFrame(sf::IntRect(25, 0, 25, 25));
	currentAnimation = &speak;
	speak.setFrameSpeed(1.0f / 4.0f);
	//speak.setLooping(true);
	motivationalMessages =
	{
		"",
		"You can\ndo it!",
		"",
		"The secret\nis confidence!",
		"",
		"Don't forget your\ndata structures!",
		"",
		"You can submit\nbefore deadlines\nif you want!",
		"",
		"Teamwork\nmakes the\ndream work!",
		"",
		"Remember to\npush to the\nrepository!",
		"",
		"Consistency\nis key!",
		"",
		"When the going\ngets tough,\nthe tough\nget going!"
	};
	nextMessage = 0;
	if(!font.loadFromFile("font/fortuner.otf"))
		std::cout << "missed font\n";
	
	msgDisplayTargetTime = 2.0f;
	msgDisplayTime = 0.f;

	timeAlive = -4.f;	// let them get comfy.
	animSpeed = 1.0f / 8.0f;
}


void Lecturer::update(float dt)
{

	timeAlive += dt;
	msgDisplayTime += dt;
	// cycle messages every 3 seconds:
	// i.e., 0-3s: -1, 3-6s: 0, 6-9s: 1... etc
	if ((nextMessage + 1) * 3 < fmod(timeAlive, static_cast<float>(motivationalMessages.size() * 3)) &&
		(nextMessage + 2) * 3 > fmod(timeAlive, static_cast<float>(motivationalMessages.size() * 3)) &&
		timeAlive >= 0)
	{
		nextMessage++;
		msgDisplayTime = 0.0f;
	}

	// if there is text being displayed and the time to animate hasn't expired.
	if (msgDisplayTime < msgDisplayTargetTime && motivationalMessages[nextMessage] != "")
	{
		// animate the lecturer.
		switch (static_cast<int>(msgDisplayTime / animSpeed) % 4)
		{
		case 0:
			setTextureRect(sf::IntRect(0, 0, 25, 25));
			break;
		case 1:
			setTextureRect(sf::IntRect(25, 0, 25, 25));
			break;
		case 2:
			setTextureRect(sf::IntRect(50, 0, 25, 25));
			break;
		case 3:
			setTextureRect(sf::IntRect(25, 0, 25, 25));
			break;
		}
	}
	else
	{
		setTextureRect(sf::IntRect(0, 0, 25, 25));
	}
		
}

/*
Takes a text object and sizes it based on a position and dimensions to make text
cover as much of the image as possible.
*/
sf::Text Lecturer::sizeTextToGrid(sf::Text t, float boardTop, float boardRight, float boardBottom, float boardLeft)
{
	if (t.getString().isEmpty()) return t;
	// Clone the original text
	sf::Text resizedText = t;

	// Calculate the maximum character size that fits within the grid dimensions
	int maxCharacterSize = 40;

	resizedText.setPosition(sf::Vector2f(boardLeft, boardTop));

	// Adjust the character size until it fits within the grid
	while (resizedText.getLocalBounds().width < boardRight - boardLeft && 
		resizedText.getLocalBounds().height < boardBottom - boardTop &&
		maxCharacterSize < maxSize)
	{
		resizedText.setCharacterSize(maxCharacterSize);
		maxCharacterSize+=5;

		//// check if it is now too wide and therefore needing a newline.
		//if (resizedText.getLocalBounds().width > boardRight - boardLeft)
		//{
		//	std::string formerString = resizedText.getString();
		//	// Find the index to split based on word boundaries
		//	size_t splitIndex = formerString.find_last_of(" \t\n", formerString.length() / 2);
		//	if (splitIndex != std::string::npos)
		//	{
		//		formerString[splitIndex] = '\n'; // Replace space with newline
		//		resizedText.setString(formerString);
		//	}
		//	else
		//	{
		//		break; // Unable to find a suitable split point
		//	}
		//}
	}

	return resizedText;
}

sf::Text Lecturer::getMessageToDisplay(float boardTop, float boardRight, float boardBottom, float boardLeft)
{
	sf::Text messageText;
	messageText.setFont(font);
	if (nextMessage == -1)
		messageText.setString("");
	else
		messageText.setString(motivationalMessages[nextMessage]);

	return sizeTextToGrid(messageText, boardTop, boardRight, boardBottom, boardLeft);
}

