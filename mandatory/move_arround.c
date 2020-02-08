/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_arround.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:42:45 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/23 17:25:43 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	for_back(t_elt *e)
{
	if (e->move.forward == 1)
	{
		if (e->world[(int)(e->plyr.x + e->dir.x * e->movespd)][(int)e->plyr.y]
				== 0)
			e->plyr.x += e->dir.x * (e->movespd - 0.01);
		if (e->world[(int)e->plyr.x][(int)(e->plyr.y + e->dir.y * e->movespd)]
				== 0)
			e->plyr.y += e->dir.y * (e->movespd - 0.01);
	}
	if (e->move.backward == 1)
	{
		if (e->world[(int)(e->plyr.x - e->dir.x * e->movespd)][(int)e->plyr.y]
				== 0)
			e->plyr.x -= e->dir.x * (e->movespd - 0.01);
		if (e->world[(int)e->plyr.x][(int)(e->plyr.y - e->dir.y * e->movespd)]
				== 0)
			e->plyr.y -= e->dir.y * (e->movespd - 0.01);
	}
}

void	left_right(t_elt *e)
{
	if (e->move.left == 1)
	{
		if (e->world[(int)(e->plyr.x - e->dir.y * e->movespd)][(int)e->plyr.y]
				== 0)
			e->plyr.x -= e->dir.y * (e->movespd - 0.01);
		if (e->world[(int)e->plyr.x][(int)(e->plyr.y + e->dir.x * e->movespd)]
				== 0)
			e->plyr.y += e->dir.x * (e->movespd - 0.01);
	}
	if (e->move.right == 1)
	{
		if (e->world[(int)(e->plyr.x + e->dir.y * e->movespd)][(int)e->plyr.y]
				== 0)
			e->plyr.x += e->dir.y * e->movespd;
		if (e->world[(int)e->plyr.x][(int)(e->plyr.y - e->dir.x * e->movespd)]
					== 0)
			e->plyr.y -= e->dir.x * e->movespd;
	}
}

void	rot_left_right(t_elt *e)
{
	double odx;
	double opx;

	if (e->move.leftr == 1)
	{
		odx = e->dir.x;
		e->dir.x = e->dir.x * cos(-e->rotspd) - e->dir.y * sin(-e->rotspd);
		e->dir.y = odx * sin(-e->rotspd) + e->dir.y * cos(-e->rotspd);
		opx = e->plan.x;
		e->plan.x = e->plan.x * cos(-e->rotspd) - e->plan.y * sin(-e->rotspd);
		e->plan.y = opx * sin(-e->rotspd) + e->plan.y * cos(-e->rotspd);
	}
	if (e->move.rightr == 1)
	{
		odx = e->dir.x;
		e->dir.x = e->dir.x * cos(e->rotspd) - e->dir.y * sin(e->rotspd);
		e->dir.y = odx * sin(e->rotspd) + e->dir.y * cos(e->rotspd);
		opx = e->plan.x;
		e->plan.x = e->plan.x * cos(e->rotspd) - e->plan.y * sin(e->rotspd);
		e->plan.y = opx * sin(e->rotspd) + e->plan.y * cos(e->rotspd);
	}
}

int		walk_arround(void *param)
{
	t_elt *e;

	e = (t_elt*)param;
	for_back(e);
	left_right(e);
	rot_left_right(e);
	mlx_destroy_image(e->m_ptr, e->i_ptr);
	mlx_clear_window(e->m_ptr, e->win);
	e->i_ptr = mlx_new_image(e->m_ptr, e->w, e->h);
	e->i_data = (int*)mlx_get_data_addr(e->i_ptr,
		&(e->bpp), &(e->sizeline), &(e->endian));
	draw_map(e);
	mlx_put_image_to_window(e->m_ptr, e->win, e->i_ptr, 0, 0);
	return (0);
}
