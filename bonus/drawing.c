/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:54:10 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/23 11:43:32 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	verline(int x, int y0, int y1, t_elt *e)
{
	int i;

	i = y0;
	while (i <= y1)
	{
		e->i_data[x + e->w * i] = e->color;
		i++;
	}
}

void	draw_texts_mapping(t_elt *e, int x)
{
	if (e->side == 1 && e->raydir.y < 0)
		e->i_data[x + e->w * e->v.i] =
			e->text[0].i_data[e->text[0].a * e->v.ty + e->v.tx];
	if (e->side == 1 && e->raydir.y > 0)
		e->i_data[x + e->w * e->v.i] =
			e->text[1].i_data[e->text[1].a * e->v.ty + e->v.tx];
	if (e->side == 0 && e->raydir.x > 0)
		e->i_data[x + e->w * e->v.i] =
			e->text[2].i_data[e->text[2].a * e->v.ty + e->v.tx];
	if (e->side == 0 && e->raydir.x < 0)
		e->i_data[x + e->w * e->v.i] =
			e->text[3].i_data[e->text[3].a * e->v.ty + e->v.tx];
}

void	draw_texts(t_elt *e, int x)
{
	e->v.tex_num = e->world[e->map.x][e->map.y] - 1;
	e->v.wallx = (e->side == 0 ? e->plyr.y + e->perpwalldist
		* e->raydir.y : e->plyr.x + e->perpwalldist * e->raydir.x);
	e->v.wallx -= floor(e->v.wallx);
	e->v.tx = (int)(e->v.wallx * (double)e->text[0].a);
	if (e->side == 0 && e->raydir.x > 0)
		e->v.tx = e->text[0].b - e->v.tx - 1;
	if (e->side == 1 && e->raydir.y < 0)
		e->v.tx = e->text[0].b - e->v.tx - 1;
	e->v.step = 1.0 * e->text[0].b / e->lineheight;
	e->v.texpos = (e->drawstart - e->h / 2 + e->lineheight / 2) * e->v.step;
	e->v.i = e->drawstart - 1;
	while (++(e->v.i) <= e->drawend)
	{
		e->v.ty = (int)e->v.texpos & (e->text[0].b - 1);
		e->v.texpos += e->v.step;
		draw_texts_mapping(e, x);
	}
}

void	draw_sprite_on_screen(t_elt *e, int d)
{
	int x;
	int y;
	int tx;
	int ty;
	int color;

	x = e->s.drawstartx - 1;
	while (++x < e->s.drawendx)
	{
		tx = (int)(256 * (x - (-e->s.spritew / 2 + e->s.spritescreenx)) *
			e->sprite.a / e->s.spritew) / 256;
		if (e->s.try > 0 && x > 0 && x < e->w && e->s.try < e->zbuffer[x])
		{
			y = e->s.drawstarty - 1;
			while (++y < e->s.drawendy)
			{
				d = y * 256 - e->h * 128 + e->s.spriteh * 128;
				ty = ((d * e->sprite.b) / e->s.spriteh) / 256;
				color = e->sprite.i_data[e->sprite.b * ty + tx];
				if (color != 0x0000000)
					e->i_data[x + e->w * y] = color;
			}
		}
	}
}

void	draw_sprites(t_elt *e)
{
	int i;

	i = -1;
	while (++i < e->sp)
	{
		e->sporder[i] = i;
		e->spdst[i] = (e->plyr.x - e->sprts[i].x) * (e->plyr.x - e->sprts[i].x)
			+ (e->plyr.y - e->sprts[i].y) * (e->plyr.y - e->sprts[i].y);
	}
	sort(e);
	i = -1;
	while (++i < e->sp)
	{
		calc_sprite_dim(e, i);
		draw_sprite_on_screen(e, 0);
	}
}
