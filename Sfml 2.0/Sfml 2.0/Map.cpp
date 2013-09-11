#include "Map.h"
#include <iostream>


Map::Map(void):updateCount(0),updateTime(10),goalactive(false)
{
	std::deque<int> temp(20);
	for(int i = 0; i < 20; i++){
		map.push_back(temp);
	}
	if(!texture.loadFromFile("exit.png")){
		std::cout<<"no work yo"<<std::endl;
	}
	goal.setTexture(texture);
	goal.setTextureRect(sf::IntRect(1,1,62,62));

}


Map::~Map(void)
{
}

void Map::setGoalPos(int y,int width){
	if(y < 14 && y>=0){
		goal.setPosition(width + (getWidth()/2-1)*32,(y+3)*32);
	}
}
bool Map::shrink(){
	if(map[0].size()>4){
		for(int i = 0; i < map.size();i++){
			map[i].pop_back();
			map[i].pop_front();
		}
		return true;
	}
	return false;
}
void Map::unShrink(){
	if(map[0].size()<20){
		for(int i = 0; i < map.size();i++){
			map[i].push_back(0);
			map[i].push_front(0);
		}
	}
}

int Map::returnVal(int x, int y) const{
	return map[y][x];
}
void Map::setVal(int x, int y, int newVal){
	map[y][x] = newVal;
}
bool Map::checkGoal(int x, int y){
	if(goalactive = true){
		if(x >goal.getPosition().x && x+32 < goal.getPosition().x + 64){
			if(y>goal.getPosition().y && y+32<=goal.getPosition().y + 64){
				return true;
			}
		}
	}else{
		return false;
	}
	return false;
}
int Map::getHeight() const{
	return map.size();
}
int Map::getWidth() const{
	if(map.size()>0){
		return map[0].size();
	}else{
		return -1;
	}
}
int Map::getUpdateTime(){
	return updateTime;
}
bool Map::update(){
	bool s = shrink();
	if (s == true){
		updateCount++;
		if(updateCount == 1){
			items.push_back(goal);
			goalactive = true;
		}
	}

	return s;

}

std::deque<sf::Sprite> Map::getItems(){
	return items;
}
bool Map::goalActive(){
	return goalactive;
}
sf::Sprite Map::getGoal(){
	return goal;
}