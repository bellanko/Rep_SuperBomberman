#include "Globals.h"
#include "Application.h"
#include "ModuleBoss.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBoss::ModuleBoss(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;

	// Move Boss
	move.frames.PushBack({ 0, 232, 77, 77 });

	move.loop = false;
	move.speed = 0.01f;

	// Boss Attacks
	attack.frames.PushBack({ 77, 208, 77, 101});
	attack.frames.PushBack({ 77, 208, 77, 101 });
	attack.frames.PushBack({ 154, 208, 77, 101 });
	attack.frames.PushBack({ 154, 208, 77, 101 });
	attack.frames.PushBack({ 231, 208, 77, 153 });
	attack.frames.PushBack({ 231, 208, 77, 153 });
	attack.frames.PushBack({ 231, 208, 77, 153 });
	attack.frames.PushBack({ 231, 208, 77, 153 });

	attack.loop = true;
	attack.speed = 0.05f;

	// Boss Dies
	dead.frames.PushBack({ 308, 232, 77, 101 });
	dead.frames.PushBack({ 308, 232, 77, 101 });

	dead.loop = true;
	dead.speed = 0.1f;



}

ModuleBoss::~ModuleBoss()
{}

// Load assets
bool ModuleBoss::Start()
{
	LOG("Loading boss");

	graphics = App->textures->Load("Resources/Elements.png");

	current_animation = &move;

	boss_dies = false;
	boss_attacks = false;
	speed.x = speed.y = 0;

	boss_position.x = 130;
	boss_position.y = 60;

	return true;
}

// Unload assets
bool ModuleBoss::CleanUp()
{
	LOG("Unloading boss");

	App->textures->Unload(graphics);

	return true;
}



// Update: draw background
update_status ModuleBoss::Update()
{

	// CALCULATES THE ENEMY POSITION ON THE MAP ARRAY  --------------------------------------
	array_pos.x = (boss_position.x - 24) / TILE;
	array_pos.y = (boss_position.y - 40) / TILE;


	LOG("array_x: %d arra_y: %d", array_pos.x, array_pos.y);
	LOG("x: %d y: %d", boss_position.x, boss_position.y);

	if (!boss_dies && boss_attacks == false)
	{
		current_animation = &move;
		if (App->level_boss->clock % 3 == 0)
		{
			if ((App->player->position.x +8) <= boss_position.x)
				speed.x = -1;

			if ((App->player->position.x + 8) >= boss_position.x)
				speed.x = 1;

			if (App->player->position.y >= boss_position.y)
				speed.y = 1;
			
			if (App->player->position.y <= boss_position.y)
				speed.y = -1;
		}

		else
		{
			speed.x = 0;
			speed.y = 0;
		}
	}


	// BOSS ATTACKS
	if (!boss_dies)
	{
		if (App->level_boss->clock % 800 == 0 || boss_attacks)
		{
			boss_attacks = true;
			speed.x = 0;
			speed.y = 0;
		}

		if (current_animation == &attack && current_animation->Finished())
		{
			current_animation->Reset();
			boss_attacks = false;
		}
	}

	if (boss_attacks && !boss_dies)
	{
		current_animation = &attack;
		if ((boss_position.x - App->player->position.x) > -40 && (boss_position.x - App->player->position.x < 40))
		{
			if ((boss_position.y - App->player->position.y) > -75 && (boss_position.y - App->player->position.y < 150))
				App->player->player_losses = true;
		}
	}

	if (App->level_boss->clock % 1200 == 0)
		boss_dies = true;

	// DEATH ANIMATION
	if (boss_dies)
	{
		current_animation = &dead;
		speed.x = 0;
		speed.y = 0;
	}

	// SCORE
	if (score_received == false && boss_dies)
	{
		App->player->score += 2000;
		score_received = true;
	}

	if (App->level_boss->clock == 1650 && boss_dies)
	{
		App->player->player_wins = true;
		App->level_boss->win = true;
	}

	// DRAW BOSS --------------------------------------

	boss_position.x += speed.x;
	boss_position.y += speed.y;
	
	App->renderer->Blit(graphics, boss_position.x -40, boss_position.y -8, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}