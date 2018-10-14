// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "Game.h"
#include "Fireball.h"
#include <vector>
#define GLOBAL_COOLDOWN 0.5
#define timeBetweenAIActions 0.4
#define dodgeTime 1.5
sf::CircleShape Game::innercirclecreation() {
	auto innercirclecolor = sf::Color(112, 54, 14, 255);
	sf::CircleShape innercircle(300.f);
	innercircle.setFillColor(innercirclecolor);
	innercircle.setPointCount(60);
	innercircle.setOrigin(sf::Vector2f(innercircle.getGlobalBounds().width / 2, (innercircle.getGlobalBounds().height / 2)));
	return innercircle;
}

void Game::loadFonts() {
	fh.load(Fonts::orangeJuice, "C:/Users/frede/Desktop/Fonts/orange juice 2.0.ttf");
}

void Game::loadTextures()
{
	rh.load(Textures::Player, "C:/Users/frede/Desktop/Images/topdownzombie.png");
	rh.load(Textures::Fireball, "C:/Users/frede/Desktop/Images/fireball.png");
	rh.load(Textures::Sartan, "C:/Users/frede/Desktop/Images/bandanabird.png");
}

bool characterHit(std::vector<Character*> charactersInGame, sf::Shape* fbrs, Projectile* projectile){
	for (Character* current : charactersInGame) {
		sf::Shape *characterBS = current->getBoundingShape();
		if (CustomMath::circleIntersectionWithRotatedRectangle(sf::Vector2f(characterBS->getPosition().x - current->getCircleRadius(), characterBS->getPosition().y - current->getCircleRadius()), current->getCircleRadius(), fbrs->getGlobalBounds(), fbrs->getRotation())) {
			sf::Vector2f unitVectorDirection = CustomMath::normalizeUnitVector(current->getSprite().getPosition(), projectile->getSprite().getPosition());
			sf::Vector2f unitVectorOppositeDirection = sf::Vector2f(-unitVectorDirection.x, -unitVectorDirection.y);
			if (current->getID() != projectile->getOwnerID()) {
				current->isHit(unitVectorOppositeDirection);
				//std::cout << "sdaddasda";
				//projectileit = activeAbilities.erase(projectileit);
				return true;
			}
		}

	}

	return false;
}

Game::Game() : viewPos(0,0), windowRect(viewPos.x, viewPos.y, windowWidth, windowHeight)
{
	bool dodge = false;
	loadFonts();
	loadTextures();
	sf::Text healthText;
	healthText.setFont(fh.get(Fonts::orangeJuice));
	//healthText.setFillColor(sf::Color::Blue);
	healthText.setCharacterSize(30);
	sf::Clock dodgeClock;
	sf::Clock globalCooldownClock;
	sf::Clock aiActionClock;
	Player player(rh,1);
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
	sf::View view(windowRect);
	sf::CircleShape innercircle = innercirclecreation();
	//sf::View view(sf::FloatRect(windowWidth / 2, windowHeight / 2, windowWidth, windowHeight));
	window.setView(view);
	window.setFramerateLimit(30);
	//innercircle.setPosition(view.getCenter().x - (innercircle.getGlobalBounds().width / 2), view.getCenter().y - (innercircle.getGlobalBounds().height / 2));
	innercircle.setPosition(view.getCenter().x, view.getCenter().y);
	sf::Vector2f playerPosition(view.getCenter().x, view.getCenter().y);
	player.setPosition(playerPosition);
	//player.getBoundingShape()->setOrigin(player.getSprite().getOrigin());
	std::vector<Projectile*> activeAbilities;
	std::vector<Character*> charactersInGame;
	//activeAbilities.reserve(100000);

	//intersection test
	Sartan s(rh, 3);
	Player p2(rh,2);
	Fireball fb(rh,p2.getID());
	fb.setPosition(sf::Vector2f(400,30));
	fb.changeDirectionToPoint(playerPosition);
	fb.startMoving(playerPosition);
	activeAbilities.push_back(&fb);

	charactersInGame.push_back(&s);
	charactersInGame.push_back(&player);

	while (window.isOpen())
	{
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
		//sf::Shape* mrs = player.getBoundingShape(); 
		/*sf::CircleShape mrs;
		sf::Vector2f circlepos = sf::Vector2f(player.getSprite().getPosition().x - (player.getSprite().getTextureRect().width / 5 / 3.5), player.getSprite().getPosition().y - (player.getSprite().getTextureRect().height / 5 / 2.9));
		float circleradius = 20;
		mrs.setPosition(circlepos);
		
		mrs.setRadius(20);*/
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.getHitState() == Character::NOTHIT) {
			player.startMovingToPoint(pointClicked);
		}
		if (dodge && dodgeClock.getElapsedTime().asSeconds() > dodgeTime) {
			dodge = false;
			s.setDodged(false);
			dodgeClock.restart();
		}
		if (s.getHitState() == Character::NOTHIT && aiActionClock.getElapsedTime().asSeconds() > timeBetweenAIActions) {
			s.act(dodge,activeAbilities);
			aiActionClock.restart();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				if (globalCooldownClock.getElapsedTime().asSeconds() > GLOBAL_COOLDOWN && player.getHitState() == Character::NOTHIT) {
					Fireball* fb = new Fireball(rh,player.getID());
					player.shootProjectile(fb, pointClicked);
					globalCooldownClock.restart();
					activeAbilities.push_back(fb);
					sf::Vector2f pointAfterMove = CustomMath::pointAfterMove(fb->getSprite().getPosition(), CustomMath::distance(fb->getSprite().getPosition(), s.getSprite().getPosition()), fb->getAngle());
					sf::FloatRect oldPosRect = fb->getSprite().getGlobalBounds();
					//std::cout << pointAfterMove.x << " sartan x " << s.getBoundingShape()->getPosition().x << " " <<  pointAfterMove.y << " sartan y " << s.getBoundingShape()->getPosition().y << "\n";
					sf::FloatRect newPosRect = sf::FloatRect(pointAfterMove.x, pointAfterMove.y, oldPosRect.width, oldPosRect.height);
					if (CustomMath::circleIntersectionWithRotatedRectangle(sf::Vector2f(s.getBoundingShape()->getPosition().x - s.getCircleRadius(), s.getBoundingShape()->getPosition().y - s.getCircleRadius()), s.getCircleRadius(), newPosRect, fb->getBoundingShape()->getRotation())) {
						dodge = true; 
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
				//window.draw(*fbrs);
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

