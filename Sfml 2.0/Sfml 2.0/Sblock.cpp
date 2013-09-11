#include "Sblock.h"
#include <iostream>


Sblock::Sblock(void):x(0),y(0)
{
	std::deque<int> temp;
	temp.push_back(0);
	temp.push_back(7);
	temp.push_back(7);
	horizontalMap.push_back(temp);
	temp.clear();
	temp.push_back(7);
	temp.push_back(7);
	temp.push_back(0);
	horizontalMap.push_back(temp);

	temp.clear();
	temp.push_back(7);
	temp.push_back(0);
	verticalMap.push_back(temp);
	temp.clear();
	temp.push_back(7);
	temp.push_back(7);
	verticalMap.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(7);
	verticalMap.push_back(temp);

	shapeMap = horizontalMap;
}


Sblock::~Sblock(void)
{
}
void Sblock::rotate(std::deque<std::deque<int>> leMap){
	if(getState()==1){
		if(getY()>0){
			int tempy = getY() -1;
			if(Piece::checkRotate(leMap,getX(),tempy,verticalMap)){
				shapeMap = verticalMap;
				setY(tempy);
				setState(0);
			}
		}
	}else{
		int tempy = getY() + 1;
		if(Piece::checkRotate(leMap,getX(),tempy,horizontalMap)){
			shapeMap = horizontalMap;
			setY(tempy);
			setState(1);
		}
	
	}
	
}