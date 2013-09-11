#pragma once
#include <string>
class Block
{
public:
	Block(void);
	~Block(void);
	int getX();
	int getY();
	std::string getColor();
	bool isOccupied();
private:
	int x;
	int y;
	std::string color;
	bool occupied;


};

