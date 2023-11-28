/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include <SDL2/SDL_mixer.h>

#include "common.h"

#include "sound.h"

static void loadSounds(void);

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

void initSounds(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);

	music = NULL;

	loadSounds();
}

void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void)
{
	char sdd_player_fire[] = "romfs:/data/sound/334227__jradcoolness__laser.ogg";
	sounds[SND_PLAYER_FIRE] = Mix_LoadWAV(sdd_player_fire);

	char sdd_alien_fire[] = "romfs:/data/sound/196914__dpoggioli__laser-gun.ogg";
	sounds[SND_ALIEN_FIRE] = Mix_LoadWAV(sdd_alien_fire);

	char sdd_player_die[] = "romfs:/data/sound/245372__quaker540__hq-explosion.ogg";
	sounds[SND_PLAYER_DIE] = Mix_LoadWAV(sdd_player_die);

	char sdd_alien_die[] = "romfs:/data/sound/10 Guage Shotgun-SoundBible.com-74120584.ogg";
	sounds[SND_ALIEN_DIE] = Mix_LoadWAV(sdd_alien_die);
}
