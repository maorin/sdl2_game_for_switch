// some switch buttons
#define JOY_A     0
#define JOY_B     1
#define JOY_X     2
#define JOY_Y     3
#define JOY_PLUS  10
#define JOY_MINUS 11
#define JOY_LEFT  12
#define JOY_UP    13
#define JOY_RIGHT 14
#define JOY_DOWN  15


#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

#define PLAYER_SPEED        4
#define PLAYER_BULLET_SPEED 20

#define MAX_JOYSTICK_BUTTONS       350


#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


#define SIDE_PLAYER 0
#define SIDE_ALIEN  1

#define FPS 60

#define ALIEN_BULLET_SPEED    8

#define MAX_STARS   500

#define MAX_SND_CHANNELS 8

enum
{
	CH_ANY = -1,
	CH_PLAYER,
	CH_ALIEN_FIRE
};

enum
{
	SND_PLAYER_FIRE,
	SND_ALIEN_FIRE,
	SND_PLAYER_DIE,
	SND_ALIEN_DIE,
	SND_MAX
};

#define MAX_LINE_LENGTH 1024