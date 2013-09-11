#include "Piece.h"
#include <iostream>


Piece::Piece(void):xx(0),yy(0),state(1)
{
}


Piece::~Piece(void)
{
}

void Piece::rotate(std::deque<std::deque<int>> leMap){
	std::cout<<"Piece's rotate"<<std::endl;
}

int Piece::getX(){
	return xx;
}
int Piece::getY(){
	return yy;
}

void Piece::setX(int i){
	xx=i;
}

void Piece::setY(int i){
	yy = i;
}
bool Piece::checkRotate(const std::deque<std::deque<int>> &map,int x, int y,std::deque<std::deque<int>> map2){
	if(y + map2.size()>map.size()){
		return false;
	}
	if(x < 0){
		return false;
	}
	if(x + map2[0].size()>map[0].size()-1){
		return false;
	}
	for(int i = 0; i < map2.size();i++){
		for(int j = 0; j < map2[i].size();j++){
			if(map2[i][j]!=0 && map[y + i][x + j] !=0){
				return false;
			}
		}
	}

	return true;
}
int Piece::getState(){
	return state;
}
void Piece::setState(int i){
	state = i;
}
bool Piece::moveLeft(std::deque<std::deque<int>> map){
	int tempx = getX()-1;
	if(tempx>=0){
		for(int i =0;i<shapeMap.size();i++){
			for(int j = 0; j<shapeMap[i].size();j++){
				if(shapeMap[i][j]!=0 && map[getY()+i][tempx + j] !=0){
					return false;
				}
			}
		}
		setX(tempx);
		return true;
	}
	return false;

}
bool Piece::moveRight(std::deque<std::deque<int>> map){
	int tempx = getX() +1;
	if(tempx + shapeMap[0].size()<=map[0].size()){
		for(int i =0;i<shapeMap.size();i++){
			for(int j = 0; j<shapeMap[i].size();j++){
				if(shapeMap[i][j]!=0 && map[getY()+i][tempx + j] !=0){
					return false;
				}
			}
		}
		setX(tempx);
		return true;
	}
	return false;
	
}
int Piece::getHeight(){
	return shapeMap.size();
}
int Piece::getWidth(){
	return shapeMap[0].size();
}