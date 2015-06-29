#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct Collider;

class ModuleLevelBoss : public Module
{
public:
	ModuleLevelBoss(Application* app, bool start_enabled = true);
	~ModuleLevelBoss();

	unsigned int Longitud(unsigned int n);
	void PrintScore();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* interficie;
	unsigned int fx;

	unsigned int clock;
	unsigned int incremental_score;

	Animation layout;
	Animation layout_raw;
	Animation mid;
	Animation title;
	Animation timer;
	Animation timer_square;

	Animation* x_raw_layout;
	Animation* x_layout;
	Animation* x_mid;
	Animation* x_title;
	Animation* x_timer;
	Animation* x_timer_square;

	Animation zero;
	Animation one;
	Animation two;
	Animation three;
	Animation four;
	Animation five;
	Animation six;
	Animation seven;
	Animation eight;
	Animation nine;

	Animation* x_zero;
	Animation* x_one;
	Animation* x_two;
	Animation* x_three;
	Animation* x_four;
	Animation* x_five;
	Animation* x_six;
	Animation* x_seven;
	Animation* x_eight;
	Animation* x_nine;

	bool win;
	bool lose;
	bool scene_transition;

	int pos_mid;
	int pos_title;
};