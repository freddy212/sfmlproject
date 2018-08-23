

#include "Ability.h"
#include "ResourceHolder.h"
#include "Textures.h"
#include "SFML/Graphics.hpp"

class Fireball : public Ability{
private:

	std::string fireballImageDestination = "C:/Users/frede/Desktop/Images/fireball.png";
	sf::RectangleShape fbrs;

public:

	void setBoundingShape();
	Fireball(ResourceHolder <sf::Texture, Textures::ID> &rh, int ownerID);
};
