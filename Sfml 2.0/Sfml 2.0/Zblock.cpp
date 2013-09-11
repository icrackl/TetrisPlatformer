#include "Zblock.h"
#include <iostream>


Zblock::Zblock(void)
{
	std::deque<int> temp;
	temp.push_back(5);
	temp.push_back(5);
	temp.push_back(0);
	horizontalMap.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(5);
	temp.push_back(5);
	horizontalMap.push_back(temp);

	temp.clear();
	temp.push_back(0);
	temp.push_back(5);
	verticalMap.push_back(temp);
	temp.clear();
	temp.push_back(5);
	temp.push_back(5);
	verticalMap.push_back(temp);
	temp.clear();
	temp.push_back(5);
	temp.push_back(0);
	verticalMap.push_back(temp);

	shapeMap = horizontalMap;
}


Zblock::~Zblock(void)
{

}

void Zblock::rotate(std::deque<std::deque<int>> leMap){
	if(getState()==1){
		if(getY()>0){
			int tempy = getY() -1;
			int tempx = getX()+1;
			if(Piece::checkRotate(leMap,tempx,tempy,verticalMap)){
				shapeMap = verticalMap;
				setY(tempy);
				setX(tempx);
				setState(0);
			}
		}
	}else{
		int tempy = getY() + 1;
		int tempx = getX() -1;
		if(Piece::checkRotate(leMap,tempx,tempy,horizontalMap)){
			shapeMap = horizontalMap;
			setY(tempy);
			setX(tempx);
			setState(1);
		}
	
	}

}
