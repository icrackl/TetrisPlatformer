#pragma once
#include "piece.h"
class reverseL :
	public Piece
{
public:
	reverseL(void);
	~reverseL(void);
	void rotate(std::deque<std::deque<int>> leMap);
private:
	std::deque<std::deque<int>> defaultMap;
	std::deque<std::deque<int>> rightMap;
	std::deque<std::deque<int>> upsideDownMap;
	std::deque<std::deque<int>> leftMap;
	int x;
	int y;
};

