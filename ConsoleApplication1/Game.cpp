// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "Game.h"
#include "Fireball.h"
#include "Icicle.h"
#include "Meteor.h"
#include <vector>
#define GLOBAL_COOLDOWN 0.2
#define timeBetweenAIActions 0.5
#define dodgeTime 0.8
#define icicleTime 3.0
#define neutralPlayerId -1
sf::CircleShape Game::innercirclecreation() {
	auto innercirclecolor = sf::Color(112, 54, 14, 255);
	sf::CircleShape innercircle(300.f);
	innercircle.setFillColor(innercirclecolor);
	innercircle.setPointCount(60);
	innercircle.setOrigin(sf::Vector2f(innercircle.getGlobalBounds().width / 2, (innercircle.getGlobalBounds().height / 2)));
	return innercircle;
}

Projectile* Game::createProjectile(bool Qpressed, bool Wpressed, bool Epressed,Player &c) {
	if (Qpressed) {
		return new Fireball(rh, c.getID());
	}
	if (Wpressed) {
		c.decrementAvailableIcicle();
	   return  new Icicle(rh, c.getID());
	}
	if (Epressed) {
		return new Meteor(rh, neutralPlayerId);
	}
	return nullptr; 
}

void Game::loadFonts() {
	fh.load(Fonts::orangeJuice, "C:/Users/frede/Desktop/Fonts/orange juice 2.0.ttf");
}

void Game::loadTextures()
{
	rh.load(Textures::Player, "C:/Users/frede/Desktop/Images/topdownzombie.png");
	rh.load(Textures::Fireball, "C:/Users/frede/Desktop/Images/fireball.png");
	rh.load(Textures::Sartan, "C:/Users/frede/Desktop/Images/bandanabird.png");
	rh.load(Textures::Lava, "C:/Users/frede/Desktop/Images/Lava.jpg");
	rh.load(Textures::Icicle, "C:/Users/frede/Desktop/Images/Icicle.png");
	rh.load(Textures::Meteor, "C:/Users/frede/Desktop/Images/meteor.png");
}

bool characterHit(std::vector<Character*> charactersInGame, sf::Shape* fbrs, Projectile* projectile){
	for (Character* current : charactersInGame) {
		sf::Shape *characterBS = current->getBoundingShape();
		if (CustomMath::circleIntersectionWithRotatedRectangle(sf::Vector2f(characterBS->getPosition().x - current->getCircleRadius(), characterBS->getPosition().y - current->getCircleRadius()), current->getCircleRadius(), fbrs->getGlobalBounds(), fbrs->getRotation())) {
			sf::Vector2f unitVectorDirection = CustomMath::normalizeUnitVector(current->getSprite().getPosition(), projectile->getSprite().getPosition());
			sf::Vector2f unitVectorOppositeDirection = sf::Vector2f(-unitVectorDirection.x, -unitVectorDirection.y);
			if (current->getID() != projectile->getOwnerID()) {
				current->isHit(unitVectorOppositeDirection);
				return true;
			}
		}

	}

	return false;
}

//bool projectileHit. test om fireball rammer icicle. Test om meteor rammer fireball. 

