#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* pantalla_inicio;

	bool finish_intro;

	unsigned int fx;
	unsigned int ping;

	unsigned int contador;
	unsigned int contador_titulo;
	unsigned int menu_key;

	Animation background;
	Animation zepelin_h;
	Animation zepelin_fire;
	Animation globo;
	Animation bomberman_left;
	Animation bomberman_right;
	Animation arrow;
	Animation flash;
	Animation* x_background;
	Animation* x_zepelin_h;
	Animation* x_zepelin_fire;
	Animation* x_globo;
	Animation* x_bomberman_left;
	Animation* x_bomberman_right;
	Animation* x_arrow;
	Animation* x_flash;

	p2Point<int> pos_zep_h;
	p2Point<int> pos_zep_fire;
	p2Point<int> pos_globo;

	int pos_title;
	int flash_duration;
};