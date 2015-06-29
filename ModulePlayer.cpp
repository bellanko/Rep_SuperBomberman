#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// SUPER BOMBERMAN SNES PROJECT

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;

	bombs = 0;
	player_losses = false;
	player_wins = false;

	// idle animations (just the player)
	idle_down.frames.PushBack({ 16, 0, 16, 24 });
	idle_up.frames.PushBack({ 160, 0, 16, 24 });
	idle_left.frames.PushBack({ 64, 0, 16, 24 });
	idle_right.frames.PushBack({ 112, 0, 16, 24 });

	// move upwards
	up.frames.PushBack({ 144, 0, 16, 24 });
	up.frames.PushBack({ 160, 0, 16, 24 });
	up.frames.PushBack({ 176, 0, 16, 24 });
	up.frames.PushBack({ 160, 0, 16, 24 });
	up.loop = true;
	up.speed = 0.1f;


	// Move down
	down.frames.PushBack({ 0, 0, 16, 24 });
	down.frames.PushBack({ 16, 0, 16, 24 });
	down.frames.PushBack({ 32, 0, 16, 24 });
	down.frames.PushBack({ 16, 0, 16, 24 });
	down.loop = true;
	down.speed = 0.1f;

	// Move Right
	right.frames.PushBack({ 96, 0, 16, 24 });
	right.frames.PushBack({ 112, 0, 16, 24 });
	right.frames.PushBack({ 128, 0, 16, 24 });
	right.frames.PushBack({ 112, 0, 16, 24 });
	right.loop = true;
	right.speed = 0.1f;


	// Move Left
	left.frames.PushBack({ 48, 0, 16, 24 });
	left.frames.PushBack({ 64, 0, 16, 24 });
	left.frames.PushBack({ 80, 0, 16, 24 });
	left.frames.PushBack({ 64, 0, 16, 24 });
	left.loop = true;
	left.speed = 0.1f;


	// Dead
	dead.frames.PushBack({ 256, 0, 16, 24 });
	dead.frames.PushBack({ 272, 0, 16, 24 });
	dead.frames.PushBack({ 288, 0, 16, 24 });
	dead.frames.PushBack({ 304, 0, 16, 24 });
	dead.frames.PushBack({ 304, 0, 16, 24 });
	dead.frames.PushBack({ 304, 0, 16, 24 });
	dead.loop = false;
	dead.speed = 0.1f;

	// Win
	win.frames.PushBack({ 259, 137, 16, 24 });
	win.frames.PushBack({ 275, 137, 16, 24 });
	win.frames.PushBack({ 291, 137, 16, 24 });
	win.frames.PushBack({ 307, 137, 16, 24 });
	win.frames.PushBack({ 323, 137, 16, 24 });
	win.frames.PushBack({ 339, 137, 16, 24 });
	win.frames.PushBack({ 355, 137, 16, 24 });
	win.frames.PushBack({ 373, 137, 16, 24 });
	win.frames.PushBack({ 389, 137, 16, 24 });
	win.frames.PushBack({ 405, 137, 16, 24 });

	win.loop = false;
	win.speed = 0.3f;

	//invulnerable
	invulnerable.frames.PushBack({ 0, 160, 16, 24 });
	invulnerable.frames.PushBack({ 16, 160, 16, 24 });
	invulnerable.frames.PushBack({ 32, 160, 16, 24 });
	invulnerable.frames.PushBack({ 48, 160, 16, 24 });
	invulnerable.frames.PushBack({ 64, 160, 16, 24 });
	invulnerable.frames.PushBack({ 80, 160, 16, 24 });
	invulnerable.frames.PushBack({ 96, 160, 16, 24 });
	invulnerable.frames.PushBack({ 112, 160, 16, 24 });
	invulnerable.frames.PushBack({ 128, 160, 16, 24 });
	invulnerable.frames.PushBack({ 144, 160, 16, 24 });
	invulnerable.frames.PushBack({ 160, 160, 16, 24 });
	invulnerable.frames.PushBack({ 176, 160, 16, 24 });
	invulnerable.loop = true;
	invulnerable.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Resources/Elements.png");
	walk_fx = App->audio->LoadFx("Resources/walk1.wav");
	bomb_fx = App->audio->LoadFx("Resources/bomb.wav");
	powerup_fx = App->audio->LoadFx("Resources/powerup.wav");
	explosion_fx = App->audio->LoadFx("Resources/exploting_bomb.wav");

	walk_timer = 0;
	timerw = 0;
	timerb = 0;
	bombdown = false;
	App->particles->bombed = false;
	explosion_timer = false;
	explosion_sec = 0;


	player_wins = false;
	player_losses = false;

	up.speed = down.speed = right.speed = left.speed = 0.1f;

	speed.x = speed.y = 0;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

