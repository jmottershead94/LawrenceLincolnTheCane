#include "Object.h"

Object::Object(){	
	flip = false;
	spriteDisplay = 0;				
	playeryVel = 6;
	playerxVel = 5;
	playerX = 20;
	playerY = 117;
	movingPlayerY = playerY + 8;
	idlePlayerY = movingPlayerY - 8;
	playerWidth = 2;
	playerHeight = 2;
	bulletX = (playerX + (playerWidth * 9));
	bulletY = (playerY + (playerHeight * 4));
	enemyX = 180;
	enemyY = 125;
	enemyWidth = 2;
	enemyHeight = 2;
	enemyBulX = (enemyX - (enemyWidth * 9));
	enemyBulY = (enemyY + (enemyHeight * 4));
	platX = 84;
	platY = 58;
	platX2 = 108;
	platY2 = 48;
	platWidth = 0;
	platHeight = 0;
	groundY = 125;
}

bool Object::Collision(int object1X, int object1Y, int object1Width, int object1Height, int object2X, int object2Y, int object2Width, int object2Height){
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;
	
	left1 = object1X;
	left2 = object2X;		
	right1 = object1X + (object1Width * 8);	
	right2 = object2X + (object2Width * 8);		
	top1 = object1Y; 
	top2 = object2Y;		
	bottom1 = object1Y + (object1Height * 8);
	bottom2 = object2Y + (object2Height * 8);
	
	// Objects are not colliding.
	if(bottom1 < top2)
		return false;
	if(top1 > bottom2)	
		return false;
	if(right1 < left2)
		return false;
	if(left1 > right2)
		return false;
	// Otherwise, objects are colliding.
	return true;
}

int Object::Display_Sprite(int shapeNum, int width, int height, int y, int x, bool flip, int spriteDisplay){
	if(flip == true){
		SetObject(shapeNum,
	          ATTR0_SHAPE(width) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(y),
			  ATTR1_SIZE(height) | ATTR1_X(x) | ATTR1_HFLIP,
			  ATTR2_ID8(spriteDisplay));
			  
			  return 0;
	}
	else if(flip == false){
		SetObject(shapeNum,
	          ATTR0_SHAPE(width) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(y),
			  ATTR1_SIZE(height) | ATTR1_X(x),
			  ATTR2_ID8(spriteDisplay));
			  
			  return 0;
	}
	else{
		return 1;
	}
	
	return 0;
}

