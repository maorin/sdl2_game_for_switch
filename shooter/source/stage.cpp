/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "draw.h"
#include "stage.h"

extern App   app;
extern Stage stage;

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doFighters(void);
static void doPlayer(void);
static void doBullets(void);
static void drawPlayer(void);
static void drawFighters(void);
static void drawBullets(void);
static void spawnEnemies(void);

static Entity      *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static int          enemySpawnTimer;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	initPlayer();

	char bulletTexturePath[] = "romfs:/data/playerBullet.png";
	bulletTexture = loadTexture(bulletTexturePath);
	//bulletTexture = loadTexture("gfx/playerBullet.png");

	char enemyTexturePath[] = "romfs:/data/enemy.png";
	enemyTexture = loadTexture(enemyTexturePath);

	enemySpawnTimer = 0;
}

static void initPlayer()
{
	player = static_cast<Entity*>(malloc(sizeof(Entity)));
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;

	player->x = 100;
	player->y = 100;

	char playTexturePath[] = "romfs:/data/player.png";
	player->texture = loadTexture(playTexturePath);

	//player->texture = loadTexture("gfx/player.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void logic(void)
{
	doPlayer();

	doFighters();

	doBullets();

	spawnEnemies();
}

static void doPlayer(void)
{
	player->dx = player->dy = 0;

	if (player->reload > 0)
	{
		player->reload--;
	}

	if (app.joystick[JOY_UP])
	{
		player->dy = -PLAYER_SPEED;
	}

	if (app.joystick[JOY_DOWN])
	{
		player->dy = PLAYER_SPEED;
	}

	if (app.joystick[JOY_LEFT])
	{
		player->dx = -PLAYER_SPEED;
	}

	if (app.joystick[JOY_RIGHT])
	{
		player->dx = PLAYER_SPEED;
	}

	if (app.joystick[JOY_A] && player->reload == 0)
	{
		fireBullet();
	}

	player->x += player->dx;
	player->y += player->dy;
}

static void fireBullet(void)
{
	Entity *bullet;

	bullet = static_cast<Entity*>(malloc(sizeof(Entity)));
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = player->x;
	bullet->y = player->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = bulletTexture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->y += (player->h / 2) - (bullet->h / 2);

	player->reload = 8;
}

static void doBullets(void)
{
	Entity *b, *prev;

	prev = &stage.bulletHead;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;

		if (b->x > SCREEN_WIDTH)
		{
			if (b == stage.bulletTail)
			{
				stage.bulletTail = prev;
			}

			prev->next = b->next;
			free(b);
			b = prev;
		}

		prev = b;
	}
}

static void doFighters(void)
{
	Entity *e, *prev;

	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;

		if (e != player && e->x < -e->w)
		{
			if (e == stage.fighterTail)
			{
				stage.fighterTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

static void spawnEnemies(void)
{
	Entity *enemy;

	if (--enemySpawnTimer <= 0)
	{
		enemy = static_cast<Entity*>(malloc(sizeof(Entity)));
		memset(enemy, 0, sizeof(Entity));
		stage.fighterTail->next = enemy;
		stage.fighterTail = enemy;

		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT;
		enemy->texture = enemyTexture;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

		enemy->dx = -(2 + (rand() % 4));

		enemySpawnTimer = 30 + (rand() % 60);
	}
}


static void draw(void)
{
	drawFighters();

	drawBullets();
}

static void drawPlayer(void)
{
	blit(player->texture, player->x, player->y);
}

static void drawFighters(void)
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x, e->y);
	}
}

static void drawBullets(void)
{
	Entity *b;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		blit(b->texture, b->x, b->y);
	}
}
