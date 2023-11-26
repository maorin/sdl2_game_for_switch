/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "input.h"

extern App app;


static void doJoyButtonUp(SDL_JoyButtonEvent *event)
{
	if (event->state == SDL_RELEASED && event->button < MAX_JOYSTICK_BUTTONS)
	{
		app.joystick[event->button] = 0;
	}
}


static void doJoyButtonDown(SDL_JoyButtonEvent *event)
{

	if (event->state == SDL_PRESSED && event->button < MAX_JOYSTICK_BUTTONS)
	{
		app.joystick[event->button] = 1;
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
				doJoyButtonDown(&event.jbutton);
				break;

			case SDL_JOYBUTTONUP:
				doJoyButtonUp(&event.jbutton);
				break;

			default:
				break;
		}
	}
}