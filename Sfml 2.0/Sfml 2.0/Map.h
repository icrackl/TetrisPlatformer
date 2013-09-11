#pragma once
#include <deque>
#include <SFML/Graphics.hpp>
class Map
{
public:
	Map(void);
	~Map(void);
	std::deque<std::deque<int>> map;
	bool shrink();
	void unShrink();
	int returnVal(int x, int y) const;
	void setVal(int x, int y, int newVal);
	virtual bool checkGoal(int x, int y);
	bool update();
	int getWidth() const;
	int getHeight() const;
	int getLeftWallPos();
	int getRightWallPos();
	int getUpdateTime();
	void setGoalPos(int y, int width);
	std::deque<sf::Sprite> getItems();
	bool goalActive();
	sf::Sprite getGoal();
private:
	int updateTime;
	int updateCount;
	sf::Sprite goal;
	sf::Texture texture;
	std::deque<sf::Sprite> items;
	bool goalactive; 

	
};

