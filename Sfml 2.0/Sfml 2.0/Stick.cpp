#include "Stick.h"


Stick::Stick(void)
{
	std::deque<int> temp;
	
	temp.push_back(1);
	verticalMap.push_back(temp);
	verticalMap.push_back(temp);
	verticalMap.push_back(temp);
	verticalMap.push_back(temp);
	
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	horizontalMap.push_back(temp);
	shapeMap = verticalMap;
}


Stick::~Stick(void)
{
}
void Stick::rotate(std::deque<std::deque<int>> leMap){
	if(getState()==1){
		if(getY()>0){
			int tempy = getY() + 1;
			int tempx = getX() -1;
			if(Piece::checkRotate(leMap,tempx,tempy,horizontalMap)){
				shapeMap = horizontalMap;
				setY(tempy);
				setState(0);
			}
		}
	}else{
		int tempy = getY() -1;
		int tempx = getX() + 1;
		if(Piece::checkRotate(leMap,tempx,tempy,verticalMap)){
			shapeMap = verticalMap;
			setY(tempy);
			setState(1);
		}
	
	}
}