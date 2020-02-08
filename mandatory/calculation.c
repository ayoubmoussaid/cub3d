/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:49:21 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/23 10:51:34 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	sort(t_elt *e)
{
	int		i;
	int		x;
	double	k;
	int		sorted;

	sorted = 0;
	while (!sorted)
	{
		i = -1;
		sorted = 1;
		while (++i < e->sp - 1)
		{
			if (e->spdst[i] < e->spdst[i + 1])
			{
				k = e->spdst[i];
				e->spdst[i] = e->spdst[i + 1];
				e->spdst[i + 1] = k;
				x = e->sporder[i];
				e->sporder[i] = e->sporder[i + 1];
				e->sporder[i + 1] = x;
				sorted = 0;
			}
		}
	}
}

void	count_sidedist(t_elt *e)
{
	if (e->raydir.x < 0)
	{
		e->step.x = -1;
		e->sidedist.x = (e->plyr.x - e->map.x) * e->deltadist.x;
	}
	else
	{
		e->step.x = 1;
		e->sidedist.x = (e->map.x + 1.0 - e->plyr.x) * e->deltadist.x;
	}
	if (e->raydir.y < 0)
	{
		e->step.y = -1;
		e->sidedist.y = (e->plyr.y - e->map.y) * e->deltadist.y;
	}
	else
	{
		e->step.y = 1;
		e->sidedist.y = (e->map.y + 1.0 - e->plyr.y) * e->deltadist.y;
	}
}

void	find_hit(t_elt *e)
{
	while (e->hit == 0)
	{
		if (e->sidedist.x < e->sidedist.y)
		{
			e->sidedist.x += e->deltadist.x;
			e->map.x += e->step.x;
			e->side = 0;
		}
		else
		{
			e->sidedist.y += e->deltadist.y;
			e->map.y += e->step.y;
			e->side = 1;
		}
		if (e->world[e->map.x][e->map.y] == 1)
			e->hit = 1;
	}
}

void	calc_start_end(t_elt *e)
{
	if (e->side == 0)
		e->perpwalldist = (e->map.x - e->plyr.x
			+ (1 - e->step.x) / 2) / e->raydir.x;
	else
		e->perpwalldist = (e->map.y - e->plyr.y
			+ (1 - e->step.y) / 2) / e->raydir.y;
	e->lineheight = (int)(e->h / e->perpwalldist);
	e->drawstart = -e->lineheight / 2 + e->h / 2;
	if (e->drawstart < 0)
		e->drawstart = 0;
	e->drawend = e->lineheight / 2 + e->h / 2;
	if (e->drawend >= e->h)
		e->drawend = e->h - 1;
}

void	calc_sprite_dim(t_elt *e, int i)
{
	e->s.spx = e->sprts[e->sporder[i]].x - e->plyr.x;
	e->s.spy = e->sprts[e->sporder[i]].y - e->plyr.y;
	e->s.det = 1.0 / (e->plan.x * e->dir.y - e->dir.x * e->plan.y);
	e->s.trx = e->s.det * (e->dir.y * e->s.spx - e->dir.x * e->s.spy);
	e->s.try = e->s.det * (-e->plan.y * e->s.spx + e->plan.x * e->s.spy);
	e->s.spritescreenx = (int)((e->w / 2) * (1 + e->s.trx / e->s.try));
	e->s.spriteh = abs((int)(e->h / e->s.try));
	e->s.drawstarty = -e->s.spriteh / 2 + e->h / 2;
	if (e->s.drawstarty < 0)
		e->s.drawstarty = 0;
	e->s.drawendy = e->s.spriteh / 2 + e->h / 2;
	if (e->s.drawendy >= e->h)
		e->s.drawendy = e->h - 1;
	e->s.spritew = abs((int)(e->h / e->s.try));
	e->s.drawstartx = -e->s.spritew / 2 + e->s.spritescreenx;
	if (e->s.drawstartx < 0)
		e->s.drawstartx = 0;
	e->s.drawendx = e->s.spritew / 2 + e->s.spritescreenx;
	if (e->s.drawendx >= e->w)
		e->s.drawendx = e->w - 1;
}
