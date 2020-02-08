/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:16:03 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 14:01:04 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

static t_bmp	init_bmph(t_elt *e)
{
	t_bmp		res;

	res.id[0] = 'B';
	res.id[1] = 'M';
	res.file_size = 54 + 4 * (int)e->w * (int)e->h;
	res.unused = 0;
	res.offset = 54;
	res.dib = 54 - 14;
	res.width = (int)e->w;
	res.height = -(int)e->h;
	res.plane[0] = 1;
	res.plane[1] = 0;
	res.bpp[0] = 32;
	res.bpp[1] = 0;
	res.compression = 0;
	res.raw_bitmap_size = 4 * (int)e->w * (int)e->h;
	res.resx = 0;
	res.resy = 0;
	res.number_of_colors = 0;
	res.important_colors = 0;
	return (res);
}

void			make_bmp(t_elt *e)
{
	t_bmp		img;
	int			file;

	file = open("./cub3D.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	img = init_bmph(e);
	write(file, &img, 54);
	write(file, e->i_data, img.raw_bitmap_size);
	close(file);
	exit(0);
}
