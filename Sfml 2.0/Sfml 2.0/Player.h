#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Map.h"
class Player
{
public:
	enum Direction{Down, Left, Right, Up};
	Player(void);
	~Player(void);
	bool update();
	std::string getStatus();
	sf::Sprite getPlayer();
	void changeFrame();
	void changeDirection(int d);
	bool isJumping();
	void jump();
	void setPosition(float x, float y);
	void move(float dist);
	bool checkCollision(const Map &m,float dist,int leftPos,int rightPos);
	void checkBelow(const Map &m, int leftPos,int rightPos);
	void fall(const Map &m,float f, int leftPos,int rightPos);

private:
	std::string status;
	sf::Texture texture;
	sf::Sprite playerImage;
	int numFrames;
	bool reverse;
	int direction;
	bool jumping;
	int xFrame;
	int yFrame;
	int playerWidth;
	int playerHeight;
	float yVelocity;
	
	

};

