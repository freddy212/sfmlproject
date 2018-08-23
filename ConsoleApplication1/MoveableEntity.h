#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceHolder.h"
#include "Textures.h"

class MoveableEntity {
protected:
	sf::CircleShape circleshape;
	sf::Vector2f destination;
	sf::Vector2f movementvector;
	sf::Sprite sprite;
	sf::Shape* boundingshape;
	float angle;
	int movementspeed = 3;
	//ResourceHolder<sf::Texture,Textures::ID> rh;

public: 
	void moveInDirection();
	sf::Shape* getBoundingShape();
	virtual void setBoundingShape() = 0;
	void startMoving(sf::Vector2f point);
	void changeDirectionToPoint(sf::Vector2f point);
	void setPosition(sf::Vector2f newpos);
	float getAngle();
	sf::Sprite getSprite();
	int getMovementSpeed();
	sf::Vector2f getMovementVector();
	void loadTexture(Textures::ID id, ResourceHolder <sf::Texture, Textures::ID> &rh);
}; 