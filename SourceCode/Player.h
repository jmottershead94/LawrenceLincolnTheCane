#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include <math.h>
#include "Object.h"

class Player : public Object{
	// Attributes.
	public:
		int curLevel;			
		int prevLevel;			
		int score;
		bool enemyTarget;
		bool onPlat;
		bool enemyKilled;
	
	private:
		int frameCounter;
		int gravity;
		bool canJump;
		bool hasJumped;
		bool hasGrappled;
		bool bulletFired;
		
		struct player_t{
			int spriteFrame[9];	// Stores the sprite images.
			int activeFrame;	// Switches between the sprite images.
		};
	
		player_t player;
		Object object;
		
	// Methods.
	public:
		Player();
		void Movement(uint16_t, uint16_t);
		void Determine_Level();
		void Colliding_With_Ground();
		void Set_Platform_Limits();
		
	private:
		void Jump();
		int Grapple_Hook();
		void Attack();
};

class Enemy : public Player{
	public:
		bool enemyBullet;
		bool playerHit;
		
	private:
		struct enemy_t{
			int spriteFrame[9];	
			int activeFrame;	
		};
		
		enemy_t enemy;
		Player p;
		Object obj;
		
	public:
		Enemy();
		void Add_Enemy();
		void Enemy_AI();
		void Attack_Player();
};

#endif