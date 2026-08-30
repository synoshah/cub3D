#pragma once

typedef enum e_gamemode
{
	START,
	PLAYING,
	LOST,
	WON
}	t_gamemode;

typedef struct s_game_state
{
	int			level;
	e_gamemode	gamemode;
	int			imgaes;
}	t_game_state;
