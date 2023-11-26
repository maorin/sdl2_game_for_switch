/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "input.h"

extern App app;

static void doKeyUp(SDL_JoyButtonEvent *event)
{
	if (event->button == JOY_UP)
	{
		app.up = 0;
	}

	if (event->button == JOY_DOWN)
	{
		app.down = 0;
	}

	if (event->button == JOY_LEFT)
	{
		app.left = 0;
	}

	if (event->button == JOY_RIGHT)
	{
		app.right = 0;
	}
	
}

static void doKeyDown(SDL_JoyButtonEvent *event)
{

	if (event->button == JOY_UP)
	{
		app.up = 1;
	}

	if (event->button == JOY_DOWN)
	{
		app.down = 1;
	}

	if (event->button == JOY_LEFT)
	{
		app.left = 1;
	}

	if (event->button == JOY_RIGHT)
	{
		app.right = 1;
	}

}

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			
			case SDL_JOYBUTTONDOWN:
				doKeyDown(&event.jbutton);
				break;

			case SDL_JOYBUTTONUP:
				doKeyUp(&event.jbutton);
				break;

			default:
				break;
		}
	}
}