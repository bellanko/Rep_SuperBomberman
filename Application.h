#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleLevelBoss.h"
#include "ModuleLevelOne.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleDrawMap.h"
#include "ModuleEnemy.h"
#include "ModuleBoss.h"

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleLevelBoss* level_boss;
	ModuleLevelOne* level_one;
	ModulePlayer* player;
	ModuleEnemy* enemy;
	ModuleBoss* boss;
	ModuleFadeToBlack* fade;
	ModuleSceneIntro* scene_intro;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleDrawMap* map;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};