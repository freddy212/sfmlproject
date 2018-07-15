#include "Fireball.h"

void manipulateSpriteImage(sf::Sprite &fbSprite) {
	fbSprite.setOrigin(fbSprite.getGlobalBounds().width / 2, fbSprite.getGlobalBounds().height / 2);
	fbSprite.scale(0.1, 0.1);
}

Fireball::Fireball(ResourceHolder<sf::Texture, Textures::ID>& rh)
{
	loadTexture(Textures::Fireball, rh);
	manipulateSpriteImage(sprite);
	damage = 10;
	cooldown = 1;
}