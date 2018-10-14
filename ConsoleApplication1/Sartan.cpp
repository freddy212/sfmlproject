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
	movementspeed = 5;
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
	if (!dodged) {
		dodged = true;
		int randomNumX = rand() % 125 - 250;
		int randomNumY = rand() % 125 - 250;
		startMovingToPoint(sf::Vector2f(400 + randomNumX, 320 + randomNumY));
	}
}

void Sartan::fireBarrage(std::vector<Projectile*> &activeAbilities){
	Fireball* fb1 = new Fireball(*refrh, getID());
	shootProjectile(fb1, sf::Vector2f(0, 0));
	activeAbilities.push_back(fb1);
	Fireball* fb2 = new Fireball(*refrh, getID());
	shootProjectile(fb2, sf::Vector2f(800, 640));
	activeAbilities.push_back(fb2);
	Fireball* fb3 = new Fireball(*refrh, getID());
	shootProjectile(fb3, sf::Vector2f(0, 640));
	activeAbilities.push_back(fb3);
	Fireball* fb4 = new Fireball(*refrh, getID());
	shootProjectile(fb4, sf::Vector2f(800, 0));
	activeAbilities.push_back(fb4);
}

void Sartan::setDodged(bool idodged)
{
	dodged = idodged;
}

void Sartan::act(bool dodge, std::vector<Projectile*> &activeAbilities) {
	if (!dodge) {
		int randomNumX = rand() % 100 - 50;
		int randomNumY = rand() % 80 - 40;
		sf::Vector2f newDirection = sf::Vector2f(400 + randomNumX, 320 + randomNumY);
		startMovingToPoint(newDirection);
		defaultMovementVector = movementvector;
		fireBarrage(activeAbilities);
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

