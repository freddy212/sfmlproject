#include "Game.h"
#include "Fireball.h"
#include "string"
#include "ResourceHolder.h"

ResourceHolder<sf::Texture,Textures::ID> rh;
void testFireball();
void testMovement();

template <class T>
void testeq(std::string testname,T a, T b) {
	a == b ? std::cout <<  testname << " has passed \n" : std::cout << testname << " has failed \n";
}

int mai() {
	testFireball();
	testMovement();
	Game game;
}

void testMovement() {
	//MoveableEntity mv;
	//testeq("movement speed should be 3 ",3, mv.getMovementSpeed());
}
void testFireball() {
	/*Fireball fb(rh,2);
	testeq ("fireball should do 10 damage", 10, fb.getDamage());
	testeq ("fireball should have 1 cooldown", 1, fb.getCooldown());
	testeq ("fireball should have 1 cooldown", 2, fb.getCooldown());*/
}
void testIntersection() {

}
