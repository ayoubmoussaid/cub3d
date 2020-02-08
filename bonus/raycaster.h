/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 12:25:52 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 17:57:21 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

# include "SDL.h"
# include "SDL_mixer.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

typedef struct	s_move
{
	int		forward;
	int		backward;
	int		left;
	int		right;
	int		leftr;
	int		rightr;
}				t_move;

typedef	struct	s_color
{
	int red;
	int green;
	int blue;
}				t_color;

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
	void	*i_ptr;
	int		*i_data;
	int		bpp;
	int		endian;
	int		sizeline;
	int		a;
	int		b;
}				t_image;

typedef struct	s_txtr
{
	int		tex_num;
	double	wallx;
	int		tx;
	int		ty;
	double	step;
	double	texpos;
	int		i;
}				t_txtr;

typedef struct	s_sprite
{
	double	spx;
	double	spy;
	double	det;
	double	trx;
	double	try;
	int		spritescreenx;
	int		spriteh;
	int		spritew;
	int		drawstartx;
	int		drawstarty;
	int		drawendx;
	int		drawendy;
}				t_sprite;

typedef struct	s_ver
{
	int		a;
	int		b;
	int		c;
	int		d;
	int		e;
	int		f;
	int		h;
}				t_ver;

typedef struct	s_elt
{
	int			w;
	int			h;
	void		*m_ptr;
	void		*win;
	void		*img;
	void		*data;
	void		*i_ptr;
	int			*i_data;
	int			bpp;
	int			sizeline;
	int			endian;
	t_point		map;
	t_cam		sidedist;
	t_cam		deltadist;
	double		perpwalldist;
	double		movespd;
	double		rotspd;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			color;
	t_point		step;
	t_cam		plyr;
	t_cam		plan;
	t_cam		dir;
	t_cam		camera;
	t_cam		raydir;
	t_image		text[4];
	t_image		sprite;
	t_move		move;
	t_cam		*sprts;
	double		*zbuffer;
	int			*sporder;
	double		*spdst;
	int			sp;
	int			ceil_color;
	int			floor_color;
	char		*worldmap;
	int			mapwidth;
	int			mapheight;
	int			**world;
	int			mouse;
	t_txtr		v;
	t_sprite	s;
	Mix_Chunk	*wallhit;
	int			check;
	t_ver		test;
	int			health;
}				t_elt;

void			take_pos(t_elt *e);
void			make_map(t_elt *e, int k);
void			read_map(char *str, t_elt *e);
void			check_map(t_elt *e, int i, int j);
int				nbr_words(char **tab);
void			fill_texts(int id, char *str, t_elt *e);
void			verify_color(int a, int b, int c);
void			get_color(int id, char *str, t_elt *e);
char			*get_string(char *str);
void			fill_texts_helper2(t_elt *e, char **tab, int var);
void			fill_texts_helper1(t_elt *e, char **tab, int var);
void			get_map(char *str, t_elt *e, int var, int size);
void			check_line(char *str, t_elt *e);
int				walk_arround(void *param);
void			rot_left_right(t_elt *e);
void			left_right(t_elt *e);
void			for_back(t_elt *e);
int				key_release(int keycode, void *param);
int				key_press(int keycode, void *param);
int				close_win(void *param);
void			sort(t_elt *e);
void			count_sidedist(t_elt *e);
void			find_hit(t_elt *e);
void			calc_start_end(t_elt *e);
void			calc_sprite_dim(t_elt *e, int i);
void			verline(int x, int y0, int y1, t_elt *e);
void			draw_texts_mapping(t_elt *e, int x);
void			draw_texts(t_elt *e, int x);
void			draw_sprite_on_screen(t_elt *e, int d);
void			draw_sprites(t_elt *e);
void			draw_map(t_elt *e);
void			initialize_e(t_elt *e, int bmp);
void			start_game(t_elt *e, char *str, int bmp);
void			make_bmp(t_elt *e);
void			check_mouse(t_elt *elt);
void			check_wall(t_elt *elt);
void			play_sound(t_elt *elt);
void			ft_error(char *str);
void			check_ext(char *str);
void			check_file(char *str);
void			health_bar(t_elt *e);
void			game_over(t_elt *e);

#endif
