/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 12:25:52 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/18 09:56:37 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

//#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

#include "mlx.h"

#define WIDTH 1024
#define HEIGHT 720
#define mapWidth 24
#define mapHeight 24

typedef struct	s_move
{
	int		forward;
	int		backward;
	int		left;
	int		right;
	int		leftr;
	int		rightr;
}				t_move;

typedef struct	s_cam
{
	double	x;
	double	y;
}				t_cam;

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct	s_image
{
	void		*img_ptr;
	int			*img_data;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_image;

typedef struct	s_elt
{
	void		*mlx_ptr;
	void		*win;
	void		*img;
	void		*data;
	void		*img_ptr;
	int			*img_data;
	int			bpp;
	int			sizeline;
	int			endian;
	t_point		map;
	t_cam		sidedist;
	t_cam		deltadist;
	double 		perpwalldist;
	double		movespeed;
	double		rotspeed;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			color;
	t_point		step;
	t_cam		player;
	t_cam		plane;
	t_cam		dir;
	t_cam		camera;
	t_cam 		raydir;
	t_image		texture[4];
	t_image		sprite;
	t_move		move;
	t_cam		*sprts;
	double		*zbuffer;
	int			*sporder;
	double		*spdist;
	int			sp;
}				t_elt;


#endif