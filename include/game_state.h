#pragma once

typedef enum e_gamemode
{
	START,
	PLAYING,
	LOST,
	WON,
	DONE
}	t_gamemode;

typedef struct s_game_state
{
	int			level;
	t_gamemode	gamemode;
}	t_game_state;
