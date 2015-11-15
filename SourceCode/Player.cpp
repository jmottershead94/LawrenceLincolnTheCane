#include "Player.h"

Player::Player(){
	frameCounter = 0;
	gravity = 1;
	curLevel = 1;
	prevLevel = curLevel - 1;
	score = 0;
	enemyTarget = false;
	onPlat = false;
	enemyKilled = false;
	canJump = false;			
	hasJumped = false;
	hasGrappled = false;
	bulletFired = false;
	player.activeFrame = 0;		// Setting up active frame for use in player animations.
	player.spriteFrame[0] = 0;	// Idle Front Sprite.
	player.spriteFrame[1] = 2;	// Idle Back Sprite.
	player.spriteFrame[2] = 4;	// Idle Side Sprite.
	player.spriteFrame[3] = 6;	// Idle Attacking Side Sprite.
	player.spriteFrame[4] = 8;	// Idle Grappling Side Sprite.
	player.spriteFrame[5] = 86;	// Moving Attacking Side Sprite.
	player.spriteFrame[6] = 2;	// Moving Side Sprite.
	player.spriteFrame[7] = 82;	// Moving Up Sprite.
	player.spriteFrame[8] = 80;	// Moving Down Sprite.
}

/*--Plays--Animations--*/
void Player::Movement(uint16_t curButtons, uint16_t prevButtons)
{
	frameCounter++;
	
	if(frameCounter% 10 == 0){
		frameCounter = 0;
		
		if(bulletFired == true){							// Makes the players bullet invisible once fired.
			SetObject(3,
				ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(object.bulletY),
				ATTR1_SIZE(1) | ATTR1_X(object.bulletX),
				ATTR2_ID8(0));
		}
		
		if((curButtons & KEY_LEFT) == 0){	
			if((object.playerY <= object.platY2 - 24)){		// Player is on platform 2.
				if(player.activeFrame == 2)
					player.activeFrame = 6;
				else
					player.activeFrame = 2;
				
				object.playerY = object.platY2 - 32;
				spriteDisplay = player.spriteFrame[player.activeFrame];						
				flip = true;
				object.playerX -= object.playerxVel;
			}
			else if((object.playerY <= object.platY - 16)){
				if(player.activeFrame == 2)
					player.activeFrame = 6;
				else
					player.activeFrame = 2;
				
				object.playerY = (object.platY - 24);
				spriteDisplay = player.spriteFrame[player.activeFrame];						
				flip = true;
				object.playerX -= object.playerxVel;
			}
			else if(hasGrappled == false && object.playerX >= 5){
				if(player.activeFrame == 2)
					player.activeFrame = 6;
				else
					player.activeFrame = 2;
				
				spriteDisplay = player.spriteFrame[player.activeFrame];							
				flip = true;
				object.playerX -= object.playerxVel;
			}
		}
		
		if((curButtons & KEY_RIGHT) == 0){	
			flip = false;	
			if((object.playerY <= object.platY2 - 24)){
				if(player.activeFrame == 2)
					player.activeFrame = 6;
				else
					player.activeFrame = 2;
				
				object.playerY = (object.platY2 - 32);
				spriteDisplay = player.spriteFrame[player.activeFrame];
				object.playerX += object.playerxVel;
			}
			else if((object.playerY <= object.platY - 16)){
				if(player.activeFrame == 2)
					player.activeFrame = 6;
				else
					player.activeFrame = 2;
				
				object.playerY = (object.platY - 24);
				spriteDisplay = player.spriteFrame[player.activeFrame];
				object.playerX += object.playerxVel;
			}
			else if(hasGrappled == false && object.playerX <= 223){
				if(player.activeFrame == 2)
					player.activeFrame = 6;
				else
					player.activeFrame = 2;
				
				spriteDisplay = player.spriteFrame[player.activeFrame];
				object.playerX += object.playerxVel;
			}
		}
		
		if((curButtons & KEY_UP) == 0){	// GRAPPLING.	
			if(hasGrappled == true && (object.playerY <= (object.platY - 16)) && (object.playerX > object.platX) && (object.playerX + (object.playerWidth * 8) < (object.platX + 40)))
				object.playerY = object.platY - 24;
			else if(hasGrappled == false && (object.playerY <= (object.platY2 - 24)) && (object.playerX > object.platX2) && (object.playerX + (object.playerWidth * 8)  < (object.platX2 + 144)))
				object.playerY = object.platY2 - 32;
			else if(hasGrappled == false){				
				if(object.playerY <= (object.platY - 16))
					object.playerY = object.platY - 24;
				else if(object.playerY <= (object.platY2 - 24))
					object.playerY = object.platY2 - 32;
				else if(object.playerY >= 117 && object.playerY <= 125)
					Grapple_Hook();
			}
			
			player.activeFrame = 4;
			spriteDisplay = player.spriteFrame[player.activeFrame];
		}
		
		if((curButtons & KEY_A) == 0){	// JUMPING.
			canJump = true;
			hasJumped = false;
			object.playeryVel = 6;
			Jump();
		}
		
		if((curButtons & KEY_B) == 0){	// ATTACKING.
			bulletFired = false;
			Attack();
			
			if(hasGrappled == true && (object.playerY <= (object.platY - 16)) && (object.playerX > object.platX) && (object.playerX + (object.playerWidth * 8) < (object.platX + 40))){
				object.playerY = object.platY - 24;
				object.bulletY = object.platY - 24;
			}
			else if(hasGrappled == false && (object.playerY <= (object.platY2 - 24)) && (object.playerX > object.platX2) && (object.playerX + (object.playerWidth * 8) < (object.platX2 + 144))){
				object.playerY = object.platY2 - 32;
				object.bulletY = object.platY2 - 32;
			}
			
			player.activeFrame = 3;
			spriteDisplay = player.spriteFrame[player.activeFrame];	
		}
	}
	
	object.Display_Sprite(0, object.playerWidth, object.playerHeight, object.playerY, object.playerX, flip, spriteDisplay);
}

