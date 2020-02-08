/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:53:19 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 16:59:49 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	draw_map(t_elt *e)
{
	int x;

	x = -1;
	while (++x < e->w)
	{
		e->camera.x = 2 * x / (double)e->w - 1;
		e->raydir.x = e->dir.x + e->plan.x * e->camera.x;
		e->raydir.y = e->dir.y + e->plan.y * e->camera.x;
		e->map.x = (int)e->plyr.x;
		e->map.y = (int)e->plyr.y;
		e->deltadist.x = fabs(1 / e->raydir.x);
		e->deltadist.y = fabs(1 / e->raydir.y);
		e->hit = 0;
		count_sidedist(e);
		find_hit(e);
		calc_start_end(e);
		e->color = e->ceil_color;
		verline(x, 0, e->drawstart, e);
		draw_texts(e, x);
		e->color = e->floor_color;
		verline(x, e->drawend, e->h - 1, e);
		e->zbuffer[x] = e->perpwalldist;
	}
	draw_sprites(e);
}

void	initialize_e(t_elt *e, int bmp)
{
	if (bmp == 0)
		e->win = mlx_new_window(e->m_ptr, e->w, e->h, "cub3D");
	e->i_ptr = mlx_new_image(e->m_ptr, e->w, e->h);
	e->i_data = (int*)mlx_get_data_addr(e->i_ptr,
		&(e->bpp), &(e->sizeline), &(e->endian));
	e->move.forward = 0;
	e->move.backward = 0;
	e->move.left = 0;
	e->move.right = 0;
	e->move.leftr = 0;
	e->move.rightr = 0;
	e->movespd = 0.1;
	e->rotspd = 0.04;
	e->check = 0;
	e->test.a = 0;
	e->test.b = 0;
	e->test.c = 0;
	e->test.d = 0;
	e->test.e = 0;
	e->test.f = 0;
	e->test.h = 0;
}

void	start_game(t_elt *e, char *str, int bmp)
{
	e->worldmap = ft_strdup("");
	e->m_ptr = mlx_init();
	read_map(str, e);
	make_map(e, 0);
	check_map(e, 0, 0);
	take_pos(e);
	initialize_e(e, bmp);
	draw_map(e);
	if (bmp == 1)
		make_bmp(e);
	mlx_loop_hook(e->m_ptr, walk_arround, e);
	mlx_hook(e->win, 2, 0, key_press, e);
	mlx_hook(e->win, 3, 0, key_release, e);
	mlx_hook(e->win, 17, 0, close_win, e);
	mlx_loop(e->m_ptr);
}

void	check_ext(char *str)
{
	int len;

	if ((len = ft_strlen(str)) < 5)
		ft_error("invalid file");
	if (str[len - 1] != 'b' || str[len - 2] != 'u' || str[len - 3] != 'c')
		ft_error("invalid extension");
}

int		main(int n, char **argv)
{
	t_elt *e;

	if (n == 2)
	{
		e = (t_elt*)malloc(sizeof(t_elt));
		start_game(e, argv[1], 0);
	}
	else if (n == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		e = (t_elt*)malloc(sizeof(t_elt));
		start_game(e, argv[1], 1);
	}
	else
		ft_putendl_fd("Usage:\t./cub3d {map}", 1);
	return (0);
}
