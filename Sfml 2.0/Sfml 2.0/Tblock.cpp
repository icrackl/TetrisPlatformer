#include "Tblock.h"
#include <iostream>


Tblock::Tblock(void)
{
	std::deque<int> temp;
	temp.push_back(0);
	temp.push_back(6);
	temp.push_back(0);
	defaultMap.push_back(temp);
	temp.clear();
	temp.push_back(6);
	temp.push_back(6);
	temp.push_back(6);
	defaultMap.push_back(temp);

	temp.clear();
	temp.push_back(6);
	temp.push_back(0);
	rightMap.push_back(temp);
	temp.clear();
	temp.push_back(6);
	temp.push_back(6);
	rightMap.push_back(temp);
	temp.clear();
	temp.push_back(6);
	temp.push_back(0);
	rightMap.push_back(temp);
	
	temp.clear();
	temp.push_back(6);
	temp.push_back(6);
	temp.push_back(6);
	upsideDownMap.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(6);
	temp.push_back(0);
	upsideDownMap.push_back(temp);

	temp.clear();
	temp.push_back(0);
	temp.push_back(6);
	leftMap.push_back(temp);
	temp.clear();
	temp.push_back(6);
	temp.push_back(6);
	leftMap.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(6);
	leftMap.push_back(temp);


	shapeMap = defaultMap;
}


Tblock::~Tblock(void)
{
}
void Tblock::rotate(std::deque<std::deque<int>> leMap){
	int tempx;
	int tempy;
	switch(getState()){
		case 1:
			tempx = getX()+1;
			if(Piece::checkRotate(leMap,tempx,getY(),rightMap)){
				shapeMap = rightMap;
				setY(getY());
				setX(tempx);
				setState(2);
			}
			break;
		case 2:
			tempx = getX()-1;
			tempy = getY()+1;
			if(Piece::checkRotate(leMap,tempx,tempy,upsideDownMap)){
				shapeMap = upsideDownMap;
				setY(tempy);
				setX(tempx);
				setState(3);
			}
			break;
		case 3:
			tempx = getX();
			tempy = getY()-1;
			if(Piece::checkRotate(leMap,tempx,tempy,leftMap)){
				shapeMap = leftMap;
				setY(tempy);
				setX(tempx);
				setState(4);
			}
			break;
			
		case 4:
			tempx = getX();
			if(Piece::checkRotate(leMap,tempx,getY(),defaultMap)){
				shapeMap = defaultMap;
				setY(getY());
				setX(tempx);
				setState(1);
			}
			break;
	}
}