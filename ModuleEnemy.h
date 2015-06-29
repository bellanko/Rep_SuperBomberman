#pragma once
#include "Module.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "Globals.h"
#include "p2Point.h"

enum movement {
	downDir = 0,
	rightDir = 1,
	leftDir = 2,
	upDir = 3,
};

class ModuleEnemy : public Module
{
public:
	ModuleEnemy(Application* app, bool start_enabled = true);
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool OnCollision(movement);


public:

	SDL_Texture* graphics;

	unsigned int countdown;

	//Animations
	Animation* current_animation;

	Animation up;
	Animation down;
	Animation right;
	Animation left;

	Animation dead_up;
	Animation dead_down;
	Animation dead_right;
	Animation dead_left;
	Animation blow;

	//Player Main Points 
	p2Point<int> speed;
	p2Point<int> position;

	//Collision Points
	p2Point<int> array_pos;

	//Other Variables
	Particle* last_bomb;

	bool enemy_dies;
	bool score_received;
};