void Player::Jump(){	
	int time = 4;
	hasJumped = false;
	object.playeryVel = 6;

	for(int i = 0; i < time; i++){
		object.playerY -= ((object.playeryVel * i) + (gravity * i^2)); // suvat equation: s = ut + (at^2).
		//object.bulletY = object.playerY;
		
		if(flip == true && (object.playerX > 7))
			object.playerX -= (object.playerxVel * i);
		else if(flip == false && (object.playerX + (object.playerWidth * 8) < 215))
			object.playerX += (object.playerxVel * i);
	}
		
	hasJumped = true;
}

int Player::Grapple_Hook(){
	hasGrappled = true;
	int platEdgeL = object.platX;											// Left grapple target.
	int platEdgeR = (object.platX + (object.platWidth * 8)) + 24;			// Right grapple target.
	int platSide = (object.platY - 3);										// Used to work out platform height from the player.

	if(object.playerX <= platEdgeL){		
		object.playerY = object.platY - 32;
		object.playerX = object.platX;
		object.bulletY = object.platY - 32;
		onPlat = true;
		return 0;
	}
	else if(object.playerX >= platEdgeR){		
		object.playerY = object.platY - 32;
		object.playerX = object.platX + 35;
		object.bulletY = object.platY - 32;
		onPlat = true;
		return 0;
	}
	else{
		return 1;
	}
}

