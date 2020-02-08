/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:45:09 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 15:05:13 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	memory_free(t_elt *elt)
{
	int i;

	i = 0;
	free(elt->spdst);
	free(elt->sporder);
	free(elt->sprts);
	while (i < elt->mapheight)
		free(elt->world[i++]);
	free(elt->world);
	free(elt->worldmap);
	free(elt->zbuffer);
}

int		close_win(void *param)
{
	memory_free((t_elt*)param);
	free((t_elt*)param);
	exit(0);
}

int		key_press(int keycode, void *param)
{
	t_elt *e;

	e = (t_elt*)(param);
	if (keycode == 13)
		e->move.forward = 1;
	if (keycode == 1)
		e->move.backward = 1;
	if (keycode == 0)
		e->move.left = 1;
	if (keycode == 2)
		e->move.right = 1;
	if (keycode == 124)
		e->move.leftr = 1;
	if (keycode == 123)
		e->move.rightr = 1;
	if (keycode == 257)
		e->movespd = 0.1;
	if (keycode == 53)
		close_win(e);
	return (0);
}

int		key_release(int keycode, void *param)
{
	t_elt *e;

	e = (t_elt*)(param);
	if (keycode == 13)
		e->move.forward = 0;
	if (keycode == 1)
		e->move.backward = 0;
	if (keycode == 0)
		e->move.left = 0;
	if (keycode == 2)
		e->move.right = 0;
	if (keycode == 124)
		e->move.leftr = 0;
	if (keycode == 123)
		e->move.rightr = 0;
	if (keycode == 257)
		e->movespd = 0.07;
	return (0);
}
