#ifndef _OBJECT_H_INCLUDED_
#define _OBJECT_H_INCLUDED_

#include "gba.h"

class Object{
	// Attributes.
	public:	
		bool flip;
		int playeryVel, playerxVel;
		int playerX, playerY, movingPlayerY, idlePlayerY;
		int playerWidth, playerHeight;
		int bulletX, bulletY;
		int enemyBulX, enemyBulY;
		int enemyX, enemyY;
		int enemyWidth, enemyHeight;
		int platX, platY, platX2, platY2;
		int platWidth, platHeight;
		int groundY;
		int spriteDisplay;		// Tile number.
	
	// Methods.
	public:
		Object();
		bool Collision(int, int, int, int, int, int, int, int);
		int Display_Sprite(int, int, int, int, int, bool, int);
};

#endif