#pragma once
#include "piece.h"
class Sblock :
	public Piece
{
public:
	Sblock(void);
	~Sblock(void);
	void rotate(std::deque<std::deque<int>> leMap);
private:
	std::deque<std::deque<int>> horizontalMap;
	std::deque<std::deque<int>> verticalMap;
	int x;
	int y;
	

};

