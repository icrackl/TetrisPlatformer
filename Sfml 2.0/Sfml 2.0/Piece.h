#pragma once
#include "Block.h"
#include <deque>

class Piece
{
public:
	Piece(void);
	~Piece(void);
	bool moveLeft(std::deque<std::deque<int>> map);
	bool moveRight(std::deque<std::deque<int>> map);
	virtual void rotate(std::deque<std::deque<int>> leMap);
	void setX(int i);
	void setY(int i);
	int getX();
	int getY();
	bool checkRotate(const std::deque<std::deque<int>> &map,int x, int y,std::deque<std::deque<int>> map2);
	std::deque<std::deque<int>> shapeMap;
	void setState(int i);
	int getState();
	int getHeight();
	int getWidth();
	
	
	
private:
	int xx;
	int yy;
	int state;



};

