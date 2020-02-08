/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:26:54 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 18:05:30 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	check_wall(t_elt *elt)
{
	if (elt->move.forward == 1)
	{
		if (elt->world[(int)(elt->plyr.x + elt->dir.x *
		elt->movespd)][(int)elt->plyr.y] != 0 ||
		elt->world[(int)elt->plyr.x][(int)(elt->plyr.y
		+ elt->dir.y * elt->movespd)] != 0)
		{
			Mix_PlayChannel(-1, elt->wallhit, 0);
			elt->health--;
		}
	}
	if (elt->move.backward == 1)
	{
		if (elt->world[(int)(elt->plyr.x - elt->dir.x *
		elt->movespd)][(int)elt->plyr.y] != 0 ||
		elt->world[(int)elt->plyr.x][(int)(elt->plyr.y
		- elt->dir.y * elt->movespd)] != 0)
		{
			Mix_PlayChannel(-1, elt->wallhit, 0);
			elt->health--;
		}
	}
}

void	play_sound(t_elt *elt)
{
	Mix_Music *music;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	elt->wallhit = Mix_LoadWAV("sounds/wallhit.wav");
	Mix_VolumeMusic(60);
	music = Mix_LoadMUS("sounds/music1.mp3");
	Mix_VolumeChunk(elt->wallhit, 120);
	Mix_PlayMusic(music, -1);
}

void	health_bar(t_elt *e)
{
	int i;

	i = 10;
	e->color = 0x0;
	verline(9, 10, 30, e);
	verline(10, 10, 30, e);
	e->color = 0xba0f0f;
	while (++i < e->health)
		verline(i, 10, 30, e);
	e->color = 0x0;
	verline(60, 10, 30, e);
	verline(61, 10, 30, e);
}

void	game_over(t_elt *e)
{
	ft_putendl_fd("**************************************************", 1);
	ft_putendl_fd("*************** YOU DIED AS A HERO ***************", 1);
	ft_putendl_fd("**************************************************", 1);
	ft_putendl_fd("==>> i made you leave so you can retry, SORRY <3 !", 1);
	close_win((void*)e);
}
