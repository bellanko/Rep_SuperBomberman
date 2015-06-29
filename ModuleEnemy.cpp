#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleEnemy::ModuleEnemy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;

	// Move Up
	up.frames.PushBack({ 64, 184, 16, 24 });
	up.frames.PushBack({ 80, 184, 16, 24 });
	up.frames.PushBack({ 96, 184, 16, 24 });
	up.frames.PushBack({ 112, 184, 16, 24 });
	up.loop = true;
	up.speed = 0.1f;

	// Move Down
	down.frames.PushBack({ 0, 184, 16, 24 });
	down.frames.PushBack({ 16, 184, 16, 24 });
	down.frames.PushBack({ 32, 184, 16, 24 });
	down.frames.PushBack({ 48, 184, 16, 24 });
	down.loop = true;
	down.speed = 0.1f;

	// Move Right
	right.frames.PushBack({ 192, 184, 16, 24 });
	right.frames.PushBack({ 208, 184, 16, 24 });
	right.frames.PushBack({ 224, 184, 16, 24 });
	right.frames.PushBack({ 240, 184, 16, 24 });
	right.loop = true;
	right.speed = 0.1f;

	// Move Left
	left.frames.PushBack({ 128, 184, 16, 24 });
	left.frames.PushBack({ 144, 184, 16, 24 });
	left.frames.PushBack({ 160, 184, 16, 24 });
	left.frames.PushBack({ 176, 184, 16, 24 });
	left.loop = true;
	left.speed = 0.1f;

	// Die Up (then blows)
	dead_up.frames.PushBack({ 112, 184, 16, 24 });
	dead_up.frames.PushBack({ 112, 168, 16, 24 });
	dead_up.frames.PushBack({ 112, 184, 16, 24 });
	dead_up.frames.PushBack({ 112, 168, 16, 24 });
	dead_up.frames.PushBack({ 112, 184, 16, 24 });
	dead_up.loop = true;
	dead_up.speed = 0.05f;

	// Die Down (then blows)
	dead_down.frames.PushBack({ 48, 184, 16, 24 });
	dead_down.frames.PushBack({ 48, 168, 16, 24 });
	dead_down.frames.PushBack({ 48, 184, 16, 24 });
	dead_down.frames.PushBack({ 48, 168, 16, 24 });
	dead_down.frames.PushBack({ 48, 184, 16, 24 });
	dead_down.loop = true;
	dead_down.speed = 0.05f;

	// Die Right (then blows)
	dead_right.frames.PushBack({ 208, 184, 16, 24 });
	dead_right.frames.PushBack({ 208, 168, 16, 24 });
	dead_right.frames.PushBack({ 208, 184, 16, 24 });
	dead_right.frames.PushBack({ 208, 168, 16, 24 });
	dead_right.frames.PushBack({ 208, 184, 16, 24 });
	dead_right.loop = true;
	dead_right.speed = 0.05f;

	// Die Left (then blows)
	dead_left.frames.PushBack({ 176, 184, 16, 24 });
	dead_left.frames.PushBack({ 176, 168, 16, 24 });
	dead_left.frames.PushBack({ 176, 184, 16, 24 });
	dead_left.frames.PushBack({ 176, 168, 16, 24 });
	dead_left.frames.PushBack({ 176, 184, 16, 24 });
	dead_left.loop = false;
	dead_left.speed = 0.05f;

	// Blow (goes after each Die)
	blow.frames.PushBack({ 286, 168, 16, 40 });
	blow.frames.PushBack({ 301, 168, 16, 40 });
	blow.frames.PushBack({ 316, 168, 16, 40 });
	blow.frames.PushBack({ 335, 168, 16, 40 });
	blow.frames.PushBack({ 357, 168, 16, 40 });
	blow.frames.PushBack({ 378, 168, 16, 40 });
	blow.frames.PushBack({ 402, 168, 16, 40 });
	blow.frames.PushBack({ 417, 168, 16, 40 });
	blow.loop = false;
	blow.speed = 0.05f;

}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading enemy");

	graphics = App->textures->Load("Resources/Elements.png");

	current_animation = &down;

	enemy_dies = false;

	countdown = 4;

	position.x = 120;			
	position.y = 56;	

	array_pos.x = 6;
	array_pos.y = 1;

	speed.y = 1;

	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemy");

	App->textures->Unload(graphics);

	return true;
}

