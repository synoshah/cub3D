/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:47:05 by synoshah          #+#    #+#             */
/*   Updated: 2026/09/03 21:47:05 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
