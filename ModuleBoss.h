#pragma once
#include "Module.h"
#include "Animation.h"
#include "ModuleParticles.h"
#include "Globals.h"
#include "p2Point.h"

enum movement2 {
	downDir2 = 0,
	rightDir2 = 1,
	leftDir2 = 2,
	upDir2 = 3,
};

class ModuleBoss : public Module
{
public:
	ModuleBoss(Application* app, bool start_enabled = true);
	~ModuleBoss();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool OnCollision(movement2);


public:

	SDL_Texture* graphics;

	//Animations
	Animation* current_animation;

	Animation move;
	Animation attack;
	Animation dead;

	p2Point<int> speed;
	p2Point<int> boss_position;

	//Collision Points
	p2Point<int> array_pos;

	//Other Variables
	Particle* last_bomb;

	bool boss_attacks;
	bool boss_dies;
	bool score_received;
};