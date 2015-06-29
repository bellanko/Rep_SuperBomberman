#pragma once
#include "Module.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "Globals.h"
#include "p2Point.h"

enum moving {
	downD = 0,
	rightD = 1,
	leftD = 2,
	upD = 3,
	upRightD = 4,
	upLeftD = 5,
	downRightD = 6,
	downLeftD = 7
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool OnCollision(moving);

public:

	SDL_Texture* graphics;

	//Variables for storing fxs
	unsigned int walk_fx;
	unsigned int bomb_fx;
	unsigned int powerup_fx;
	unsigned int explosion_fx;
	
	//Variables for bombs
	p2Point<int> last_bomb_pos;
	unsigned int timerb;
	bool bombdown;
	bool explosion_timer;
	int explosion_sec;



	//Timers for walking sounds
	unsigned int walk_timer;
	unsigned int timerw;

	Animation idle_down;
	Animation idle_up;
	Animation idle_left;
	Animation idle_right;
	Animation idle_invulnerable;
	
	//Animations
	Animation* current_animation;

	Animation up;
	Animation down;
	Animation right;
	Animation left;
	Animation invulnerable;

	Animation dead;
	Animation win;

	//Player Main Points 
	p2Point<int> speed;
	p2Point<int> position;

	//Collision Points
	p2Point<int> array_pos;

	//Other Variables
	int bombs;
	unsigned int score;
	unsigned int life;
	bool player_losses;
	bool player_wins;
	bool powerup_speed;
	bool powerup_range;
};