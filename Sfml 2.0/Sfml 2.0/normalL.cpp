#include "normalL.h"


normalL::normalL(void)
{
	std::deque<int> temp;
	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(3);
	defaultMap.push_back(temp);
	temp.clear();
	temp.push_back(3);
	temp.push_back(3);
	temp.push_back(3);
	defaultMap.push_back(temp);

	temp.clear();
	temp.push_back(3);
	temp.push_back(0);
	rightMap.push_back(temp);
	temp.clear();
	temp.push_back(3);
	temp.push_back(0);
	rightMap.push_back(temp);
	temp.clear();
	temp.push_back(3);
	temp.push_back(3);
	rightMap.push_back(temp);
	
	temp.clear();
	temp.push_back(3);
	temp.push_back(3);
	temp.push_back(3);
	upsideDownMap.push_back(temp);
	temp.clear();
	temp.push_back(3);
	temp.push_back(0);
	temp.push_back(0);
	upsideDownMap.push_back(temp);

	temp.clear();
	temp.push_back(3);
	temp.push_back(3);
	leftMap.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(3);
	leftMap.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(3);
	leftMap.push_back(temp);
	shapeMap = rightMap;
}


normalL::~normalL(void)
{
}

void normalL::rotate(std::deque<std::deque<int>> leMap){
	int tempx;
	int tempy;
	switch(getState()){
		case 1:
			tempx = getX();
			tempy = getY()+1;
			if(Piece::checkRotate(leMap,tempx,tempy,upsideDownMap)){
				shapeMap = upsideDownMap;
				setY(tempy);
				setX(tempx);
				setState(2);
			}
			break;
		case 2:
			tempx = getX();
			tempy = getY();
			if(Piece::checkRotate(leMap,tempx,tempy,leftMap)){
				shapeMap = leftMap;
				setY(tempy);
				setX(tempx);
				setState(3);
			}
			break;
		case 3:
			tempx = getX()-1;
			tempy = getY()+1;
			if(Piece::checkRotate(leMap,tempx,tempy,defaultMap)){
				shapeMap = defaultMap;
				setY(tempy);
				setX(tempx);
				setState(4);
			}
			break;
			
		case 4:
			tempx = getX()+1;
			tempy = getY()-1;
			if(Piece::checkRotate(leMap,tempx,tempy,rightMap)){
				shapeMap = rightMap;
				setY(tempy);
				setX(tempx);
				setState(1);
			}
			break;
	}
}
