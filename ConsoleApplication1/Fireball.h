

#include "Ability.h"
#include "ResourceHolder.h"
#include "Textures.h"
#include "SFML/Graphics.hpp"

class Fireball : public Ability{
private:
	std::string fireballImageDestination = "C:/Users/frede/Desktop/Images/fireball.png";

public:
	Fireball(ResourceHolder <sf::Texture, Textures::ID> &rh);
};
