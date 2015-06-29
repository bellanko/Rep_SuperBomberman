#include "Globals.h"
#include "Application.h"
#include "ModuleLevelBoss.h"

ModuleLevelBoss::ModuleLevelBoss(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	interficie = NULL;

	//Raw Layout
	layout_raw.frames.PushBack({ 0, 335, 256, 201 });
	layout_raw.loop = false;

	// Layout (Parte Superior del Mapa)
	layout.frames.PushBack({ 0, 0, 256, 32 });
	layout.loop = false;
	layout.speed = 0.1f;

	// Mid (Parte Central del Mapa)
	mid.frames.PushBack({ 0, 44, 256, 201 });
	mid.loop = false;
	mid.speed = 0.1f;

	// Title
	title.frames.PushBack({ 0, 245, 127, 90 });
	title.loop = false;
	title.speed = 0.1f;

	// Timer
	timer.frames.PushBack({ 0, 35, 9, 9 });
	timer.frames.PushBack({ 9, 35, 9, 9 });
	timer.frames.PushBack({ 18, 35, 9, 9 });
	timer.frames.PushBack({ 27, 35, 9, 9 });
	timer.frames.PushBack({ 36, 35, 9, 9 });
	timer.frames.PushBack({ 45, 35, 9, 9 });
	timer.frames.PushBack({ 54, 35, 9, 9 });
	timer.frames.PushBack({ 63, 35, 9, 9 });
	timer.loop = true;
	timer.speed = 0.015f;

	// Timer Square
	timer_square.frames.PushBack({ 108, 32, 4, 3 });
	timer_square.loop = true;
	timer_square.speed = 0.1f;

	// NUMBERS
	zero.frames.PushBack({ 184, 248, 8, 10 });
	zero.loop = false;
	zero.speed = 0.1f;

	one.frames.PushBack({ 192, 248, 8, 10 });
	one.loop = false;
	one.speed = 0.1f;

	two.frames.PushBack({ 200, 248, 8, 10 });
	two.loop = false;
	two.speed = 0.1f;

	three.frames.PushBack({ 208, 248, 8, 10 });
	three.loop = false;
	three.speed = 0.1f;

	four.frames.PushBack({ 216, 248, 8, 10 });
	four.loop = false;
	four.speed = 0.1f;

	five.frames.PushBack({ 224, 248, 8, 10 });
	five.loop = false;
	five.speed = 0.1f;

	six.frames.PushBack({ 176, 248, 8, 10 });
	six.loop = false;
	six.speed = 0.1f;

	seven.frames.PushBack({ 232, 248, 8, 10 });
	seven.loop = false;
	seven.speed = 0.1f;

	eight.frames.PushBack({ 240, 248, 8, 10 });
	eight.loop = false;
	eight.speed = 0.1f;

	nine.frames.PushBack({ 2, 248, 8, 10 });
	nine.loop = false;
	nine.speed = 0.1f;

}

unsigned int ModuleLevelBoss::Longitud(unsigned int n)
{
	int count = 1;
	while (n > 9) {
		n /= 10;
		++count;
	}
	return count;
}

void ModuleLevelBoss::PrintScore()
{
	int aux = incremental_score;
	int k;

	for (unsigned int n = 0; n < Longitud(incremental_score); n++)
	{
		k = aux % 10;
		if (k == 0) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_zero->GetCurrentFrame()));
		else if (k == 1) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_one->GetCurrentFrame()));
		else if (k == 2) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_two->GetCurrentFrame()));
		else if (k == 3) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_three->GetCurrentFrame()));
		else if (k == 4) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_four->GetCurrentFrame()));
		else if (k == 5) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_five->GetCurrentFrame()));
		else if (k == 6) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_six->GetCurrentFrame()));
		else if (k == 7) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_seven->GetCurrentFrame()));
		else if (k == 8) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_eight->GetCurrentFrame()));
		else if (k == 9) App->renderer->Blit(interficie, (104 - (n * 8)), 11, &(x_nine->GetCurrentFrame()));
		aux /= 10;
	}

	if (App->player->life == 1) App->renderer->Blit(interficie, 24, 11, &(x_one->GetCurrentFrame()));
	else if (App->player->life == 0) App->renderer->Blit(interficie, 24, 11, &(x_zero->GetCurrentFrame()));
	else if (App->player->life == 2) App->renderer->Blit(interficie, 24, 11, &(x_two->GetCurrentFrame()));
	else if (App->player->life == 3) App->renderer->Blit(interficie, 24, 11, &(x_three->GetCurrentFrame()));
	else if (App->player->life == 4) App->renderer->Blit(interficie, 24, 11, &(x_four->GetCurrentFrame()));
	else if (App->player->life == 5) App->renderer->Blit(interficie, 24, 11, &(x_five->GetCurrentFrame()));
}

