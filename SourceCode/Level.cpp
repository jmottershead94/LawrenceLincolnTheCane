#include "Level.h"

Level::Level(){
	waterFrameCounter = 0;
	Water.activeFrameTopLeft = 0;
	Water.activeFrameTopRight = 0;
	Water.activeFrameBottomLeft = 0;
	Water.activeFrameBottomRight = 0;
	Water.spriteNum[0] = 9;			// First set of water tiles.
	Water.spriteNum[1] = 10;
	Water.spriteNum[2] = 11;
	Water.spriteNum[3] = 12;
	Water.spriteNum[4] = 25;		// Second set of water tiles.
	Water.spriteNum[5] = 26;
	Water.spriteNum[6] = 27;
	Water.spriteNum[7] = 28;
	levelOneDrawn = false;
	levelTwoDrawn = false;
	levelThreeDrawn = false;
	levelFinalDrawn = false;
	levelOne = false;
	levelTwo = false;
	levelThree = false;
	levelFinal = false;
}

void Level::Building(int y, int desiredLength){
	for(int x = rand() % 32; x > 0; x--){
		for(desiredLength = desiredLength; desiredLength > y; desiredLength--)
			SetTile(29, x, desiredLength, 38);
	}
}

void Level::Floor(int x, int y, int desiredLength){
	SetTile(29, x, y, 2);					// Displays the first concrete tile.
	SetTile(29, x, (y + 1), 18);
	SetTile(29, x, (y + 2), 34);
	
	for(int i = 1; i < desiredLength; i += 3){
		SetTile(29,(x + i), y, 3);
		SetTile(29,((x + 1) + i), y, 4);
		SetTile(29,((x + 2) + i), y, 5);
		SetTile(29,(x + i), (y + 1), 19);
		SetTile(29,((x + 1) + i), (y + 1), 20);
		SetTile(29,((x + 2) + i), (y + 1), 21);
		SetTile(29,(x + i), (y + 2), 35);
		SetTile(29,((x + 1) + i), (y + 2), 36);
		SetTile(29,((x + 2) + i), (y + 2), 37);
	}
}

void Level::Big_Cloud(int x, int y){
	SetTile(28, x, y, 50);
	SetTile(28, (x + 1), y, 51);
	SetTile(28, (x + 2), y, 52);
	SetTile(28, x, (y + 1), 66);
	SetTile(28, (x + 1), (y + 1), 67);
	SetTile(28, (x + 2), (y + 1), 68);
}

void Level::Small_Cloud(int x, int y){
	SetTile(28, x, y, 53);
}

void Level::Water_Tile(int x, int y, int desiredLength){
	waterFrameCounter++;
	
	if(waterFrameCounter % 60 == 0){
		waterFrameCounter = 0;
		
		if(Water.activeFrameTopLeft == 0){
			Water.activeFrameTopLeft = 4;
			Water.activeFrameTopRight = 5;
			Water.activeFrameBottomLeft = 6;
			Water.activeFrameBottomRight = 7;
		}
		
		for(int i = 0; i < desiredLength; i += 2){
			SetTile(29, (x + i), (y - 1), Water.spriteNum[Water.activeFrameTopLeft]);
			SetTile(29, ((x + 1) + i), (y - 1), Water.spriteNum[Water.activeFrameTopRight]);
			SetTile(29, (x + i), y, Water.spriteNum[Water.activeFrameBottomLeft]);
			SetTile(29, ((x + 1) + i), y, Water.spriteNum[Water.activeFrameBottomRight]);
		}
	}
}

void Level::Reset_Water(int x, int y, int desiredLength){
	for(int i = 0; i < desiredLength; i += 2){
		SetTile(29, (x + i), (y - 1), 9);
		SetTile(29, ((x + 1) + i), (y - 1), 10);
		SetTile(29, (x + i), y, 11);
		SetTile(29, ((x + 1) + i), y, 12);
	}
}

void Level::Set_Sky(){
	for (int y = 0; y < 32; y++){
		for (int x = 0; x < 32; x++)
			SetTile(27, x, y, 13);	
	}
}

void Level::Set_Level_Template(){
	Set_Sky();
	Floor(0, 17, 31);
	Big_Cloud(1, 3);
	Big_Cloud(3, 9);
	Big_Cloud(10, 4);
	Big_Cloud(17, 8);	
	Big_Cloud(21, 2);		
	Big_Cloud(29, 4);		
	Small_Cloud(2, 7);
	Small_Cloud(4, 4);
	Small_Cloud(6, 10);
	Small_Cloud(13, 8);
	Small_Cloud(15, 2);
	Small_Cloud(24, 1);
	Small_Cloud(25, 10);
	Small_Cloud(26, 2);
}

void Level::Set_Level1(){
	levelOne = true;
	
	if(levelOneDrawn == false && levelOne == true){
		Set_Level_Template();
	
		for(int y = 0; y < 32; y++)
			Building((rand()%y), 14); // Random building locations.
		// Spawns an enemy obstacle.
		levelEnemy.Add_Enemy();
		// Spawns platforms.
		for(int i = 0, n = 4; i < 40, n < 10; i += 8, n++)
			levelObject.Display_Sprite(n, levelObject.platWidth, levelObject.platHeight, levelObject.platY, levelObject.platX + i, false, 10);
		
		levelOneDrawn = true;
	}
}

void Level::Set_Level2(){
	levelOne = false;
	levelTwo = true;
	levelObject.platX = 60;
	
	if(levelTwoDrawn == false){
		Set_Level_Template();
		levelEnemy.Add_Enemy();
		
		for(int i = 0, n = 4; i < 40, n < 10; i += 8, n++)
			levelObject.Display_Sprite(n, levelObject.platWidth, levelObject.platHeight, levelObject.platY + 10, levelObject.platX + i, false, 10);	
		for(int j = 0, m = 10; j < 144, m < 29; j += 8, m++)
			levelObject.Display_Sprite(m, levelObject.platWidth, levelObject.platHeight, levelObject.platY2, levelObject.platX2 + j, false, 10);
				
		levelTwoDrawn = true;
	}
}

void Level::Set_Level3(){
	levelTwo = false;
	levelThree = true;
	levelObject.platX = 198;
	levelObject.platX2 = 0;
	
	if(levelThreeDrawn == false){
		Set_Level_Template();
		levelEnemy.Add_Enemy();
		
		for(int i = 0, n = 4; i < 40, n < 10; i += 8, n++)
			levelObject.Display_Sprite(n, levelObject.platWidth, levelObject.platHeight, levelObject.platY, levelObject.platX + i, false, 10);
		for(int j = 0, m = 10; j < 144, m < 29; j += 8, m++)
			levelObject.Display_Sprite(m, levelObject.platWidth, levelObject.platHeight, levelObject.platY2, levelObject.platX2 + j, false, 10);
		
		levelThreeDrawn = true;
	}
}

void Level::Final_Level(){
	levelThree = false;
	levelFinal = true;
}