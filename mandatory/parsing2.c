/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 09:07:24 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 17:10:03 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

int			nbr_words(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

void		fill_texts(int id, char *str, t_elt *e)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) == -1)
		ft_error("some files won't open");
	close(fd);
	if ((e->text[id].i_ptr = mlx_png_file_to_image(e->m_ptr,
		str, &(e->text[id].a), &(e->text[id].b))) == NULL)
		ft_error("one of the pictures won't open !");
	e->text[id].i_data = (int*)mlx_get_data_addr(e->text[id].i_ptr,
		&(e->text[id].bpp), &(e->text[id].sizeline), &(e->text[id].endian));
	if (id == 0)
		e->test.d = 1;
	if (id == 1)
		e->test.c = 1;
	if (id == 2)
		e->test.b = 1;
	if (id == 3)
		e->test.a = 1;
}

void		verify_color(int a, int b, int c)
{
	if (a > 255 || b > 255 || c > 255 || a < 0 || b < 0 || c < 0)
		ft_error("color values should be between 0 - 255");
}

void		get_color(int id, char *str, t_elt *e)
{
	t_color	c;
	char	**colors;

	colors = ft_split(str, ',');
	if (nbr_words(colors) == 3)
	{
		c.red = ft_atoi(colors[0]);
		c.green = ft_atoi(colors[1]);
		c.blue = ft_atoi(colors[2]);
		verify_color(c.red, c.green, c.blue);
		if (id == 1)
		{
			e->floor_color = (c.red << 16) + (c.green << 8) + (c.blue);
			e->test.f = 1;
		}
		if (id == 2)
		{
			e->ceil_color = (c.red << 16) + (c.green << 8) + (c.blue);
			e->test.h = 1;
		}
	}
	else
		ft_error("only three main colors exist : RGB");
}

char		*get_string(char *str)
{
	int i;
	int size;
	int j;

	i = 0;
	size = ft_strlen(str);
	while (str[i] != '\0' && i < size - 1)
	{
		j = i;
		if (str[i] == ' ')
		{
			while (j < size - 1)
			{
				str[j] = str[j + 1];
				j++;
			}
			size -= 1;
		}
		i++;
	}
	str[i] = '\0';
	return (str);
}
