/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 19:40:55 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 17:06:11 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void		fill_texts_helper2(t_elt *e, char **tab, int var)
{
	if (var == 1)
		ft_error("The map should be the last thing !");
	if (ft_strcmp(tab[0], "NO") == 0 && e->test.a == 0)
		fill_texts(3, tab[1], e);
	else if (ft_strcmp(tab[0], "SO") == 0 && e->test.b == 0)
		fill_texts(2, tab[1], e);
	else if (ft_strcmp(tab[0], "WE") == 0 && e->test.c == 0)
		fill_texts(1, tab[1], e);
	else if (ft_strcmp(tab[0], "EA") == 0 && e->test.d == 0)
		fill_texts(0, tab[1], e);
	else if (ft_strcmp(tab[0], "S") == 0 && e->test.e == 0)
	{
		check_file(tab[1]);
		e->test.e = 1;
		e->sprite.i_ptr = mlx_png_file_to_image(e->m_ptr, tab[1],
			&(e->sprite.a), &(e->sprite.b));
		e->sprite.i_data = (int*)mlx_get_data_addr(e->sprite.i_ptr,
			&(e->sprite.bpp), &(e->sprite.sizeline), &(e->sprite.endian));
	}
	else if (ft_strcmp(tab[0], "F") == 0 && e->test.f == 0)
		get_color(1, tab[1], e);
	else if (ft_strcmp(tab[0], "C") == 0 && e->test.h == 0)
		get_color(2, tab[1], e);
	else
		ft_error("Data is not CORRECT !");
}

void		fill_texts_helper1(t_elt *e, char **tab, int var)
{
	int w;
	int h;

	if (var == 1)
		ft_error("The map should be the last thing !");
	w = ft_atoi(tab[1]);
	h = ft_atoi(tab[2]);
	e->w = w > 1920 ? 1920 : w;
	e->h = h > 1080 ? 1080 : h;
	e->w = e->w < 100 ? 100 : e->w;
	e->h = e->h < 100 ? 100 : e->h;
}

void		get_map(char *str, t_elt *e, int *var, int size)
{
	if (*var == 0)
		e->mapwidth = size;
	*var = 1;
	if (e->mapwidth != size)
		ft_error("Map width is not correct !");
	e->worldmap = ft_strjoin(e->worldmap, get_string(str));
}

void		check_line(char *str, t_elt *e)
{
	static int	var = 0;
	size_t		len;
	char		**tab;
	int			size;

	len = ft_strlen(str);
	if (len > 0)
	{
		tab = ft_split(str, ' ');
		size = nbr_words(tab);
		if (size == 3 && ft_strcmp(tab[0], "R") == 0)
			fill_texts_helper1(e, tab, var);
		else if (size == 2)
		{
			fill_texts_helper2(e, tab, var);
			e->check++;
		}
		else if (size >= 3)
			get_map(str, e, &var, size);
		else
			ft_error("Something went wrong ... gotta check your file!");
	}
}

void		read_map(char *str, t_elt *e)
{
	int		fd;
	char	*line;
	int		x;

	check_ext(str);
	if ((fd = open(str, O_RDONLY)) == -1)
	{
		perror("Error\ncub3D");
		exit(0);
	}
	while (1)
	{
		x = get_next_line(fd, &line);
		check_line(line, e);
		if (x == 0)
			break ;
	}
	if (e->check != 7)
		ft_error("There should be four textures ! SORRY");
}
