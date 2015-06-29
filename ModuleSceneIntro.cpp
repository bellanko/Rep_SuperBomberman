#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

// SUPER BOMBERMAN SNES PROJECT

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	pantalla_inicio = NULL;
	fx = 0;
	ping = 0;

	// Background
	background.frames.PushBack({ 0, 96, 256, 224 });
	background.loop = false;
	background.speed = 0.1f;

	// Zepelin "H"
	zepelin_h.frames.PushBack({ 0, 77, 31, 18 });
	zepelin_h.loop = false;
	zepelin_h.speed = 0.1f;

	// Zepelin "Fire"
	zepelin_fire.frames.PushBack({ 116, 41, 72, 40 });
	zepelin_fire.frames.PushBack({ 43, 41, 72, 40 });
	zepelin_fire.frames.PushBack({ 189, 41, 72, 40 });
	zepelin_fire.frames.PushBack({ 43, 0, 72, 40 });
	zepelin_fire.frames.PushBack({ 262, 41, 72, 40 });
	zepelin_fire.frames.PushBack({ 116, 0, 72, 40 });
	zepelin_fire.frames.PushBack({ 335, 0, 72, 40 });
	zepelin_fire.frames.PushBack({ 189, 0, 72, 40 });
	zepelin_fire.frames.PushBack({ 262, 0, 72, 40 });
	zepelin_fire.loop = true;
	zepelin_fire.speed = 0.4f;

	// Globo
	globo.frames.PushBack({ 0, 0, 42, 76 });
	globo.loop = false;
	globo.speed = 0.1f;

	// Bomberman Title
	bomberman_left.frames.PushBack({ 80, 321, 256, 112 });
	bomberman_left.loop = true;
	bomberman_left.speed = 1.0f;

	bomberman_right.frames.PushBack({ 80, 433, 256, 112 });
	bomberman_right.loop = true;
	bomberman_right.speed = 1.0f;

	flash.frames.PushBack({ 257, 96, 256, 112 });
	flash.loop = false;
	flash.speed = 0.05f;

	// Arrow
	arrow.frames.PushBack({ 32, 77, 10, 14 });
	arrow.loop = false;
	arrow.speed = 0.5f;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	x_background = &background;
	x_zepelin_h = &zepelin_h;
	x_zepelin_fire = &zepelin_fire;
	x_globo = &globo;
	x_bomberman_left = &bomberman_left;
	x_bomberman_right = &bomberman_right;
	x_flash = &flash;
	x_arrow = &arrow;

	// Initial Positions of each Floating Object
	pos_zep_h.x = 50;
	pos_zep_h.y = 120;
	pos_zep_fire.x = 180;
	pos_zep_fire.y = 85;
	pos_globo.x = 10;
	pos_globo.y = 5;
	pos_title = 0;

	// Initial Values for Timers
	contador_titulo = 0;
	contador = 0;
	flash_duration = 0;

	//Menu Keyboard Initial Value
	menu_key = 1;
	finish_intro = false;

	App->audio->Enable();
	pantalla_inicio = App->textures->Load("Resources/Pantalla_Inicio.png");
	App->audio->PlayMusic("Resources/01_intro.ogg", 0.0f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(pantalla_inicio);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(pantalla_inicio, 0, 0, &(x_background->GetCurrentFrame()));
	App->renderer->Blit(pantalla_inicio, pos_zep_h.x, pos_zep_h.y, &(x_zepelin_h->GetCurrentFrame()));
	App->renderer->Blit(pantalla_inicio, pos_zep_fire.x, pos_zep_fire.y, &(x_zepelin_fire->GetCurrentFrame()));
	App->renderer->Blit(pantalla_inicio, pos_globo.x, pos_globo.y, &(x_globo->GetCurrentFrame()));

	// Timers and Actions
	contador_titulo++;
	contador++;

	if (contador == 4)
	{
		pos_zep_fire.x -= 1;
	}

	if (contador == 6)
	{
		pos_zep_h.x += 1;
	}

	if (contador >= 8)
	{
		pos_zep_fire.x -= 1;
		pos_globo.x += 1;
		if ((pos_globo.x / 8) % 2 >= 0.5f)
			pos_globo.y += 1;
		else
			pos_globo.y -= 1;
		contador = 0;
	}

	// Titulo Bomberman
	if (contador_titulo >= 240)
	{
		App->renderer->Blit(pantalla_inicio, -255 + pos_title, 1, &(x_bomberman_left->GetCurrentFrame()));
		App->renderer->Blit(pantalla_inicio, 255 - pos_title, 113, &(x_bomberman_right->GetCurrentFrame()));
		
		if (pos_title < 255)
		{
			pos_title += 5;

			if (pos_title < 255)
				pos_title += 5; // Smooth
		}
	}
	
	// Flash
	if (pos_title == 255)
	{
		flash_duration++;
		if (flash_duration <= 10)
		{
			App->renderer->Blit(pantalla_inicio, 1, 1, &(x_flash->GetCurrentFrame()));
			App->renderer->Blit(pantalla_inicio, 1, 113, &(x_flash->GetCurrentFrame()));
		}
	}

	if ((contador_titulo >= 300) && (menu_key == 1))
	{
		App->audio->PlayFx(ping);
		App->renderer->Blit(pantalla_inicio, 61, 153, &(x_arrow->GetCurrentFrame()));
	}

	if ((contador_titulo >= 300) && (menu_key == 2))
	{
		App->audio->PlayFx(ping);
		App->renderer->Blit(pantalla_inicio, 61, 167, &(x_arrow->GetCurrentFrame()));
	}

	if ((contador_titulo >= 300) && (menu_key == 3))
	{
		App->audio->PlayFx(ping);
		App->renderer->Blit(pantalla_inicio, 61, 181, &(x_arrow->GetCurrentFrame()));
	}

	fx = App->audio->LoadFx("Resources/selection_change.wav");

	// Keyboard
	if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_UP) && (contador_titulo >= 300) && (finish_intro == false))
	{
		App->audio->PlayFx(fx);
		menu_key--;
		if (menu_key == 0)
		{
			menu_key = 3;
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP) && (contador_titulo >= 300) && (finish_intro == false))
	{
		App->audio->PlayFx(fx);
		menu_key++;
		if (menu_key == 4)
		{
			menu_key = 1;
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP) && (contador_titulo >= 300) && (finish_intro == false))
	{
		menu_key = 1;
		finish_intro = true;
		fx = App->audio->LoadFx("Resources/menu_confirm.wav");
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(this, App->level_one, 3.0f);
	}

	return UPDATE_CONTINUE;
}