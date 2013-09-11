#include "Game.h"
#include <iostream>
#include <algorithm>


Game::Game(void):state(States::Running), topBuffer(0),windowWidth(800),windowHeight(800),tileWidth(32)
{
	
	leftWall.setSize(sf::Vector2f(tileWidth,tileWidth*20));
	leftWall.setPosition(windowWidth/2-32.0*11,1.0*topBuffer);
	leftWall.setFillColor(sf::Color(84,84,84,255));
	rightWall.setSize(sf::Vector2f(tileWidth,tileWidth*20));
	rightWall.setPosition(windowWidth/2+32.0*10,1.0*topBuffer);
	rightWall.setFillColor(sf::Color(84,84,84,255));
	bottomWall.setSize(sf::Vector2f(tileWidth*2 + tileWidth*map.getWidth(),tileWidth));
	bottomWall.setPosition(windowWidth/2-32.0*11,tileWidth*20 + topBuffer);
	bottomWall.setFillColor(sf::Color(84,84,84,255));
	gridBlock.setPosition(windowWidth/2-tileWidth*10,0);
	gridBlock.setSize(sf::Vector2f(tileWidth,tileWidth));
	gridBlock.setFillColor(sf::Color::Yellow);
	gridBlock.setOutlineColor(sf::Color::White);
	gridBlock.setOutlineThickness(2.0);
}


Game::~Game(void)
{

}

