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

#define JOY_LEFT_STICK_X  16
#define JOY_LEFT_STICK_Y  17
#define JOY_RIGHT_STICK_X 18
#define JOY_RIGHT_STICK_Y 19

#define JOYSTICK_DEAD_ZONE 8000


#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

#define PLAYER_SPEED        4
#define PLAYER_BULLET_SPEED 20

#define MAX_JOYSTICK_BUTTONS       350
#define MAX_KEYBOARD_KEYS 350


#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define SIDE_PLAYER 0
#define SIDE_ALIEN  1

#define FPS 60

#define ALIEN_BULLET_SPEED    8

#define MAX_STARS   500

#define MAX_SND_CHANNELS 8

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH  18

enum
{
	CH_ANY = -1,
	CH_PLAYER,
	CH_ALIEN_FIRE,
	CH_POINTS
};

enum
{
	SND_PLAYER_FIRE,
	SND_ALIEN_FIRE,
	SND_PLAYER_DIE,
	SND_ALIEN_DIE,
	SND_POINTS,
	SND_MAX
};

enum
{
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};


#define MAX_SCORE_NAME_LENGTH 16
#define MAX_NAME_LENGTH       32
#define MAX_LINE_LENGTH       1024

#define NUM_HIGHSCORES 8