bool ModulePlayer::OnCollision(moving direction)
{
	switch (direction)
	{
	case upD:
		if (position.y - 40 == 0) //Checks map limits.(External walls)
			return true;

		else if ((position.x - 24) % 16 == 0 && (App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 10 || App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 0 || App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 5 || App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 6 || App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 7))
			return false;

		else if ((position.x - 24) % 16 == 0 && App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] != 0 && ((position.y - 8) % 16 != 0))
			return false;

		return true;
		break;

	case downD:
		if (position.y - 40 == 160) //Checks map limits.(External walls)
			return true;

		else if ((position.x - 24) % 16 == 0 && (App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 10 || App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 0 || App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 5 || App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 6 || App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 7))
			return false;

		else if ((position.x - 24) % 16 == 0 && App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] != 0 && ((position.y - 8) % 16 != 0))
			return false;

		return true;
		break;

	case rightD:
		if (position.x - 24 == 192) //Checks map limits.(External walls)
			return true;

		else if ((position.y - 8) % 16 == 0 && (App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 10 || App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 0 || App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 5 || App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 6 || App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 7))
			return false;

		else if ((position.y - 8) % 16 == 0 && App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] != 0 && ((position.x - 24) % 16 != 0))
			return false;

		return true;
		break;

	case leftD:
		if (position.x - 24 == 0) //Checks map limits.(External walls)
			return true;

		else if ((position.y - 8) % 16 == 0 && (App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 10 || App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 0 || App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 5 || App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 6 || App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 7))
			return false;

		else if ((position.y - 8) % 16 == 0 && App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] != 0 && ((position.x - 24) % 16 != 0))
			return false;

		return true;
		break;

	case upRightD:

		if (App->level_one->l1_map_array[array_pos.y - 1][array_pos.x + 1] == 0)
			return false;

		return true;
		break;

	case upLeftD:

		if (App->level_one->l1_map_array[array_pos.y - 1][array_pos.x - 1] == 0)
			return false;

		return true;
		break;

	case downRightD:

		if (App->level_one->l1_map_array[array_pos.y + 1][array_pos.x + 1] == 0)
			return false;

		return true;
		break;

	case downLeftD:

		if (App->level_one->l1_map_array[array_pos.y + 1][array_pos.x - 1] == 0)
			return false;

		return true;
		break;
	}
	return false;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	speed.x = speed.y = 0;

	//CALCULATES THE PLAYER POSITION ON THE MAP ARRAY  --------------------------------------
	array_pos.x = (position.x - 24) / TILE;
	array_pos.y = (position.y - 40) / TILE;

	LOG("array_x: %d arra_y: %d", array_pos.x, array_pos.y);
	LOG("x: %d y: %d", position.x, position.y);

	//POWERUPS ----------------------------------------------------------------------------------
	//Speed
	if (player_losses != true || life == 0)
	{
		if (App->level_one->l1_map_array[array_pos.y][array_pos.x] == 5)
		{
			powerup_speed = true;
			App->level_one->l1_map_array[array_pos.y][array_pos.x] = 0;
			score += 400;
			App->audio->PlayFx(powerup_fx);
		}

		//Bomb range
		if (App->level_one->l1_map_array[array_pos.y][array_pos.x] == 6)
		{
			powerup_range = true;
			App->particles->bomb_range += 1;
			App->level_one->l1_map_array[array_pos.y][array_pos.x] = 0;
			score += 200;
			App->audio->PlayFx(powerup_fx);
		}

		//Changes player speed animations based on poweup active or not
		if (powerup_speed)
			up.speed = down.speed = right.speed = left.speed = 0.2f;
	}

	//SETS PLAYER SPEED BASED ON KEY PRESS  --------------------------------------
	
	if (App->level_one->l1_map_array[array_pos.y][array_pos.x] != 7 && player_losses != true)
	{
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			if (!powerup_speed)
				speed.y = 1;
			else
				speed.y = 2;
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			if (!powerup_speed)
				speed.y = -1;
			else
				speed.y = -2;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (!powerup_speed)
				speed.x = 1;
			else
				speed.x = 2;
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			if (!powerup_speed)
				speed.x = -1;
			else
				speed.x = -2;
		}
	}

	LOG("speed.x: %d speed.y: %d", speed.x, speed.y);

	//FILTERS PLAYER SPEED BASED ON COLLISIONS IN MAP  --------------------------------------
	if (OnCollision(upD) && speed.y <= -1)
	{
		speed.y = 0;
		current_animation = &idle_up;
	}

	if (OnCollision(downD) && speed.y >= 1)
	{
		speed.y = 0;
		current_animation = &idle_down;
	}

	if (OnCollision(rightD) && speed.x >= 1)
	{
		speed.x = 0;
		current_animation = &idle_right;
	}

	if (OnCollision(leftD) && speed.x <= -1)
	{
		speed.x = 0;
		current_animation = &idle_left;
	}


	if (OnCollision(upRightD) && speed.x >= 1 && speed.y <= -1)
		speed.y = 0;

	if (OnCollision(upLeftD) && speed.x <= -1 && speed.y <= -1)
		speed.y = 0;

	if (OnCollision(downRightD) && speed.x >= 1 && speed.y >= 1)
		speed.x = 0;

	if (OnCollision(downLeftD) && speed.x <= -1 && speed.y >= 1)
		speed.x = 0;

	LOG("f_speed.x: %d f_speed.y: %d", speed.x, speed.y);

	position += speed;

	//UPDATES THE PLAYER ANIMATION BASED ON PLAYERS SPEED  --------------------------------------
	if (speed.x != 0 || speed.y != 0)
	{
		if (speed.x >= 1)
			current_animation = &right;

		else if (speed.x <= -1)
			current_animation = &left;

		else if (speed.y >= 1)
			current_animation = &down;

		else if (speed.y <= -1)
			current_animation = &up;
	}

	else
	{
		if (current_animation == &down)
			current_animation = &idle_down;

		else if (current_animation == &left)
			current_animation = &idle_left;

		else if (current_animation == &right)
			current_animation = &idle_right;

		else if (current_animation == &up)
			current_animation = &idle_up;
	}

	// REGULATES WALKING SOUNDS   --------------------------------------
	if ((speed.x != 0 || speed.y != 0) && walk_timer < 1)
	{
		walk_timer++;
		timerw = 0;
		App->audio->PlayFx(walk_fx);
	}

	if (timerw > 20) walk_timer = 0;

	timerw++;

	//BOMBS  --------------------------------------
	if (!player_losses)
	{
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && !bombdown)
		{
			last_bomb_pos.x = ((position.x - 24 + 8) / 16);
			last_bomb_pos.y = ((position.y - 32) / 16);

			App->level_one->l1_map_array[last_bomb_pos.y][last_bomb_pos.x] = 3;

			App->particles->AddParticle(App->particles->bomb, (last_bomb_pos.x * TILE) + 24, (last_bomb_pos.y * TILE) + 40, 0);
			App->audio->PlayFx(bomb_fx);

			bombdown = true;
		}

		if (bombdown)
			timerb++;

		if (timerb > 200)
		{
			timerb = 0;
			bombdown = false;
			App->audio->PlayFx(explosion_fx);
			App->level_one->l1_map_array[last_bomb_pos.y][last_bomb_pos.x] = 0;
			App->particles->Explosion();
			explosion_timer = true;
		}
	}

	if (array_pos.x == App->enemy->array_pos.x && array_pos.y == App->enemy->array_pos.y && (position.x - 24) % 16 == 0 && !(App->particles->enemy_dead))
	{
		player_losses = true;
		speed.x = speed.y = 0;
	}

	else if (((position.x - 24) % 16) > 0 && array_pos.x + 1 == App->enemy->array_pos.x && array_pos.y == App->enemy->array_pos.y && !(App->particles->enemy_dead))
	{
		player_losses = true;
		speed.x = speed.y = 0;

	}

	// DEATH
	if (player_losses)
	{
		speed.x = speed.y = 0;
		current_animation = &dead;
	}


	// WIN
	else if (App->level_one->l1_map_array[array_pos.y][array_pos.x] == 7)
	{
		player_wins = true;
		current_animation = &win;
	}

	if (player_wins && current_animation->Finished())
	{
		App->level_one->win = true;
	}

	if (player_losses && current_animation->Finished())
	{

		life -= 1;
		player_losses = false;
		current_animation = &idle_down;
		App->level_one->clock = 181;
		App->level_boss->clock = 181;
		if (life > 0)
		{
			position.x = 24;
			position.y = 40;
		}
	}


	// DRAW PLAYER --------------------------------------
	App->renderer->Blit(graphics, position.x, position.y - 8, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

