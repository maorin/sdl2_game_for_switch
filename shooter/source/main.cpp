#include "common.h"


#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"


App app;
Entity player;



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
	romfsInit();
	chdir("romfs:/");

	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));

	initSDL();

	player.x = 100;
	player.y = 100;

	char texturePath[] = "romfs:/data/player.png";
	player.texture = loadTexture(texturePath);

	printf("C hello \n");
	std::cout << "C++  hello" << std::endl;

	//SDL_Surface *sdllogo = IMG_Load("romfs:/data/sdl.png");
	//SDL_Surface *sdllogo = IMG_Load("data/sdl.png");
	//std::cout << "sdllogo: " << sdllogo << std::endl;

	atexit(cleanup);

	while (1)
	{
		prepareScene();

		doInput();

		blit(player.texture, player.x, player.y);

		presentScene();

		SDL_Delay(16);
	}

	romfsExit();

	#ifdef DEBUG_MODE
    	socketExit();
    #endif
    return 0;
}
