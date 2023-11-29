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

	memset(app.inputText, '\0', MAX_LINE_LENGTH);

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_JOYAXISMOTION:
				if (event.jaxis.axis == 0) // X轴
				{
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						// 执行向左操作
						app.joystick[JOY_LEFT] = 1;
						app.joystick[JOY_RIGHT] = 0;
					}
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						// 执行向右操作
						app.joystick[JOY_LEFT] = 0;
						app.joystick[JOY_RIGHT] = 1;
					}
				}
				else if (event.jaxis.axis == 1) // Y轴
				{
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						// 执行向上操作
						app.joystick[JOY_UP] = 1;
						app.joystick[JOY_DOWN] = 0;
					}
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						// 执行向下操作
						app.joystick[JOY_UP] = 0;
						app.joystick[JOY_DOWN] = 1;
					}
				}

			case SDL_JOYBUTTONDOWN:
				doJoyButtonDown(&event.jbutton);
				break;

			case SDL_JOYBUTTONUP:
				doJoyButtonUp(&event.jbutton);
				break;

			case SDL_TEXTINPUT:
				STRNCPY(app.inputText, event.text.text, MAX_LINE_LENGTH);
				break;


			default:
				break;
		}
	}
}