ModuleLevelBoss::~ModuleLevelBoss()
{}

// Load assets
bool ModuleLevelBoss::Start()
{
	//Fill array as needed
	//FLOOR: 10;
	//BLOCK: 11;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i % 2 != 0 && j % 2 != 0)
				App->level_one->l1_map_array[i][j] = 11;
			else
				App->level_one->l1_map_array[i][j] = 10;
		}
	}

	LOG("Loading Level Boss");
	interficie = App->textures->Load("Resources/Level_Layout_2.png");

	// Initial Positions for Moving Objects
	pos_mid = 600;
	pos_title = -128;

	x_raw_layout = &layout_raw;
	x_title = &title;
	x_layout = &layout;
	x_mid = &mid;
	x_timer = &timer;
	x_timer_square = &timer_square;

	x_zero = &zero;
	x_one = &one;
	x_two = &two;
	x_three = &three;
	x_four = &four;
	x_five = &five;
	x_six = &six;
	x_seven = &seven;
	x_eight = &eight;
	x_nine = &nine;

	// Starting Attributes for Player
	App->player->current_animation = &App->player->win;
	App->player->current_animation->Reset();

	App->player->current_animation = &App->player->dead;
	App->player->current_animation->Reset();

	App->player->current_animation = &App->player->idle_up;
	
	// Score
	incremental_score = App->player->score;

	scene_transition = false;
	win = false;
	lose = false;

	// Timer < ! >
	clock = 0;

	//Starting Position for Player
	App->player->position.x = 88;
	App->player->position.y = 200;

	fx = App->audio->LoadFx("Resources/07_win.ogg");

	App->audio->PlayMusic("Resources/05_level_Boss.ogg");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return true;
}


// UnLoad assets
bool ModuleLevelBoss::CleanUp()
{
	LOG("Unloading space scene");

	App->boss->Disable();
	App->player->Disable();
	App->particles->Disable();
	App->map->Disable();
	App->textures->Unload(interficie);

	return true;
}

// Update: draw background
update_status ModuleLevelBoss::Update()
{
	// Draw everything --------------------------------------
	if (clock >= 40 && clock <= 180)
	{
		App->renderer->Blit(interficie, 0, pos_mid, &(x_mid->GetCurrentFrame()));
		if (pos_mid > 23)
		{
			pos_mid -= 5; // Smooth
		}
		if (pos_mid < 23)
		{
			pos_mid = 23;
		}
		else if (pos_mid > 23)
		{
			pos_mid -= 4;
		}
		if (pos_title <= 64)
		{
			pos_title += 6;
		}
	}

	if (clock >= 150)
	{
		pos_title += 8;
	}

	if (clock >= 180)
	{
		App->renderer->Blit(interficie, 0, 23, &(x_raw_layout->GetCurrentFrame()));
		App->map->Enable();
		App->particles->Enable();
		App->player->Enable();
		App->boss->Enable();
	}

	App->renderer->Blit(interficie, 0, 0, &(x_layout->GetCurrentFrame()));

	// Timer
	if (clock >= 180 && clock < 6900)
	{
		App->renderer->Blit(interficie, 124, 14, &(x_timer->GetCurrentFrame()));
		for (int k = 13 - (1 * ((clock - 179) / 535)); k >= 0; k--)
		{
			App->renderer->Blit(interficie, 114 - (k * 8), 26, &(x_timer_square->GetCurrentFrame()));
		}
	}

	// Score
	PrintScore();

	if (App->player->score > incremental_score)
	{
		incremental_score += 5;
	}

	// Player dies if time runs out
	if (clock == 6900)
	{
		App->player->player_losses = true;
		App->player->life -= 1;
	}

	// Defeat
	if (App->player->life == 0)
		lose = true;

	App->renderer->Blit(interficie, pos_title, 90, &(x_title->GetCurrentFrame()));

	clock++;

	//Check Game Over
	if (win && !scene_transition)
	{
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(this, App->scene_intro, 3.0f);
		scene_transition = true;
	}

	if (lose && !scene_transition)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 3.0f);
		scene_transition = true;
	}

	return UPDATE_CONTINUE;
}