void Player::Attack(){
	if(flip == true && bulletFired == false){							
		for(int j = 0; j < ((15 - object.playerX) * -1); j++){		// Works out the distance to the left of the player the top hat will travel.			
			object.bulletX = (object.playerX - (object.playerWidth * 8));
			object.Display_Sprite(3, 0, 1, object.bulletY, (object.bulletX -= j), false, 0);
			
			if(object.Collision(object.bulletX, object.bulletY, 2, 1, object.enemyX, object.enemyY, object.enemyWidth, object.enemyHeight) == true){
				object.bulletX = (object.enemyX - (object.enemyWidth * 8));
				object.enemyY = 10;
				// Enemy disappears.
				SetObject(1,
							ATTR0_SHAPE(object.enemyWidth) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(object.enemyY),
							ATTR1_SIZE(object.enemyHeight) | ATTR1_X(object.enemyX),
							ATTR2_ID8(0));
		
				enemyKilled = true;
				break;
			}
			
			bulletFired = true;
		}
	}
	else if(flip == false && bulletFired == false){
		for(int i = 0; i < (212 - object.playerX); i++){
			object.bulletX = (object.playerX + (object.playerWidth * 8));			
			object.Display_Sprite(3, 0, 1, object.bulletY, (object.bulletX += i), false, 0);
		
			if(object.Collision(object.bulletX, object.bulletY, 2, 1, object.enemyX, object.enemyY, object.enemyWidth, object.enemyHeight) == true){
				object.bulletX = (object.enemyX - (object.enemyWidth * 8));
				object.enemyY = 10;
				// Enemy disappears.
				SetObject(1,
							ATTR0_SHAPE(object.enemyWidth) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(object.enemyY),
							ATTR1_SIZE(object.enemyHeight) | ATTR1_X(object.enemyX),
							ATTR2_ID8(0));
				
				enemyKilled = true;
				break;
			}
			
			bulletFired = true;
		}
	}
	
	if(enemyKilled == true && bulletFired == true)
		score += 50;
}

void Player::Determine_Level(){
	if((object.playerX + (object.playerWidth * 8) >= 220) && (curLevel != 4)){
		curLevel++;
		object.playerX = 10;
		object.enemyY = 117;		
		enemyKilled = false;
	}
}

void Player::Colliding_With_Ground(){
	// Player is above the ground floor.
	if((object.playerY < 117)){ 
		if((object.Collision(object.playerX, object.playerY, object.playerWidth - 1, object.playerHeight + 1, object.platX, object.platY, 5, 1) == true) || (object.Collision(object.playerX, object.playerY, object.playerWidth, object.playerHeight + 1, object.platX2, object.platY2, 18, 1) == true)){
			onPlat = true;
			object.playeryVel = 0;
		}
		if((object.playerY == (object.platY - 24) && ((object.playerX + 8) < object.platX)) || (object.playerY == (object.platY - 24) && (object.playerX > (object.platX + 40)))){
			if((object.Collision(object.playerX, object.playerY, object.playerWidth - 1, object.playerHeight + 1, object.platX, object.platY, 5, 1) == true) || (object.Collision(object.playerX, object.playerY, object.playerWidth, object.playerHeight + 1, object.platX2, object.platY2, 18, 1) == true)){
				onPlat = true;
				object.playeryVel = 0;
			}
			else{
				onPlat = false;
				object.playeryVel += gravity;
			}
			
			hasGrappled = false;
		}
		else if((object.playerY == (object.platY2 - 32) && ((object.playerX + 8) < object.platX2)) || (object.playerY == (object.platY2 - 32) && (object.playerX > (object.platX2 + 120)))){
			if((object.Collision(object.playerX, object.playerY, object.playerWidth - 1, object.playerHeight + 1, object.platX, object.platY, 5, 1) == true) || (object.Collision(object.playerX, object.playerY, object.playerWidth, object.playerHeight + 1, object.platX2, object.platY2, 18, 1) == true)){
				onPlat = true;
				object.playeryVel = 0;
			}
			else{
				onPlat = false;
				object.playeryVel += gravity;
			}
			
			hasGrappled = false;
		}
		else if(object.playerY == (object.platY2 - 32)){
			onPlat = true;
			object.playeryVel = 0;
			hasGrappled = false;
		}	
		else if(object.playerY == (object.platY - 24)){
			onPlat = true;
			object.playeryVel = 0;
			hasGrappled = false;
		}
	}
	else if(object.playerY >= 117 && object.playerY <= 125){
		onPlat = false;
		object.playeryVel = 0;
		object.bulletY = object.playerY;
		
		if(object.playerX >= 20 && object.playerX <= 52)	// Area targeted by the enemy.
			enemyTarget = true;
		else
			enemyTarget = false;
	}
	
	object.playerY += object.playeryVel;
}

