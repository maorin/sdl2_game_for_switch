#include "common.h"


#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"


App app;
Entity player;
Entity bullet;



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
	memset(&bullet, 0, sizeof(Entity));


	initSDL();

	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_JoystickOpen(0);

	player.x = 100;
	player.y = 100;

	char playTexturePath[] = "romfs:/data/player.png";
	player.texture = loadTexture(playTexturePath);

	char bulletTexturePath[] = "romfs:/data/playerBullet.png";
	bullet.texture = loadTexture(bulletTexturePath);
	

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

		if (app.up)
		{
			player.y -= 4;
		}

		if (app.down)
		{
			player.y += 4;
		}

		if (app.left)
		{
			player.x -= 4;
		}

		if (app.right)
		{
			player.x += 4;
		}

		if (app.fire && bullet.health == 0)
		{
			bullet.x = player.x;
			bullet.y = player.y;
			bullet.dx = 16;
			bullet.dy = 0;
			bullet.health = 1;
		}

		bullet.x += bullet.dx;
		bullet.y += bullet.dy;

		if (bullet.x > SCREEN_WIDTH)
		{
			bullet.health = 0;
		}

		blit(player.texture, player.x, player.y);

		if (bullet.health > 0)
		{
			blit(bullet.texture, bullet.x, bullet.y);
		}


		presentScene();

		SDL_Delay(16);
	}

	romfsExit();

	#ifdef DEBUG_MODE
    	socketExit();
    #endif
    return 0;
}
