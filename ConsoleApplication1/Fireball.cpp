#include "Fireball.h"

void manipulateFireballImage(sf::Sprite &fbSprite) {
	fbSprite.setOrigin(fbSprite.getGlobalBounds().width / 2, fbSprite.getGlobalBounds().height / 2);
	fbSprite.scale(0.1, 0.1);
}

Fireball::Fireball(ResourceHolder<sf::Texture, Textures::ID>& rh, int id)
{
	ownerID = id;
	fbrs.setOrigin(10, 20);
	fbrs.setSize(sf::Vector2f(20, 50));
	boundingshape = &fbrs;
	loadTexture(Textures::Fireball, rh);
	manipulateFireballImage(sprite);
	damage = 10;
	cooldown = 0.6;
	movementspeed = 10;
}
void Fireball::setBoundingShape(){
	auto gb = getSprite().getGlobalBounds();
	auto fbrs = getBoundingShape();
	fbrs->setPosition(gb.left + (gb.width / 2), gb.top + (gb.height / 2));
	fbrs->setRotation(getAngle() - 90);

}