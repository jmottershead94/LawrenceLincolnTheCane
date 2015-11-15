#ifndef _LEVEL_H_INCLUDED_
#define _LEVEL_H_INCLUDED_

#include "gba.h"
#include "Player.h"
#include <stdlib.h>

class Level : public Player{
	// Attributes.
	private:
		int waterFrameCounter;		// Animates water.
		bool levelOneDrawn;
		bool levelTwoDrawn;
		bool levelThreeDrawn;
		bool levelFinalDrawn;
		bool levelOne;				// Player is on level one.
		bool levelTwo;
		bool levelThree;
		bool levelFinal;
		
		typedef struct
		{
			int spriteNum[8];
			int activeFrameTopLeft;	// Setting up animation frames for each water sprite.
			int activeFrameTopRight;
			int activeFrameBottomLeft;
			int activeFrameBottomRight;
		}Animation;
		
		Animation Water;
		Object levelObject;
		Player levelPlayer;
		Enemy levelEnemy;
	
	// Methods. 
	public:
		Level();
		void Set_Level_Template();
		void Water_Tile(int, int, int);
		void Reset_Water(int, int, int);
		void Set_Level1();
		void Set_Level2();
		void Set_Level3();
		void Final_Level();
		
	private:
		void Building(int, int);
		void Floor(int, int, int);
		void Big_Cloud(int, int);
		void Small_Cloud(int, int);
		void Set_Sky();
};

#endif