bool ModuleEnemy::OnCollision(movement direction)
{
	switch (direction)
	{
	case upDir:
		if (position.y - 40 == 0) //Checks map limits.(External walls)
			return true;

		else if ((position.x - 24) % 16 == 0 && (App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 10 || App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 0 || App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 5 || App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 6 || App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] == 7))
			return false;

		else if ((position.x - 24) % 16 == 0 && App->level_one->l1_map_array[array_pos.y - 1][array_pos.x] != 0 && ((position.y - 8) % 16 != 0))
			return false;

		return true;
		break;

	case downDir:
		if (position.y - 40 == 160) //Checks map limits.(External walls)
			return true;

		else if ((position.x - 24) % 16 == 0 && (App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 10 || App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 0 || App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 5 || App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 6 || App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] == 7))
			return false;

		else if ((position.x - 24) % 16 == 0 && App->level_one->l1_map_array[array_pos.y + 1][array_pos.x] != 0 && ((position.y - 8) % 16 != 0))
			return false;

		return true;
		break;

	case rightDir:
		if (position.x - 24 == 192) //Checks map limits.(External walls)
			return true;

		else if ((position.y - 8) % 16 == 0 && (App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 10 || App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 0 || App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 5 || App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 6 || App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] == 7))
			return false;

		else if ((position.y - 8) % 16 == 0 && App->level_one->l1_map_array[array_pos.y][array_pos.x + 1] != 0 && ((position.x - 24) % 16 != 0))
			return false;

		return true;
		break;

	case leftDir:
		if (position.x - 24 == 0) //Checks map limits.(External walls)
			return true;

		else if ((position.y - 8) % 16 == 0 && (App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 10 || App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 0 || App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 5 || App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 6 || App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] == 7))
			return false;

		else if ((position.y - 8) % 16 == 0 && App->level_one->l1_map_array[array_pos.y][array_pos.x - 1] != 0 && ((position.x - 24) % 16 != 0))
			return false;

		return true;
		break;
	}
	return false;
}


// Update: draw background
update_status ModuleEnemy::Update()
{

	// CALCULATES THE ENEMY POSITION ON THE MAP ARRAY  --------------------------------------
	array_pos.x = (position.x - 24) / TILE;
	array_pos.y = (position.y - 40) / TILE;

	LOG("array_x: %d arra_y: %d", array_pos.x, array_pos.y);
	LOG("x: %d y: %d", position.x, position.y);

	// FILTERS PLAYER SPEED BASED ON COLLISIONS IN MAP  --------------------------------------
	if (enemy_dies != true)
	{
		if (OnCollision(upDir) && speed.y == -1)
		{
			speed.y = 1;
			current_animation = &up;
			countdown -= 1;
			if (OnCollision(rightDir) == false && countdown == 0)
			{
				speed.y = 0;
				speed.x = 1;
				countdown = 4;
			}
			else if (OnCollision(leftDir) == false && countdown == 0)
			{
				speed.y = 0;
				speed.x = -1;
				countdown = 4;
			}
		}

		if (OnCollision(downDir) && speed.y == 1)
		{
			speed.y = -1;
			current_animation = &down;
			countdown -= 1;
			if (OnCollision(rightDir) == false && countdown == 0)
			{
				speed.y = 0;
				speed.x = 1;
				countdown = 4;
			}
			else if (OnCollision(leftDir) == false && countdown == 0)
			{
				speed.y = 0;
				speed.x = -1;
				countdown = 4;
			}
		}

		if (OnCollision(rightDir) && speed.x == 1)
		{
			speed.x = -1;
			current_animation = &right;
			countdown -= 1;
			if (OnCollision(upDir) == false && countdown == 0)
			{
				speed.y = 1;
				speed.x = 0;
				countdown = 4;
			}
			else if (OnCollision(downDir) == false && countdown == 0)
			{
				speed.y = -1;
				speed.x = 0;
				countdown = 4;
			}
		}

		if (OnCollision(leftDir) && speed.x == -1)
		{
			speed.x = 1;
			current_animation = &left;
			countdown -= 1;
			if (OnCollision(upDir) == false && countdown == 0)
			{
				speed.y = 1;
				speed.x = 0;
				countdown = 4;
			}
			else if (OnCollision(downDir) == false && countdown == 0)
			{
				speed.y = -1;
				speed.x = 0;
				countdown = 4;
			}
		}
	}

	// UPDATES THE ENEMY ANIMATION BASED ON ENEMY'S SPEED
	if (speed.y == -1)
		current_animation = &up;

	else if (speed.y == 1)
		current_animation = &down;

	if (speed.x == 1)
		current_animation = &right;

	else if (speed.x == -1)
		current_animation = &left;

	// DEATH ANIMATION
	if (enemy_dies && upDir)
		current_animation = &dead_up;

	else if (enemy_dies && downDir)
		current_animation = &dead_down;

	else if (enemy_dies && rightDir)
		current_animation = &dead_right;

	else if (enemy_dies && leftDir)
		current_animation = &dead_left;

	// SCORE
	if (score_received == false && enemy_dies)
	{
		App->player->score += 100;
		score_received = true;
	}

	position.y += speed.y;

	if ((current_animation == &dead_up || current_animation == &dead_down) && current_animation->Finished())
	{
		Disable();
	}

	// DRAW ENEMY --------------------------------------
	
	if (speed.y != 0)
		App->renderer->Blit(graphics, position.x, position.y - 8, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}