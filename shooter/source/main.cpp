#include "common.h"


#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"
#include "sound.h"
#include "stage.h"


App app;
Stage stage;

static void capFrameRate(long *then, float *remainder);



int main(int argc, char *argv[])
{
	/**
	 * 这个是debug到shell 打印的信息
	 * 需要释放socket
	 * nxlink -s -a 192.168.178.4 shooter.nro 
	*/
	#ifdef DEBUG_MODE
		socketInitializeDefault();
		nxlinkStdio();
	#endif

	/**
	 * 这个地方是SDL2的初始化 在switch上不一样的地方 需要初始化这个romfs
	 * 资源文件在romfs:/data/下面
	 * 需要释放romfs
	*/

	long  then;
	float remainder;

	romfsInit();
	chdir("romfs:/");

	memset(&app, 0, sizeof(App));



	initSDL();

	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_JoystickOpen(0);

	atexit(cleanup);

	initSounds();

	initStage();

	printf("C hello \n");
	std::cout << "C++  hello" << std::endl;

	then = SDL_GetTicks();
	remainder = 0;


	while (1)
	{
		prepareScene();

		doInput();

		app.delegate.logic();

		app.delegate.draw();

		presentScene();

		capFrameRate(&then, &remainder);
	}

	romfsExit();

	#ifdef DEBUG_MODE
    	socketExit();
    #endif
    return 0;
}

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}
