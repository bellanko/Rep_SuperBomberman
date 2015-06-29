#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

class ModuleDrawMap : public Module
{
public:

	ModuleDrawMap(Application* app, bool start_enabled = true);
	~ModuleDrawMap();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	SDL_Texture* elements;

	Animation* awall;
	Animation* awall_boss;
	Animation* afloor1;
	Animation* afloor2;
	Animation* afloor3;
	Animation* afloor_boss;
	Animation* afalsewall;
	Animation* afinish;
	Animation* abomb;
	Animation* apowerup_speed;
	Animation* apowerup_range;

	Animation wall;
	Animation wall_boss;
	Animation floor1;
	Animation floor2;
	Animation floor3;
	Animation floor_boss;
	Animation falsewall;
	Animation finish;
	Animation bomb;
	Animation powerup_speed;
	Animation powerup_range;

};