void Game::run(){
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris Platformer");
	sf::Clock updateClock;
	sf::Clock buttonClock;
	sf::Clock playerClock;
	sf::Clock fallingClock;
	sf::Clock mapClock;
	sf::Text text;
	sf::Texture winTexture;
	sf::Texture loseTexture;
	if(!winTexture.loadFromFile("winscreen.png")){
	}
	if(!loseTexture.loadFromFile("losescreen.png")){
	}
	sf::Sprite background;

	std::deque<sf::Sprite> thing = map.getItems();
	
	bool pressed = false;
	int buttonTime = 160;
	int playerSpeed = 200;
	int width = 800;
	int height = 800;
	int updateTime = 500;
	sf::Time time = sf::seconds(2);

	time = clock.getElapsedTime();
	srand(time.asMilliseconds());
	map.setGoalPos(rand()%5,leftWall.getPosition().x + tileWidth);
	
	getNextPiece();
	getNextPiece();
	character.setPosition(leftWall.getPosition().x+tileWidth*map.map[0].size()/2,bottomWall.getPosition().y-tileWidth);
	while(window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event))
        {
			switch(event.type){
				case sf::Event::Closed:
					window.close();
					break;
			}
        }
		switch(state){
			case(States::Menu):
				break;
			case(States::Pause):
				break;
			case(States::Running):
				window.clear(sf::Color(135,206,235));
				time = buttonClock.getElapsedTime();
				if(buttonTime < time.asMilliseconds()){
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
						current->rotate(map.map);
						buttonClock.restart();
					}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
						update();
						buttonClock.restart();
					}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
						current->moveRight(map.map);
						buttonClock.restart();
					}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
						current->moveLeft(map.map);
						buttonClock.restart();
					}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
						while(update()){
							checkPlayerCollision();
						}
						updateTime-=10;
						placeBlocks();
						checkRow(current->getY(),current->getHeight());
						getNextPiece();
						updateClock.restart();
						buttonClock.restart();
					}
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
					if(character.isJumping()==false){
							character.jump();
					}
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){

				}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
						if(pressed == false){
							playerClock.restart();
						}else{
							time = playerClock.getElapsedTime();
							character.changeDirection(2);
							character.changeFrame();
							float d = time.asSeconds()*playerSpeed;
							if(character.checkCollision(map,d,leftWall.getPosition().x+tileWidth,rightWall.getPosition().x)){
								character.move(d);
							}
							playerClock.restart();
						}
						pressed = true;
						
				}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
						if(pressed == false){
							playerClock.restart();
								
						}else{
							time = playerClock.getElapsedTime();
							character.changeDirection(1);
							character.changeFrame();
							float d = time.asSeconds()*playerSpeed;
							if(character.checkCollision(map,d,leftWall.getPosition().x+tileWidth,rightWall.getPosition().x)){
								character.move(d);
							}
							playerClock.restart();
						}
						pressed = true;
				}else{
					pressed = false;
				}
				if(character.isJumping()){
					sf::Time t = fallingClock.getElapsedTime();

					character.fall(map,t.asSeconds(),leftWall.getPosition().x+tileWidth,rightWall.getPosition().x);
					fallingClock.restart();
				}else{
					character.checkBelow(map,leftWall.getPosition().x+tileWidth,rightWall.getPosition().x);
					fallingClock.restart();
				}
				time = updateClock.getElapsedTime();
				if(updateTime<time.asMilliseconds()){
					updateClock.restart();
					if(update()==false){
						placeBlocks();
						checkRow(current->getY(),current->getHeight());
						getNextPiece();
						updateTime-=10;
					}
				}
				time = mapClock.getElapsedTime();
				if(map.getUpdateTime() < time.asSeconds()){
					if(map.update()){
						leftWall.setPosition(leftWall.getPosition().x + tileWidth,leftWall.getPosition().y);
						bottomWall.setPosition(bottomWall.getPosition().x + tileWidth, bottomWall.getPosition().y);
						rightWall.setPosition(rightWall.getPosition().x - tileWidth, rightWall.getPosition().y);
						bottomWall.setSize(sf::Vector2f(tileWidth*2 + tileWidth*map.getWidth(),tileWidth));
						mapClock.restart();
						current->setX(current->getX()-1);
						if(map.getWidth()<=4){
							current->setX(0);
						}
						if(current->getX()<0 || current->getX() + current->getWidth()>map.getWidth()){
							getNextPiece();
						}
						checkRow(0,map.getHeight());
					}else{
						state = States::GameOver;
					}
				}
				for(int i = 0; i <map.getWidth();i++){
					for(int j = 0; j < map.getHeight(); j++){
						switch(map.returnVal(i,j)){
							case 0:
								gridBlock.setFillColor(sf::Color(128,128,128,255));
								break;
							case 1:
								gridBlock.setFillColor(sf::Color::Cyan);
								break;
							case 2:
								gridBlock.setFillColor(sf::Color::Blue);
								break;
							case 3:
								gridBlock.setFillColor(sf::Color(255,165,0));
								break;
							case 4:
								gridBlock.setFillColor(sf::Color::Yellow);
								break;
							case 5:
								gridBlock.setFillColor(sf::Color::Green);
								break;
							case 6:
								gridBlock.setFillColor(sf::Color::Magenta);
								break;
							case 7:
								gridBlock.setFillColor(sf::Color::Red);
								break; 
							}
						gridBlock.setPosition(leftWall.getPosition().x + tileWidth + tileWidth*i,leftWall.getPosition().y + tileWidth*j);
						window.draw(gridBlock);
					}
				}
				for(int i = 0; i < current->shapeMap.size();i++){
					for(int j = 0; j < current->shapeMap[i].size(); j++){
						sf::RectangleShape piece;
						piece.setSize(sf::Vector2f(tileWidth,tileWidth));
						piece.setOutlineColor(sf::Color::Black);
						piece.setOutlineThickness(1);
						if(current->shapeMap[i][j]!=0){
							switch(current->shapeMap[i][j]){
							case 1:
								piece.setFillColor(sf::Color::Cyan);
								break;
							case 2:
								piece.setFillColor(sf::Color::Blue);
								break;
							case 3:
								piece.setFillColor(sf::Color(255,165,0));
								break;
							case 4:
								piece.setFillColor(sf::Color::Yellow);
								break;
							case 5:
								piece.setFillColor(sf::Color::Green);
								break;
							case 6:
								piece.setFillColor(sf::Color::Magenta);
								break;
							case 7:
								piece.setFillColor(sf::Color::Red);
								break; 
							}
							
							piece.setPosition(leftWall.getPosition().x + tileWidth + (current->getX()+j)*tileWidth,(i+current->getY())*tileWidth);
							window.draw(piece);
						}
					}
				}
				thing = map.getItems();
				for(int i = 0; i < thing.size();i++){
					window.draw(thing[i]);
				}

				window.draw(leftWall);
				window.draw(rightWall);
				window.draw(bottomWall);
				window.draw(character.getPlayer());
				if(map.checkGoal(character.getPlayer().getPosition().x,character.getPlayer().getPosition().y)){
					state = States::End;
					std::cout<<"reached"<<std::endl;
				}
				checkPlayerCollision();
				break;
			case(States::Animation):
				break;
			case(States::End):
				window.clear();
				text.setString("You Win!");
				text.setStyle(sf::Text::Bold);
				text.setPosition(windowWidth/2-50,windowHeight/2-50);
				text.setColor(sf::Color::Green);
				background.setTexture(winTexture);
				window.draw(background);
				window.draw(text);
				window.draw(character.getPlayer());
				break;
			case(States::GameOver):
				window.clear();
				text.setString("Game Over");
				text.setStyle(sf::Text::Bold);
				text.setPosition(windowWidth/2-50,windowHeight/2-50);
				text.setColor(sf::Color::Red);
				background.setTexture(loseTexture);
				window.draw(background);
				window.draw(text);
				window.draw(character.getPlayer());
				break;
			}
		window.display();
	}
}
void Game::initialize(){


}
void Game::getNextPiece(){
	current = next;
	switch(rand()%7){
	case 0:
		next = new Zblock();
		break;
	case 1:
		next = new Tblock();
		break;
	case 2:
		next = new Square();
		break;
	case 3:
		next = new Sblock();
		break;
	case 4:
		next = new Stick();
		break;
	case 5:
		next = new reverseL();
		break;
	case 6:
		next = new normalL();
		break;
	}
	next->setX(map.map[0].size()/2-1);
	next->setY(0);
}

