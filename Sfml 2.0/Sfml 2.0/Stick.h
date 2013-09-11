#pragma once
#include "piece.h"
class Stick :
	public Piece
{
public:
	Stick(void);
	~Stick(void);
	void rotate(std::deque<std::deque<int>> leMap);
private:
	std::deque<std::deque<int>> horizontalMap;
	std::deque<std::deque<int>> verticalMap;
	int x;
	int y;
};

