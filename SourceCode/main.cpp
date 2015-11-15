#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gba.h"
#include "font.h"
#include "Top_Hat_Guyv3.h"
#include "Background_Sprites.h"
#include "Level.h"
#include "bitmap_font_functions.cpp"

// Function Prototypes.
void DrawText(int, int, const char);

// Function Definitions.
void DrawText(int x, int y, const char string[]){
	for(int i = 0; i < strlen(string); i++){
		SetTile(29, x, y, string[i] + 96);
		x += 1;
	}
}

int main()
{
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ;
	
	int waterAni = 0;			// Animates water tiles.
	int frame = 0;
	int frame2 = 0;
	double cloudX = 0.00;		// Scrolls clouds.
	bool titleScreen = true;
	bool gameStarted = false;
	bool gameComplete = false;
	bool gameOver = false;
	
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_BG1CNT = BG_CBB(1) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	REG_BG2CNT = BG_CBB(1) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;
	REG_BG3CNT = BG_CBB(1) | BG_SBB(27) | BG_8BPP | BG_REG_32x32;
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;
	REG_BG1HOFS = 0;
	REG_BG1VOFS = 0;
	REG_BG2HOFS = cloudX;
	REG_BG2VOFS = 0;
	REG_BG3HOFS = 0;
	REG_BG3VOFS = 0;
	
	Object mainObject;	
	Level level;
	Player player;
	Enemy enemy;
	// Loading in the sprites.
	LoadPaletteObjData(0, Top_Hat_Guyv3Pal, sizeof Top_Hat_Guyv3Pal);
	LoadTileData(4, 0, Top_Hat_Guyv3Tiles, sizeof Top_Hat_Guyv3Tiles);
	LoadPaletteBGData(0, Background_SpritesPal, sizeof Background_SpritesPal);
	LoadTileData(1, 2, Background_SpritesTiles, sizeof Background_SpritesTiles);
	
	ClearObjects();
	
	for(int i = 0; i < 128; i++)		// Loads the font tiles.
		LoadTile8(1, i + 96, font_bold[i]);
	
	uint16_t prevButtons = 0;
	
	while (true){
		REG_BG2HOFS = (cloudX += 0.2);
		uint16_t curButtons = REG_KEYINPUT;
		waterAni++;
		frame++;
		frame2++;
		// Main game.
		if(titleScreen == true){
			DrawText(6, 5, "Lawrence Lincoln:");
			DrawText(10, 6, "The Cane");
			DrawText(9, 11, "Press START");
			// Sets the title screen layout.
			level.Set_Level_Template();
		}
	
		if(((curButtons & KEY_START) == 0) && ((prevButtons & KEY_START) != 0) && (titleScreen == true)){
			titleScreen = false;
			gameStarted = true;
			DrawText(6, 5, "                 ");	// "Erases" the title screen text.
			DrawText(10, 6, "        ");
			DrawText(9, 11, "           ");
		}
		
		if(titleScreen == false && gameStarted == true){
			char buf[40];
			snprintf(buf, sizeof buf, "Score: %03d", player.score);
			DrawText(0, 2, buf);
			player.Set_Platform_Limits();
			player.Movement(curButtons, prevButtons);
			player.Determine_Level();
			
			if((player.enemyKilled != true)){			
				if(frame % 90 == 0){
					frame = 0;
					enemy.Enemy_AI();
					
					if(enemy.enemyBullet == true){
						if((frame2 % 60) == 0){
							frame2 = 0;
							// Enemy bullet disappears.
							SetObject(29,
								ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(1),
								ATTR1_SIZE(1) | ATTR1_X(1),
								ATTR2_ID8(0));
						}
						// If the player is hit by the enemy.
						if(enemy.playerHit == true && player.onPlat == false && player.enemyTarget == true){
							player.score -= 20;
							if(player.score <= 0){
								gameStarted = false;
								gameOver = true;
							}
						}
					}
				}
			}
			// Changes the level that the player is on.
			if(player.curLevel == 1)
				level.Set_Level1();
			if(player.curLevel == 2)
				level.Set_Level2();
			if(player.curLevel == 3)
				level.Set_Level3();
			if(player.curLevel == 4){
				gameComplete = true;
				gameStarted = false;
			}
			// Checks if the player is touching a surface.
			player.Colliding_With_Ground();
		}
		// Sets initial water tiles.
		level.Water_Tile(0, 16, 30);
		// Animating the water.
		if(waterAni % 90 == 0){
			waterAni = 0;
			level.Reset_Water(0, 16, 32);
		}
		
		if(gameComplete == true && gameStarted == false){
			// Clears the screen and all objects.
			for(int a = 0; a < 32; a++){
				for(int b = 0; b < 15; b++){
					DrawText(a, b, " ");
					SetObject(a,
						  ATTR0_SHAPE(3) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(b),
						  ATTR1_SIZE(2) | ATTR1_X(a),
						  ATTR2_ID8(0));
				}
			}
			DrawText(6, 6, "You have won!");
			DrawText(6, 7, "You are the Mayor now!");
			DrawText(6, 9, "Your ");
			char buf[40];
			snprintf(buf, sizeof buf, "score: %03d", player.score);
			DrawText(11, 9, buf);
		}
		
		if(gameOver == true && gameStarted == false){
			for(int a = 0; a < 32; a++){
				for(int b = 0; b < 15; b++){
					DrawText(a, b, " ");
					SetObject(a,
						  ATTR0_SHAPE(3) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(b),
						  ATTR1_SIZE(2) | ATTR1_X(a),
						  ATTR2_ID8(0));
				}
			}
			DrawText(6, 6, "You have died.");
		}
		
		prevButtons = curButtons;
		WaitVSync();
		UpdateObjects();
	}

	return 0;
}