#pragma once
#include "piece.h"
#include <deque>
class Zblock :
	public Piece
{
public:
	Zblock(void);
	~Zblock(void);
	void rotate(std::deque<std::deque<int>> leMap);
private:
	std::deque<std::deque<int>> horizontalMap;
	std::deque<std::deque<int>> verticalMap;
	int x;
	int y;

};

