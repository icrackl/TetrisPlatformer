#include "Player.h"
#include <iostream>


Player::Player(void):status("Default"),reverse(false),jumping(false),xFrame(1),yFrame(Direction::Left),playerWidth(32),playerHeight(32),yVelocity(0)
{
	if(!texture.loadFromFile("luke.png")){
		
	}
	playerImage.setTexture(texture);
	playerImage.setTextureRect(sf::IntRect(xFrame * playerWidth, yFrame * playerHeight, playerWidth, playerHeight));
}


Player::~Player(void)
{
}
sf::Sprite Player::getPlayer(){
	return playerImage;
}
void Player::changeFrame(){
	if(!reverse){
		xFrame++;
		if(xFrame>numFrames){
			reverse = true;
			xFrame-=2;
		}
	}else{
		xFrame--;
		if(xFrame<0){
			reverse = false;
			xFrame+=2;
		}
	}

	switch(direction){
	case Direction::Left:
		yFrame = Direction::Left;
		break;
	case Direction::Right:
		yFrame = Direction::Right;
		break;
	case Direction::Up:
		yFrame = Direction::Up;
		break;
	}
	playerImage.setTextureRect(sf::IntRect(xFrame * playerWidth, yFrame * playerHeight, playerWidth, playerHeight));
}
bool Player::isJumping(){
	return jumping;
}

void Player::setPosition(float x, float y){
	playerImage.setPosition(x,y);
}
void Player::changeDirection(int d){
	direction = d;	
}
void Player::move(float dist){
	switch(direction){
	case Direction::Left:
		playerImage.move(-dist,0);
		break;
		
	case Direction::Right:
		playerImage.move(dist,0);
		break;
	}
}
void Player::jump(){
	jumping = true;
	yVelocity = 350;
}
bool Player::checkCollision(const Map &m,float dist, int leftPos,int rightPos){
	if(direction==Direction::Left){
		int tempx = playerImage.getPosition().x - leftPos-dist;
		int checkx = playerImage.getPosition().x - leftPos-32;
		int tempy = (playerImage.getPosition().y+2)/32;
		int tempy2 = (playerImage.getPosition().y + playerHeight -1)/32;
		if(tempx/32 == checkx/32){
			return true;
		}

		if(tempx<0){
			return false;
		}
		if(m.returnVal(tempx/32,tempy)!=0 || m.returnVal(tempx/32,tempy2)!=0){
			return false;
		}
		return true;
		


	}else{
		int tempx = playerImage.getPosition().x - leftPos + dist+32;
		int checkx = playerImage.getPosition().x - leftPos+32;
		int tempy = (playerImage.getPosition().y+2)/32;
		int tempy2 = (playerImage.getPosition().y + playerHeight-2)/32;
		if(tempx/32 == checkx/32){
			return true;
		}
		if(playerImage.getPosition().x + dist > rightPos-32){
			return false;
		}
		
		for(int i = 0; i < 2; i++){
			if(m.returnVal(tempx/32,tempy)!=0||m.returnVal(tempx/32,tempy2)!=0){
				return false;
			}
		}
		

	}
	return true;
}

void Player::checkBelow(const Map &m, int leftPos,int rightPos){
	int tempx = playerImage.getPosition().x - leftPos+1;
	int tempx2 = tempx + playerWidth/3;
	int tempx3 = tempx + playerWidth * 2 / 3;
	int tempx4 = tempx + playerWidth-1;
	tempx = tempx / 32;
	tempx2 = tempx2/32;
	tempx3 = tempx3/32;
	tempx4 = tempx4/32;
	int tempy = (playerImage.getPosition().y + playerHeight+1)/32;
	if(tempy< m.getHeight()){
		if(m.returnVal(tempx,tempy) ==0 && m.returnVal(tempx4,tempy)==0){
			jumping=true;
		}
	}
}
void Player::fall(const Map &m,float f, int leftPos,int rightPos){

	float temp = yVelocity + -900*f;
	int tempx = playerImage.getPosition().x - leftPos+1;
	int tempx2 = tempx + playerWidth/3;
	int tempx3 = tempx + playerWidth * 2 / 3;
	int tempx4 = tempx + playerWidth-1;
	tempx = tempx/32;
	tempx2 = tempx2/32;
	tempx3 = tempx3/32;
	tempx4 = tempx4/32;
	if(temp >0){
		//check collision going up
		//if hit something, immediately change velocity to 0;
		int tempy = (playerImage.getPosition().y -temp*f)/32;
		if(tempy >=0){
			if(m.returnVal(tempx2,tempy) !=0 || m.returnVal(tempx3,tempy)!=0){
				temp = 0;
				yVelocity = 0;
				playerImage.setPosition(playerImage.getPosition().x,playerImage.getPosition().y - yVelocity*f);
			}else{
				yVelocity = temp;
			}
		}else{
			yVelocity = 0;
			temp = 0;
			playerImage.setPosition(playerImage.getPosition().x,playerImage.getPosition().y - yVelocity*f);
		}
	}else if(temp <=0){
		//check collision going down
		int tempy = (playerImage.getPosition().y -temp*f + playerHeight)/32;
		if(tempy < m.getHeight()){
			if(m.returnVal(tempx2,tempy)!=0 || m.returnVal(tempx3,tempy)!=0){
				temp = 0;
				yVelocity = 0;
				jumping = false;
			}else{
			yVelocity = temp;
			}
		}else{
			jumping = false;
			yVelocity = 0;
		}
	}
	if(yVelocity <-150){
		yVelocity=-150;
	}
	playerImage.setPosition(playerImage.getPosition().x,playerImage.getPosition().y - yVelocity*f);


	
}
