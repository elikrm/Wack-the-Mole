// HelloSFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	VideoMode vm(1440, 1080);
	RenderWindow window(vm, "Timber Game", Style::Default);
	//drawing background
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	//drawing the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setScale(0.5, 0.5);
	spriteBee.setPosition(1200, 0);
	bool BeeActive = false;
	float BeeSpeed = 0.0f;

	// drawing the mole2
	Texture textureMole2;
	textureMole2.loadFromFile("graphics/mole2.png");
	Sprite spriteMole2;
	spriteMole2.setTexture(textureMole2);
	spriteMole2.scale(0.5, 0.5);
	spriteMole2.setPosition(550, 450);
	bool MoleActive = false;
	float MoleSpeed = 0.0f;
	int MoleUp = 0;

	// drawing the mole1
	Texture textureMole1;
	textureMole1.loadFromFile("graphics/mole1.png");
	Sprite spriteMole1;
	spriteMole1.setTexture(textureMole1);
	spriteMole1.scale(0.5, 0.5);
	spriteMole1.setPosition(550, 450);

	// drawing the mole3
	Texture textureMole3;
	textureMole3.loadFromFile("graphics/mole3.png");
	Sprite spriteMole3;
	spriteMole3.setTexture(textureMole3);
	spriteMole3.scale(0.5, 0.5);
	spriteMole3.setPosition(550, 450);

	//drawing the hammer
	Texture textureHammer;
	textureHammer.loadFromFile("graphics/hammer2.png");
	Sprite spriteHammer;
	spriteHammer.setTexture(textureHammer);
	spriteHammer.scale(0.5, 0.5);
	spriteHammer.setPosition(650, 300);
	bool HammerActive = false;
	float HammerSpeed = 0.0f;

	Clock clock;
	//track whether the game is running
	bool paused = true;

	//Draw some text
	int score = 0;
	sf::Text MessageText;
	sf::Text ScoreText;
	// choose a font
	sf:: Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//set the font to our messages
	MessageText.setFont(font);
	ScoreText.setFont(font);

	//assign the actual messages
	MessageText.setString("Press Enter to start");
	ScoreText.setString("Score = 0 ");

	//make them really big
	MessageText.setCharacterSize(75);
	ScoreText.setCharacterSize(100);

	//choose their color
	MessageText.setFillColor(Color::Yellow);
	ScoreText.setFillColor(Color::Yellow);

	//Position the texts
	FloatRect textRect = MessageText.getLocalBounds();
	MessageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	MessageText.setPosition(1440/2.0f, 1080/2.0f);
	ScoreText.setOrigin(5, 5);
	
	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		//check enter key is pressed
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
		}
		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!paused)
		{
			//measure the time 
			Time dt = clock.restart();
			if (!BeeActive)
			{
				//how fast is the Bee
				srand((int)time(0) * 10);
				BeeSpeed = (rand() % 500) + 500;
				srand((int)time(0) * 10);
				float heigth = (rand() % 400) + 400;
				spriteBee.setPosition(1200, heigth);
				BeeActive = true;
			}
			else
			{
				//move the bee
				spriteBee.setPosition(spriteBee.getPosition().x - (BeeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
				if (spriteBee.getPosition().x < 0)
				{
					BeeActive = false;
				}
			}
			//setup the Mole
#if 0
			if (!MoleActive)
			{
				srand((int)time(0) * 10);
				MoleUp = (rand() % 3);
				//how fast is the Mole
				srand((int)time(0) * 10);
				MoleSpeed = (rand() % 200) + 200;
				// how heigth is the Mole
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteMole2.setPosition(550, height);
				MoleActive = true;
			}
			else
			{
				//move the Mole
				spriteMole2.setPosition(550, spriteMole2.getPosition().y - MoleSpeed * dt.asSeconds());
				if (spriteMole2.getPosition().y < 0)
				{
					//spriteMole.setPosition(550, 450);
					MoleActive = false;
				}

			}
#endif
			//update score text 
			std::stringstream ss;
			ss << "Score: "<< score;
			ScoreText.setString(ss.str());
		}//end of paused
		/*
		****************************************
		Draw the scene
		****************************************
		*/
		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteBee);
		window.draw(spriteHammer);
		window.draw(spriteMole2);
		clock.getElapsedTime();
		window.draw(spriteMole1);
		spriteMole1.setColor(sf::Color(255, 255, 255, 0));
		spriteMole1.setColor(sf::Color(255, 255, 255, 255));
		spriteMole2.setColor(sf::Color(255, 255, 255, 0));
		spriteMole2.setColor(sf::Color(255, 255, 255, 255));
		//window.draw(spriteMole3);
		//draw the score 
		window.draw(ScoreText);
		if (paused)
		{
			//draw our message
			window.draw(MessageText);
		}
		// show everything we just drew
		window.display();
	}
    return 0;
}

