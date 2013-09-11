#pragma once
#include "piece.h"
class Square :
	public Piece
{
public:
	Square(void);
	~Square(void);
	void rotate(std::deque<std::deque<int>> leMap);
private:
	int x;
	int y;
};