void Player::Set_Platform_Limits(){
	if(curLevel == 1){}
	else if(curLevel == 2){
		object.platX = 60;
		object.platY = 60;
	}
	else if(curLevel == 3){
		object.platX = 198;
		object.platY = 50;
		object.platX2 = 0;
	}
}
// Enemy sub-class.
Enemy::Enemy(){
	playerHit = false;
	enemyBullet = false;
	enemy.activeFrame = 0;
	enemy.spriteFrame[0] = 80;	// Idle Front Sprite.
	enemy.spriteFrame[1] = 82;	// Idle Side Attacking Sprite.
}

void Enemy::Add_Enemy(){
	spriteDisplay = enemy.spriteFrame[enemy.activeFrame];
	enemy.activeFrame = 0;
	obj.Display_Sprite(1, obj.enemyWidth, obj.enemyHeight, obj.enemyY, obj.enemyX, false, spriteDisplay);
}

void Enemy::Enemy_AI(){
	Attack_Player();
}

void Enemy::Attack_Player(){
	enemyBullet = false;
	obj.Display_Sprite(1, obj.enemyWidth, obj.enemyHeight, obj.enemyY, obj.enemyX, flip, enemy.spriteFrame[0]);
	
	if((obj.playerX < obj.enemyX) && enemyBullet == false){
		flip = true;
		enemy.activeFrame = 1;
		spriteDisplay = enemy.spriteFrame[enemy.activeFrame];
		
		for(int j = 0; j < ((15 - obj.enemyX) * -1); j++){				
			obj.enemyBulX = (obj.enemyX - (obj.enemyWidth * 8));
			obj.Display_Sprite(29, 0, 1, obj.enemyBulY, (obj.enemyBulX -= j), false, 58);
			
			if(obj.Collision(obj.enemyBulX, obj.enemyBulY, 0, 1, obj.playerX, obj.playerY, obj.playerWidth, obj.playerHeight) == true){
				obj.enemyBulX = (obj.playerX - (obj.playerWidth * 8));
				// Player has died.
				SetObject(1,
							ATTR0_SHAPE(obj.playerWidth + 1) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(obj.playerY),
							ATTR1_SIZE(obj.playerHeight + 1) | ATTR1_X(obj.playerX),
							ATTR2_ID8(0));
		
				playerHit = true;
				break;
			}
			
			enemyBullet = true;
		}
	}
	else if((obj.playerX > obj.enemyX) && enemyBullet == false){
		flip = false;
		enemy.activeFrame = 1;
		spriteDisplay = enemy.spriteFrame[enemy.activeFrame];
		
		for(int i = 0; i < (212 - obj.enemyX); i++){
			obj.enemyBulX = (obj.enemyX + (obj.enemyWidth * 8));			
			obj.Display_Sprite(3, 0, 1, obj.enemyBulY, (obj.enemyBulX += i), false, 58);
		
			if(obj.Collision(obj.enemyBulX, obj.enemyBulY, 0, 1, obj.playerX, obj.playerY, obj.playerWidth, obj.playerHeight) == true){
				obj.enemyBulX = (obj.playerX - (obj.playerWidth * 8));
				SetObject(1,
							ATTR0_SHAPE(obj.playerWidth) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(obj.playerY),
							ATTR1_SIZE(obj.playerHeight) | ATTR1_X(obj.playerX),
							ATTR2_ID8(0));
		
				playerHit = true;
				break;
			}
			
			enemyBullet = true;
		}
	}

	obj.Display_Sprite(1, obj.enemyWidth, obj.enemyHeight, obj.enemyY, obj.enemyX, flip, spriteDisplay);
}