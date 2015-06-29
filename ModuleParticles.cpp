#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Resources/Elements.png");

	bomb_range = 1;

	//Bomb
	bomb.anim.frames.PushBack({ 176, 24, 16, 16 });
	bomb.anim.frames.PushBack({ 192, 24, 16, 16 });
	bomb.anim.frames.PushBack({ 208, 24, 16, 16 });
	bomb.anim.frames.PushBack({ 192, 24, 16, 16 });
	bomb.anim.frames.PushBack({ 176, 24, 16, 16 });
	bomb.anim.frames.PushBack({ 192, 24, 16, 16 });
	bomb.anim.frames.PushBack({ 208, 24, 16, 16 });
	bomb.anim.frames.PushBack({ 192, 24, 16, 16 });
	bomb.anim.frames.PushBack({ 176, 24, 16, 16 });
	bomb.anim.frames.PushBack({ 192, 24, 16, 16 });
	bomb.life = 3300;
	bomb.anim.loop = false;
	bomb.anim.speed = 0.05f;

	explosion.anim.frames.PushBack({ 32, 72, 16, 16 });
	explosion.anim.frames.PushBack({ 112, 72, 16, 16 });
	explosion.anim.frames.PushBack({ 192, 72, 16, 16 });
	explosion.anim.frames.PushBack({ 272, 72, 16, 16 });
	explosion.anim.frames.PushBack({ 352, 72, 16, 16 });
	explosion.anim.frames.PushBack({ 272, 72, 16, 16 });
	explosion.anim.frames.PushBack({ 192, 72, 16, 16 });
	explosion.anim.frames.PushBack({ 112, 72, 16, 16 });
	explosion.anim.frames.PushBack({ 32, 72, 16, 16 });

	explosion.life = 800;
	explosion.anim.loop = false;
	explosion.anim.speed = 0.2f;

	explosionS.anim.frames.PushBack({ 32, 87, 16, 16 });
	explosionS.anim.frames.PushBack({ 112, 87, 16, 16 });
	explosionS.anim.frames.PushBack({ 192, 87, 16, 16 });
	explosionS.anim.frames.PushBack({ 272, 87, 16, 16 });
	explosionS.anim.frames.PushBack({ 352, 87, 16, 16 });
	explosionS.anim.frames.PushBack({ 272, 87, 16, 16 });
	explosionS.anim.frames.PushBack({ 192, 87, 16, 16 });
	explosionS.anim.frames.PushBack({ 112, 87, 16, 16 });
	explosionS.anim.frames.PushBack({ 32, 87, 16, 16 });

	explosionS.life = 800;
	explosionS.anim.loop = false;
	explosionS.anim.speed = 0.2f;

	explosionSS.anim.frames.PushBack({ 32, 103, 16, 16 });
	explosionSS.anim.frames.PushBack({ 112, 103, 16, 16 });
	explosionSS.anim.frames.PushBack({ 192, 103, 16, 16 });
	explosionSS.anim.frames.PushBack({ 272, 103, 16, 16 });
	explosionSS.anim.frames.PushBack({ 352, 103, 16, 16 });
	explosionSS.anim.frames.PushBack({ 272, 103, 16, 16 });
	explosionSS.anim.frames.PushBack({ 192, 103, 16, 16 });
	explosionSS.anim.frames.PushBack({ 112, 103, 16, 16 });
	explosionSS.anim.frames.PushBack({ 32, 103, 16, 16 });

	explosionSS.life = 800;
	explosionSS.anim.loop = false;
	explosionSS.anim.speed = 0.2f;

	explosionN.anim.frames.PushBack({ 32, 56, 16, 16 });
	explosionN.anim.frames.PushBack({ 112, 56, 16, 16 });
	explosionN.anim.frames.PushBack({ 192, 56, 16, 16 });
	explosionN.anim.frames.PushBack({ 272, 56, 16, 16 });
	explosionN.anim.frames.PushBack({ 352, 56, 16, 16 });
	explosionN.anim.frames.PushBack({ 272, 56, 16, 16 });
	explosionN.anim.frames.PushBack({ 192, 56, 16, 16 });
	explosionN.anim.frames.PushBack({ 112, 56, 16, 16 });
	explosionN.anim.frames.PushBack({ 32, 56, 16, 16 });

	explosionN.life = 800;
	explosionN.anim.loop = false;
	explosionN.anim.speed = 0.2f;

	explosionNN.anim.frames.PushBack({ 32, 40, 16, 16 });
	explosionNN.anim.frames.PushBack({ 112, 40, 16, 16 });
	explosionNN.anim.frames.PushBack({ 192, 40, 16, 16 });
	explosionNN.anim.frames.PushBack({ 272, 40, 16, 16 });
	explosionNN.anim.frames.PushBack({ 352, 40, 16, 16 });
	explosionNN.anim.frames.PushBack({ 272, 40, 16, 16 });
	explosionNN.anim.frames.PushBack({ 192, 40, 16, 16 });
	explosionNN.anim.frames.PushBack({ 112, 40, 16, 16 });
	explosionNN.anim.frames.PushBack({ 32, 40, 16, 16 });

	explosionNN.life = 800;
	explosionNN.anim.loop = false;
	explosionNN.anim.speed = 0.2f;

	explosionE.anim.frames.PushBack({ 48, 72, 16, 16 });
	explosionE.anim.frames.PushBack({ 128, 72, 16, 16 });
	explosionE.anim.frames.PushBack({ 208, 72, 16, 16 });
	explosionE.anim.frames.PushBack({ 288, 72, 16, 16 });
	explosionE.anim.frames.PushBack({ 368, 72, 16, 16 });
	explosionE.anim.frames.PushBack({ 288, 72, 16, 16 });
	explosionE.anim.frames.PushBack({ 208, 72, 16, 16 });
	explosionE.anim.frames.PushBack({ 128, 72, 16, 16 });
	explosionE.anim.frames.PushBack({ 48, 72, 16, 16 });

	explosionE.life = 800;
	explosionE.anim.loop = false;
	explosionE.anim.speed = 0.2f;

	explosionEE.anim.frames.PushBack({ 64, 72, 16, 16 });
	explosionEE.anim.frames.PushBack({ 144, 72, 16, 16 });
	explosionEE.anim.frames.PushBack({ 224, 72, 16, 16 });
	explosionEE.anim.frames.PushBack({ 304, 72, 16, 16 });
	explosionEE.anim.frames.PushBack({ 384, 72, 16, 16 });
	explosionEE.anim.frames.PushBack({ 304, 72, 16, 16 });
	explosionEE.anim.frames.PushBack({ 224, 72, 16, 16 });
	explosionEE.anim.frames.PushBack({ 144, 72, 16, 16 });
	explosionEE.anim.frames.PushBack({ 64, 72, 16, 16 });

	explosionEE.life = 800;
	explosionEE.anim.loop = false;
	explosionEE.anim.speed = 0.2f;

	explosionO.anim.frames.PushBack({ 16, 72, 16, 16 });
	explosionO.anim.frames.PushBack({ 96, 72, 16, 16 });
	explosionO.anim.frames.PushBack({ 176, 72, 16, 16 });
	explosionO.anim.frames.PushBack({ 256, 72, 16, 16 });
	explosionO.anim.frames.PushBack({ 336, 72, 16, 16 });
	explosionO.anim.frames.PushBack({ 256, 72, 16, 16 });
	explosionO.anim.frames.PushBack({ 176, 72, 16, 16 });
	explosionO.anim.frames.PushBack({ 96, 72, 16, 16 });
	explosionO.anim.frames.PushBack({ 16, 72, 16, 16 });

	explosionO.life = 800;
	explosionO.anim.loop = false;
	explosionO.anim.speed = 0.2f;

	explosionOO.anim.frames.PushBack({ 0, 72, 16, 16 });
	explosionOO.anim.frames.PushBack({ 80, 72, 16, 16 });
	explosionOO.anim.frames.PushBack({ 160, 72, 16, 16 });
	explosionOO.anim.frames.PushBack({ 240, 72, 16, 16 });
	explosionOO.anim.frames.PushBack({ 320, 72, 16, 16 });
	explosionOO.anim.frames.PushBack({ 240, 72, 16, 16 });
	explosionOO.anim.frames.PushBack({ 160, 72, 16, 16 });
	explosionOO.anim.frames.PushBack({ 80, 72, 16, 16 });
	explosionOO.anim.frames.PushBack({ 0, 72, 16, 16 });

	explosionOO.life = 800;
	explosionOO.anim.loop = false;
	explosionOO.anim.speed = 0.2f;
	
	// Destruccion de FakeWall
	destruction.anim.frames.PushBack({ 48, 40, 16, 16 });
	destruction.anim.frames.PushBack({ 48, 40, 16, 16 });
	destruction.anim.frames.PushBack({ 64, 40, 16, 16 });
	destruction.anim.frames.PushBack({ 64, 40, 16, 16 });
	destruction.anim.frames.PushBack({ 80, 40, 16, 16 });
	destruction.anim.frames.PushBack({ 48, 56, 16, 16 });
	destruction.anim.frames.PushBack({ 64, 56, 16, 16 });
	destruction.anim.frames.PushBack({ 80, 56, 16, 16 });
	
	destruction.anim.loop = false;
	destruction.anim.speed = 0.2f;
	destruction.life = 650;

	next_up = true;
	next_down = true;
	next_left = true;
	next_right = true;

	enemy_dead = false;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	p2List_item<Particle*>* tmp = active.getFirst();
	p2List_item<Particle*>* tmp_next = active.getFirst();

	while(tmp != NULL)
	{
		Particle* p = tmp->data;
		tmp_next = tmp->next;

		if(p->Update() == false)
		{
			delete p;
			active.del(tmp);
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Always destroy particles that collide
void ModuleParticles::Explosion()
{
	next_up = true;
	next_down = true;
    next_left = true;
	next_right = true;

	//PETAR FALSEWALL
	for (int i = 1; i <= bomb_range; i++)
	{
		if ((App->player->last_bomb_pos.y == App->player->array_pos.y && App->player->last_bomb_pos.x == App->player->array_pos.x) && next_right)
		{
			App->player->player_losses = true;
		}

		if ((App->player->last_bomb_pos.y + i == App->player->array_pos.y && App->player->last_bomb_pos.x == App->player->array_pos.x) && next_right)
		{
			App->player->player_losses = true;
		}

		if ((App->player->last_bomb_pos.y - i == App->player->array_pos.y && App->player->last_bomb_pos.x == App->player->array_pos.x) && next_left)
		{
			App->player->player_losses = true;
		}

		if ((App->player->last_bomb_pos.y == App->player->array_pos.y && App->player->last_bomb_pos.x + i == App->player->array_pos.x) && next_up)
		{
			App->player->player_losses = true;
		}

		if ((App->player->last_bomb_pos.y == App->player->array_pos.y && App->player->last_bomb_pos.x - i == App->player->array_pos.x) && next_down)
		{
			App->player->player_losses = true;
		}

		// Middle explosion
		App->particles->AddParticle(explosion, (App->player->last_bomb_pos.x) * TILE + 24, (App->player->last_bomb_pos.y) * TILE + 40, 0);

		if (App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] == 2 && next_right)
		{
			App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] = 0;

			// Probabilidad de que aparezca PowerUP Speed
			if ((App->level_one->clock % 10) == 7 && App->player->powerup_speed != true ) { App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] = 5; }

			// Probabilidad de que aparezca PowerUP Range
			if ((App->level_one->clock % 10) == 0) { App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] = 6; }

			App->particles->AddParticle(destruction, (App->player->last_bomb_pos.x) * TILE + 24, (App->player->last_bomb_pos.y + i) * TILE + 40, 0);
			next_right = false;
		}

		if (App->level_one->l1_map_array[App->player->last_bomb_pos.y - i][App->player->last_bomb_pos.x] == 2 && next_left)
		{
			App->level_one->l1_map_array[App->player->last_bomb_pos.y - i][App->player->last_bomb_pos.x] = 0;

			// Probabilidad de que aparezca PowerUP Range
			if ((App->level_one->clock % 10) == 2) { App->level_one->l1_map_array[App->player->last_bomb_pos.y - i][App->player->last_bomb_pos.x] = 6; }

			App->particles->AddParticle(destruction, (App->player->last_bomb_pos.x) * TILE + 24, (App->player->last_bomb_pos.y - i) * TILE + 40, 0);
			next_left = false;
		}

		if (App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] == 2 && next_up)
		{
			App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] = 0;

			// Probabilidad de que aparezca PowerUP Speed
			if ((App->level_one->clock % 10) == 9 && App->player->powerup_speed != true) { App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] = 5; }

			// Probabilidad de que aparezca PowerUP Range
			if ((App->level_one->clock % 10) == 5) { App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] = 6; }

			App->particles->AddParticle(destruction, (App->player->last_bomb_pos.x + i) * TILE + 24, (App->player->last_bomb_pos.y) * TILE + 40, 0);
			next_up = false;
		}

		if (App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x - i] == 2 && next_down)
		{
			App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x - i] = 0;

			// Probabilidad de que aparezca PowerUP Range
			if ((App->level_one->clock % 10) == 3) { App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x - i] = 6; }

			App->particles->AddParticle(destruction, (App->player->last_bomb_pos.x - i) * TILE + 24, (App->player->last_bomb_pos.y) * TILE + 40, 0);
			next_down = false;
		}


		if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] == 1 || App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] == 11) && next_right)
		{
			next_right = false;
		}
		
		if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y - i][App->player->last_bomb_pos.x] == 1 || App->level_one->l1_map_array[App->player->last_bomb_pos.y - i][App->player->last_bomb_pos.x] == 11) && next_left)
		{
			next_left = false;
		}

		if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] == 1 || App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] == 11) && next_up)
		{
			next_up = false;
		}

		if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x - i] == 1 || App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x - i] == 11) && next_down)
		{
			next_down = false;
		}

		if (i != bomb_range)
		{
			if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] == 0 || App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] == 10) && next_right)
				App->particles->AddParticle(explosionS, (App->player->last_bomb_pos.x) * TILE + 24, (App->player->last_bomb_pos.y + i) * TILE + 40, 0);

			if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y - i][App->player->last_bomb_pos.x] == 0 || App->level_one->l1_map_array[App->player->last_bomb_pos.y - i][App->player->last_bomb_pos.x] == 10) && next_left)
				App->particles->AddParticle(explosionN, (App->player->last_bomb_pos.x) * TILE + 24, (App->player->last_bomb_pos.y - i) * TILE + 40, 0);

			if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] == 0 || App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] == 10) && next_up)
				App->particles->AddParticle(explosionE, (App->player->last_bomb_pos.x + i) * TILE + 24, (App->player->last_bomb_pos.y) * TILE + 40, 0);

			if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x - i] == 0 || App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x - i] == 10) && next_down)
				App->particles->AddParticle(explosionO, (App->player->last_bomb_pos.x - i) * TILE + 24, (App->player->last_bomb_pos.y) * TILE + 40, 0);
		}

		if (i == bomb_range)
		{
			if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] == 0 || App->level_one->l1_map_array[App->player->last_bomb_pos.y + i][App->player->last_bomb_pos.x] == 10) && next_right)
				App->particles->AddParticle(explosionSS, (App->player->last_bomb_pos.x) * TILE + 24, (App->player->last_bomb_pos.y + i) * TILE + 40, 0);

			if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y - i][App->player->last_bomb_pos.x] == 0 || App->level_one->l1_map_array[App->player->last_bomb_pos.y - i][App->player->last_bomb_pos.x] == 10) && next_left)
				App->particles->AddParticle(explosionNN, (App->player->last_bomb_pos.x) * TILE + 24, (App->player->last_bomb_pos.y - i) * TILE + 40, 0);

			if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] == 0 || App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x + i] == 10) && next_up)
				App->particles->AddParticle(explosionEE, (App->player->last_bomb_pos.x + i) * TILE + 24, (App->player->last_bomb_pos.y) * TILE + 40, 0);

			if ((App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x - i] == 0 || App->level_one->l1_map_array[App->player->last_bomb_pos.y][App->player->last_bomb_pos.x - i] == 10) && next_down)
				App->particles->AddParticle(explosionOO, (App->player->last_bomb_pos.x - i) * TILE + 24, (App->player->last_bomb_pos.y) * TILE + 40, 0);
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (App->player->last_bomb_pos.x + i == App->enemy->array_pos.x && App->player->last_bomb_pos.y == App->enemy->array_pos.y)
		{
			App->enemy->speed.x = App->enemy->speed.y = 0;
			enemy_dead = true;
		}

		if (App->player->last_bomb_pos.x - i == App->enemy->array_pos.x && App->player->last_bomb_pos.y == App->enemy->array_pos.y)
		{
			App->enemy->speed.x = App->enemy->speed.y = 0;
			enemy_dead = true;
		}
		
		if (App->player->last_bomb_pos.x == App->enemy->array_pos.x && App->player->last_bomb_pos.y + i == App->enemy->array_pos.y)
		{
			App->enemy->speed.x = App->enemy->speed.y = 0;
			enemy_dead = true;
		}

		if (App->player->last_bomb_pos.x == App->enemy->array_pos.x && App->player->last_bomb_pos.y - i == App->enemy->array_pos.y)
		{
			App->enemy->speed.x = App->enemy->speed.y = 0;
			enemy_dead = true;
		}
	}
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active.add(p);

	return p;

}



// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Particle::~Particle()
{
	if(collider)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	if(collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = {position.x, position.y, r.w, r.h};
	}

	return ret;
}