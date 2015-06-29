#include "Globals.h"
#include "Application.h"
#include "ModuleDrawMap.h"

ModuleDrawMap::ModuleDrawMap(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	elements = NULL;

	// falsewall
	falsewall.frames.PushBack({ 32, 24, 16, 16 });
	falsewall.frames.PushBack({ 48, 24, 16, 16 });
	falsewall.frames.PushBack({ 64, 24, 16, 16 });
	falsewall.frames.PushBack({ 80, 24, 16, 16 });

	falsewall.loop = true;
	falsewall.speed = 0.005f;

	//wall
	wall.frames.PushBack({ 0, 24, 16, 16 });
	wall.loop = false;
	wall.speed = 0.1f;

	//wall_boss
	wall_boss.frames.PushBack({ 160, 56, 16, 16 });
	wall_boss.loop = false;
	wall_boss.speed = 0.1f;

	//flooor_boss
	floor_boss.frames.PushBack({ 160, 40, 16, 16 });
	floor_boss.loop = false;
	floor_boss.speed = 0.1f;

	//floor1
	floor1.frames.PushBack({ 16, 24, 16, 16 });
	floor1.loop = false;
	floor1.speed = 0.1f;

	//floor2
	floor2.frames.PushBack({ 96, 24, 16, 16 });
	floor2.loop = false;
	floor2.speed = 0.1f;

	//floor3
	floor3.frames.PushBack({ 112, 24, 16, 16 });
	floor3.loop = false;
	floor3.speed = 0.1f;

	//finish
	finish.frames.PushBack({ 224, 24, 16, 16 });
	finish.frames.PushBack({ 240, 24, 16, 16 });
	finish.loop = true;
	finish.speed = 0.3f;

	// SPEED POWERUP
	powerup_speed.frames.PushBack({ 128, 24, 16, 16 });
	powerup_speed.frames.PushBack({ 144, 24, 16, 16 });
	powerup_speed.loop = true;
	powerup_speed.speed = 0.1f;

	// RANGE POWERUP
	powerup_range.frames.PushBack({ 128, 40, 16, 16 });
	powerup_range.frames.PushBack({ 144, 40, 16, 16 });
	powerup_range.loop = true;
	powerup_range.speed = 0.1f;
}

ModuleDrawMap::~ModuleDrawMap()
{}

// Load assets
bool ModuleDrawMap::Start()
{
	LOG("Loading Map assets");
	elements = App->textures->Load("Resources/Elements.png");

	awall = &wall;
	awall_boss = &wall_boss;
	afloor1 = &floor1;
	afloor2 = &floor2;
	afloor3 = &floor3;
	afloor_boss = &floor_boss;
	afalsewall = &falsewall;
	afinish = &finish;
	abomb = &bomb;
	apowerup_speed = &powerup_speed;
	apowerup_range = &powerup_range;

	return true;
}


// Load assets
bool ModuleDrawMap::CleanUp()
{
	LOG("Unloading Map");

	App->textures->Unload(elements);

	return true;

}

// Update: draw background
update_status ModuleDrawMap::Update()
{
	// Draw everything --------------------------------------	
	for (int x = 0; x < HEIGHT; x++)
	{
		for (int y = 0; y < WIDTH; y++)
		{
			if (App->level_one->l1_map_array[3][0] == 0)
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(afloor2->GetCurrentFrame())); //Basic Floor, no shadows.

			if (x == 0)
			{
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(afloor1->GetCurrentFrame())); //First line shadows.
			}

			if (App->level_one->l1_map_array[x][y] == 1) //Basic Wall, no shadows
			{
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(awall->GetCurrentFrame()));
			}

			if (App->level_one->l1_map_array[x - 1][y] == 1 && App->level_one->l1_map_array[x][y] != 1) //Walls under shadow.
			{
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(afloor1->GetCurrentFrame()));
			}

			if (App->level_one->l1_map_array[x][y] == 2) //Basic FalseWall, no shadows.
			{
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(afalsewall->GetCurrentFrame()));
			}

			if (App->level_one->l1_map_array[x - 1][y] == 2 && App->level_one->l1_map_array[x][y] == 0) //Walls under shadow.
			{
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(afloor3->GetCurrentFrame()));
			}

			if (App->level_one->l1_map_array[x][y] == 5) //Powerup Speed
			{
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(apowerup_speed->GetCurrentFrame()));
			}

			if (App->level_one->l1_map_array[x][y] == 6) //Powerup Range
			{
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(apowerup_range->GetCurrentFrame()));
			}

			if (App->level_one->l1_map_array[x][y] == 7) //Finish
			{
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(afinish->GetCurrentFrame()));
			}

			if (App->level_one->l1_map_array[0][0] == 10)
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(afloor_boss->GetCurrentFrame()));
			
			
			if (App->level_one->l1_map_array[x][y] == 11) //Wall_boss
			{
				App->renderer->Blit(elements, (y * TILE) + 24, (x * TILE) + 40, &(awall_boss->GetCurrentFrame()));
			}

		}
	}

	return UPDATE_CONTINUE;
}
