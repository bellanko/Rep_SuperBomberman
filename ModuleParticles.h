#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Particle
{
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles(Application* app, bool start_enabled = true);
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void Explosion();

	Particle* AddParticle(const Particle& particle, int x, int y, Uint32 delay = 0);
	
	bool enemy_dead;
	int bomb_range;
	bool bombed;
	bool next_up;
	bool next_down;
	bool next_left;
	bool next_right;
	


private:

	SDL_Texture* graphics;
	p2List<Particle*> active;

public:

	Particle explosion;
	Particle explosionNN;
	Particle explosionN;
	Particle explosionSS;
	Particle explosionS;
	Particle explosionEE;
	Particle explosionE;
	Particle explosionOO;
	Particle explosionO;
	Particle bomb;
	Particle destruction;
};