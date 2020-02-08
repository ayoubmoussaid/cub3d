/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_arround.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:42:45 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 17:56:26 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	check_mouse(t_elt *elt)
{
	int		x;
	int		y;
	double	olddirx;
	double	oldplanex;
	double	value;

	mlx_mouse_get_pos(elt->win, &x, &y);
	value = 0.5 / ((float)-elt->w / 2);
	value = value * (x - elt->w / 2);
	olddirx = elt->dir.x;
	elt->dir.x = elt->dir.x * cos(value) - elt->dir.y * sin(value);
	elt->dir.y = olddirx * sin(value) + elt->dir.y * cos(value);
	oldplanex = elt->plan.x;
	elt->plan.x = elt->plan.x * cos(value) - elt->plan.y * sin(value);
	elt->plan.y = oldplanex * sin(value) + elt->plan.y * cos(value);
}

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
	check_wall(e);
	for_back(e);
	left_right(e);
	rot_left_right(e);
	if (e->mouse == 1)
	{
		check_mouse(e);
		mlx_mouse_move(e->win, (int)(e->w / 2), (int)(e->h / 2));
	}
	mlx_destroy_image(e->m_ptr, e->i_ptr);
	mlx_clear_window(e->m_ptr, e->win);
	e->i_ptr = mlx_new_image(e->m_ptr, e->w, e->h);
	e->i_data = (int*)mlx_get_data_addr(e->i_ptr,
		&(e->bpp), &(e->sizeline), &(e->endian));
	draw_map(e);
	health_bar(e);
	mlx_put_image_to_window(e->m_ptr, e->win, e->i_ptr, 0, 0);
	if (e->health <= 0)
		game_over(e);
	return (0);
}
