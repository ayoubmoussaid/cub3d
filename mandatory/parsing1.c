/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 19:26:55 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 16:27:53 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

static void	fill(t_elt *e, double a, double b, int x)
{
	if (x == 1)
	{
		e->dir.x = a;
		e->dir.y = 0;
		e->plan.x = 0;
		e->plan.y = b;
	}
	else
	{
		e->dir.x = 0;
		e->dir.y = a;
		e->plan.x = b;
		e->plan.y = 0;
	}
}

static void	fill_direction(char c, t_elt *e)
{
	if (c == 'S')
		fill(e, 1, -0.66, 1);
	else if (c == 'N')
		fill(e, -1, 0.66, 1);
	else if (c == 'W')
		fill(e, 1, 0.66, 0);
	else if (c == 'E')
		fill(e, -1, -0.66, 0);
}

void		make_map(t_elt *e, int k)
{
	int i;
	int j;

	e->mapheight = ft_strlen(e->worldmap) / e->mapwidth;
	e->world = (int**)malloc(sizeof(int*) * e->mapheight);
	i = -1;
	while (++i < e->mapheight)
	{
		j = -1;
		e->world[i] = (int*)malloc(sizeof(int) * e->mapwidth);
		while (++j < e->mapwidth)
		{
			if (ft_isdigit(e->worldmap[k]))
				e->world[i][j] = e->worldmap[k++] - '0';
			else
			{
				e->world[i][j] = 0;
				e->plyr.x = i + 0.5;
				e->plyr.y = j + 0.5;
				fill_direction(e->worldmap[k++], e);
			}
			if (e->worldmap[k] == '2')
				e->sp++;
		}
	}
}

void		check_map(t_elt *e, int i, int j)
{
	i = -1;
	j = 0;
	while (e->worldmap[++i] != '\0')
		if (ft_isdigit(e->worldmap[i]) == 0 || (e->worldmap[i] != '1' &&
			e->worldmap[i] != '0' && e->worldmap[i] != '2'))
			j++;
	if (j != 1)
		ft_error("multiple spawn places or unknown identifiers!");
	i = -1;
	while (++i < e->mapheight)
		if (e->world[i][0] != 1)
			ft_error("map borders are not set to one");
	i = -1;
	while (++i < e->mapheight)
		if (e->world[i][e->mapwidth - 1] != 1)
			ft_error("map borders are not set to one");
	i = -1;
	while (++i < e->mapwidth)
		if (e->world[0][i] != 1)
			ft_error("map borders are not set to one");
	i = -1;
	while (++i < e->mapwidth)
		if (e->world[e->mapheight - 1][i] != 1)
			ft_error("map borders are not set to one");
}

void		take_pos(t_elt *e)
{
	int k;
	int i;
	int j;

	k = 0;
	i = -1;
	e->zbuffer = (double*)malloc(e->w * sizeof(double));
	e->sprts = (t_cam*)malloc(sizeof(t_cam) * e->sp);
	e->sporder = (int*)malloc(sizeof(int) * e->sp);
	e->spdst = (double*)malloc(sizeof(double) * e->sp);
	while (++i < e->mapheight)
	{
		j = -1;
		while (++j < e->mapwidth)
		{
			if (e->world[i][j] == 2)
			{
				e->sprts[k].x = i + 0.5;
				e->sprts[k].y = j + 0.5;
				k++;
			}
		}
	}
}
