#pragma once
#include <memory>
#include "Player.h"
#include "Map.h"
#include "Piece.h"
#include <SFML/Graphics.hpp>
#include "Zblock.h"
#include "Sblock.h"
#include "Tblock.h"
#include "Stick.h"
#include "Square.h"
#include "normalL.h"
#include "reverseL.h"

class Game
{
public:
	Game(void);
	~Game(void);
	void run();
	enum States{Menu,Running,Animation,Pause,End,GameOver};
private:
	Player character;
	Piece *current;
	Piece *next;
	Map map;
	int state;
	sf::RectangleShape leftWall;
	sf::RectangleShape rightWall;
	sf::RectangleShape bottomWall;
	sf::RectangleShape gridBlock;
	int topBuffer;
	sf::Clock clock;
	void initialize();
	void getNextPiece();
	bool update();
	void placeBlocks();
	int score;
	void checkRow(int y, int height);
	int windowWidth;
	int windowHeight;
	void checkPlayerCollision();
	int tileWidth;


};

