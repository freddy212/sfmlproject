#include "Sartan.h"
#include "CustomMath.h"
#include "Fireball.h"

void Sartan::manipulateSpriteImage(sf::Sprite &sartanSprite) {
	sartanSprite.setOrigin(sartanSprite.getGlobalBounds().width / 2.0, sartanSprite.getGlobalBounds().height / 2.0);
	sartanSprite.scale(0.3, 0.3);
	sartanSprite.rotate(0);
}

Sartan::Sartan(ResourceHolder <sf::Texture, Textures::ID> &rh, int id) {
	ID = id;
	refrh = &rh;
	health = 300;
	movementspeed = 6;
	defaultMovementSpeed = movementspeed;
	sf::Vector2f circlepos = sf::Vector2f(getSprite().getPosition());
	circleradius = 18;
	circleshape.setPosition(circlepos);
	circleshape.setRadius(circleradius);
	circleshape.setOrigin(circleradius, circleradius);
	boundingshape = &circleshape;
	loadTexture(Textures::Sartan, rh);
	manipulateSpriteImage(sprite);
	sprite.setPosition(400, 180);
}
void Sartan::dodgeProjectile() {
	if (dodged) {
		dodged = false;
		int randomNumX = rand() % 500 - 250;
		int randomNumY = rand() % 500 - 250;
		std::cout << "rand x is: " << randomNumX << "rand y is: " << randomNumY << "\n";
		startMovingToPoint(sf::Vector2f(400 + randomNumX, 320 + randomNumY));
	}
}

void Sartan::fireBarrage(std::vector<Projectile*> &activeAbilities){
	int randomNumX = rand() % 300 - 150;
	int randomNumY = rand() % 300 - 150;
	std::vector<std::pair<float, float>> fbdirectionvec;
	fbdirectionvec.push_back(std::make_pair(0,0));
	fbdirectionvec.push_back(std::make_pair(800, 640));
	fbdirectionvec.push_back(std::make_pair(0, 640));
	fbdirectionvec.push_back(std::make_pair(800, 0));
	fbdirectionvec.push_back(std::make_pair(800, 320));
	fbdirectionvec.push_back(std::make_pair(400, 640));
	fbdirectionvec.push_back(std::make_pair(400, 0));
	fbdirectionvec.push_back(std::make_pair(0, 320));
	std::cout << "rannumx" << randomNumX << "\n";
	for (int i = 0; i < fbdirectionvec.size(); i++) {
		Fireball* fb = new Fireball(*refrh, getID());
		shootProjectile(fb, sf::Vector2f(fbdirectionvec[i].first + randomNumX, fbdirectionvec[i].second + randomNumY));
		activeAbilities.push_back(fb);
	}
	/*Fireball* fb2 = new Fireball(*refrh, getID());
	shootProjectile(fb2, sf::Vector2f(800, 640));
	activeAbilities.push_back(fb2);
	Fireball* fb3 = new Fireball(*refrh, getID());
	shootProjectile(fb3, sf::Vector2f(0, 640));
	activeAbilities.push_back(fb3);
	Fireball* fb4 = new Fireball(*refrh, getID());
	shootProjectile(fb4, sf::Vector2f(800, 0));
	activeAbilities.push_back(fb4);*/
}

void Sartan::setDodged(bool idodged)
{
	dodged = idodged;
}

bool Sartan::getDodged()
{
	return dodged;
}

void Sartan::isHit(sf::Vector2f & direction)
{
	Character::isHit(direction);
	setDodged(false);

}

void Sartan::act(std::vector<Projectile*> &activeAbilities) {
	if (!dodged) {
		/*int randomNumX = rand() % 100 - 50;
		int randomNumY = rand() % 80 - 40;
		
		sf::Vector2f newDirection = sf::Vector2f(400 + randomNumX, 320 + randomNumY);
		*/
		sf::Vector2f sartanPos = getSprite().getPosition();
		if (sartanPos.x > 405 || sartanPos.x < 395 || sartanPos.y < 315 || sartanPos.y > 325) {
			startMovingToPoint(sf::Vector2f(400, 320));
		}
		else {
			fireBarrage(activeAbilities);
		}
		defaultMovementVector = movementvector;
	}
	else {
		dodgeProjectile();
	}
}
void Sartan::setBoundingShape() {
	auto mrs = getBoundingShape();
	auto newcirclepos = sprite.getPosition();
	mrs->setPosition(newcirclepos);
}

