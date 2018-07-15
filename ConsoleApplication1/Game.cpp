// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "Game.h"
#include "Fireball.h"
#include <vector>
#define GLOBAL_COOLDOWN 0.5
sf::CircleShape Game::innercirclecreation() {
	auto innercirclecolor = sf::Color(112, 54, 14, 255);
	sf::CircleShape innercircle(200.f);
	innercircle.setFillColor(innercirclecolor);
	innercircle.setPointCount(60);
	return innercircle;
}

void Game::loadTextures()
{
	rh.load(Textures::Player, "C:/Users/frede/Desktop/Images/topdownzombie.png");
	rh.load(Textures::Fireball, "C:/Users/frede/Desktop/Images/fireball.png");
}

Game::Game() : viewPos(0,0), windowRect(viewPos.x, viewPos.y, windowWidth, windowHeight)
{
	
	loadTextures();
	sf::Clock globalCooldownClock;
	float elapsedtime = 0;
	bool doonce = true;
	Player player(rh);
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
	sf::View view(windowRect);
	sf::CircleShape innercircle = innercirclecreation();
	innercircle.setPosition(view.getCenter().x - (innercircle.getGlobalBounds().width / 2), view.getCenter().y - (innercircle.getGlobalBounds().height / 2));
	sf::Vector2f playerPosition(view.getCenter().x, view.getCenter().y);
	player.setPosition(playerPosition);
	window.setView(view);
	window.setFramerateLimit(30);
	std::vector<Ability> activeAbilities;

	while (window.isOpen())
	{
		sf::Vector2f pointClicked = (sf::Vector2f) sf::Mouse::getPosition(window);
		sf::Event event;
		player.moveInDirection();
		player.stopAtDestination();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			player.changeDirectionToPoint(pointClicked);
			player.startMoving(pointClicked);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				//Fireball fireball(rh);
				if (globalCooldownClock.getElapsedTime().asSeconds() > GLOBAL_COOLDOWN) {
					Fireball fb(rh);
					fb.setPosition(player.getSprite().getPosition());
					fb.changeDirectionToPoint(pointClicked);
					fb.startMoving(pointClicked);
					globalCooldownClock.restart();
					activeAbilities.push_back(fb);
				}
		}
		window.setView(view);
		//window.draw(background);
		window.draw(innercircle);
		for (Ability &a : activeAbilities) {
			if (windowRect.contains(a.getSprite().getPosition())) {
				a.moveInDirection();
				window.draw(a.getSprite());
			}
		}
		std::cout << activeAbilities.size() << "\n";
		window.draw(player.getSprite());
		window.display();
		window.clear();
	}
	
}

