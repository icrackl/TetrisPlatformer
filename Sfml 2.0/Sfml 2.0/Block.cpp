#include "Block.h"


Block::Block(void):color("default"),occupied(false)
{
}


Block::~Block(void)
{
}
std::string Block::getColor(){
	return color;
}
bool Block::isOccupied(){
	return occupied;
}
