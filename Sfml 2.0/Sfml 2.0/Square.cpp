#include "Square.h"


Square::Square(void)
{
	std::deque<int> temp;
	temp.push_back(4);
	temp.push_back(4);

	shapeMap.push_back(temp);
	shapeMap.push_back(temp);
}


Square::~Square(void)
{
}
void Square::rotate(std::deque<std::deque<int>> leMap){
	
}