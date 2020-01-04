/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 12:25:52 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/04 19:09:45 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1080
#define mapW 30
#define mapH 15

typedef struct	s_block
{
	int type;
	double pos_x;
	double pos_y;
	int color;
}				t_block;

typedef struct	s_player
{
	char looks;
	double pos_x;
	double pos_y;
}				t_player;

typedef struct	s_elt
{
	void	*mlx_ptr;
	void	*win;
	void	*img;
	void	*data;
}				t_elt;

void *mlx_ptr;
void *window;

#endif