Game::Game() : viewPos(0,0), windowRect(viewPos.x, viewPos.y, windowWidth, windowHeight)
{
	loadFonts();
	loadTextures();
	sf::Texture background = rh.get(Textures::Lava);
	background.setRepeated(true);
	sf::Sprite backgroundSprite(background);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 640));
	sf::Sprite gb = backgroundSprite;
	sf::Text healthText;
	healthText.setFont(fh.get(Fonts::orangeJuice));
	healthText.setCharacterSize(30);
	sf::Clock dodgeClock;
	sf::Clock globalCooldownClock;
	sf::Clock aiActionClock;
	sf::Clock icicleClock;
	Player player(rh,1);
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
	sf::View view(windowRect);
	sf::CircleShape innercircle = innercirclecreation();
	window.setView(view);
	window.setFramerateLimit(30);
	innercircle.setPosition(view.getCenter().x, view.getCenter().y);
	sf::Vector2f playerPosition(view.getCenter().x, view.getCenter().y);
	player.setPosition(playerPosition);
	std::vector<Projectile*> activeAbilities;
	std::vector<Character*> charactersInGame;

	Sartan s(rh, 3);
	Player p2(rh,2);

	charactersInGame.push_back(&s);
	charactersInGame.push_back(&player);

	while (window.isOpen())
	{
		gb.setPosition((sf::Vector2f) window.mapPixelToCoords(sf::Vector2i(0, 0)));
		window.draw(gb);
		if (!CustomMath::circleContainsPoint(innercircle, player.getSprite().getPosition())) {
			player.outsideBounds();
		}
		view.setCenter(player.getSprite().getPosition());
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f pointClicked = window.mapPixelToCoords(pixelPos);
		sf::Event event;
		for (Character* current : charactersInGame) {
			current->moveInDirection();
			current->handleHitStun();
			current->setBoundingShape();
			current->stopAtDestination();
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.getHitState() == Character::NOTHIT) {
			player.startMovingToPoint(pointClicked);
		}
		if (icicleClock.getElapsedTime().asSeconds() > icicleTime) {
			player.incrementAvailableIcicle();
			icicleClock.restart();
		}
		if (s.getHitState() == Character::NOTHIT && aiActionClock.getElapsedTime().asSeconds() > timeBetweenAIActions) {
			s.act(activeAbilities);
			if (s.getDodged()) {
				s.setDodged(false);
			}
			aiActionClock.restart();
		}
		bool Qpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q); 
		bool Wpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (player.getAvailableIcicle() > 0);
		bool Epressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
		if (Qpressed || Wpressed || Epressed) {
				if (globalCooldownClock.getElapsedTime().asSeconds() > GLOBAL_COOLDOWN && player.getHitState() == Character::NOTHIT) {
					Projectile *fb = createProjectile(Qpressed, Wpressed, Epressed, player);
					if (globalCooldownClock.getElapsedTime().asSeconds() > fb->getCooldown() + GLOBAL_COOLDOWN && fb->getReadyToShoot()) {
						player.shootProjectile(fb, pointClicked);
						globalCooldownClock.restart();
						activeAbilities.push_back(fb);
						// AI stuff
						sf::Vector2f pointAfterMove = CustomMath::pointAfterMove(fb->getSprite().getPosition(), CustomMath::distance(fb->getSprite().getPosition(), s.getSprite().getPosition()), fb->getAngle());
						sf::FloatRect oldPosRect = fb->getSprite().getGlobalBounds();
						//std::cout << pointAfterMove.x << " sartan x " << s.getBoundingShape()->getPosition().x << " " <<  pointAfterMove.y << " sartan y " << s.getBoundingShape()->getPosition().y << "\n";
						sf::FloatRect newPosRect = sf::FloatRect(pointAfterMove.x, pointAfterMove.y, oldPosRect.width, oldPosRect.height);
						if (CustomMath::circleIntersectionWithRotatedRectangle(sf::Vector2f(s.getBoundingShape()->getPosition().x - s.getCircleRadius(), s.getBoundingShape()->getPosition().y - s.getCircleRadius()), s.getCircleRadius(), newPosRect, fb->getBoundingShape()->getRotation())) {
							s.setDodged(true);
							dodgeClock.restart();
						}
					}
				}
		}
		window.setView(view);
		window.draw(innercircle);
		//std::cout << activeAbilities.size();
		auto projectileit = std::begin(activeAbilities);
		while (projectileit != std::end(activeAbilities)) {
		//	if (windowRect.contains(ability->getSprite().getPosition())) {
				(*projectileit)->setBoundingShape();
				sf::Shape *fbrs = (*projectileit)->getBoundingShape(); 
				if (characterHit(charactersInGame, fbrs, (*projectileit))) {
					projectileit = activeAbilities.erase(projectileit);
					continue;
				}
				// CHECK INTERSECTION MED CIRKEL!
				(*projectileit)->moveInDirection();
				window.draw(*fbrs);
				window.draw((*projectileit)->getSprite());
				//std::cout << (*projectileit)->getSprite().getPosition().y << "\n";
				projectileit++;
				//Husk!! mange abilities = mange checks. 
			//}
		}

		healthText.setString("Health :" + std::to_string(player.getHealth()));
		healthText.setPosition((sf::Vector2f) window.mapPixelToCoords(sf::Vector2i(0, 0)));
		window.draw(healthText);
		window.draw(s.getSprite());
		window.draw(player.getSprite());
		/*for (Character* current : charactersInGame) {
			window.draw(*(current->getBoundingShape()));
		}*/
		//window.draw(*mrs);;
		//window.draw(*(s.getBoundingShape()));
		window.display();
		window.clear();
	}
	
}

