#pragma once
#include "Piece.h"
class normalL : public Piece
{
public:
	normalL(void);
	~normalL(void);
	void rotate(std::deque<std::deque<int>> leMap);
private:
	std::deque<std::deque<int>> defaultMap;
	std::deque<std::deque<int>> rightMap;
	std::deque<std::deque<int>> upsideDownMap;
	std::deque<std::deque<int>> leftMap;
	int x;
	int y;
};