bool Game::update(){
	if(current->getY() + current->shapeMap.size() >map.map.size()-1)
		return false;
	for(int i = 0; i < current->shapeMap.size();i++){
		for(int j = 0; j<current->shapeMap[i].size();j++){
			if(map.returnVal(current->getX()+j,current->getY()+i+1) !=0 && current->shapeMap[i][j]!=0){
				return false;
				if(current->getY()==0){
					state = States::GameOver;
				}
			}
		}
	}
	current->setY(current->getY() + 1);
	
	return true;
}
void Game::placeBlocks(){
	if(current->getY()==0){
		state = States::GameOver;
	}
	for(int i = 0; i < current->shapeMap.size();i++){
		for(int j = 0; j < current->shapeMap[i].size();j++){
			if(current->shapeMap[i][j]!=0){
				map.setVal(current->getX() + j, current->getY() + i, current->shapeMap[i][j]);
			}
		}
	}
}

void Game::checkRow(int y, int height){
	int total = 0;
	for(int i=0;i<height;i++){
		std::cout<<height<<std::endl;
		int c = 0;
		c = std::count(std::begin(map.map[i+y]),std::end(map.map[i+y]),0);
		if(c==0){
			total+=1;
			map.map.erase(begin(map.map)+i+y);
			std::deque<int> temp;
			for(int j = 0; j < map.getWidth(); j++){
				temp.push_back(0);
			}
			map.map.push_front(temp);
		}
	}
}

void Game::checkPlayerCollision(){
	int x = character.getPlayer().getPosition().x-leftWall.getPosition().x - tileWidth +4;
	int y = character.getPlayer().getPosition().y/tileWidth;
	for(int i = 0; i < current->shapeMap.size();i++){
		for(int j = 0; j< current->shapeMap[i].size(); j++){
			if(current->getX() + j == x/tileWidth && current->getY() + i == y){
				if(current->shapeMap[i][j] !=0){
					state = States::GameOver;
				}
			}
			if(x%tileWidth !=0){
				if(current->getX() + j == x/tileWidth+tileWidth && current->getY() + i == y){
					if(current->shapeMap[i][j] !=0){
						state = States::GameOver;
					}
				}
			}
		}
	}
}
