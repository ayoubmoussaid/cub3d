#include "raycaster.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
  {1,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,0,0,1},
  {1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	sort(t_elt *elt)
{
	int i ;
	int x;
	double k;
	int sorted = 0;
	while (!sorted)
	{
		i = -1;
		sorted = 1;
		while (++i < elt->sp - 1)
		{
			if (elt->spdist[i] < elt->spdist[i+1])
			{
				k = elt->spdist[i];
				elt->spdist[i] = elt->spdist[i+1];
				elt->spdist[i+1] = k;

				x = elt->sporder[i];
				elt->sporder[i] = elt->sporder[i+1];
				elt->sporder[i+1] = x;
				sorted = 0;
			}
		}
	}
}

void verline(int x,int y0,int y1, t_elt *elt)
{
	int i = y0;
    while ( i <= y1) 
	{ 
        elt->img_data[x + WIDTH*i] = elt->color;
		i++;
    }
}

int close_win(void *param)
{
	free((t_elt*)param);
	exit(0);
}

void	draw_map(t_elt *elt)
{
	int x = -1;
	while (++x < WIDTH)
	{
		elt->camera.x = 2 * x / (double)WIDTH - 1;
		elt->raydir.x = elt->dir.x + elt->plane.x * elt->camera.x;
		elt->raydir.y = elt->dir.y + elt->plane.y * elt->camera.x;

		elt->map.x = (int)elt->player.x;
		elt->map.y = (int)elt->player.y;

		elt->deltadist.x = fabs(1 / elt->raydir.x);
		elt->deltadist.y = fabs(1 / elt->raydir.y);

		elt->hit = 0;

		if (elt->raydir.x < 0)
		{
			elt->step.x = -1;
			elt->sidedist.x = (elt->player.x - elt->map.x) * elt->deltadist.x;
		}
		else
		{
			elt->step.x = 1;
			elt->sidedist.x = (elt->map.x + 1.0 - elt->player.x) * elt->deltadist.x;
		}
		if (elt->raydir.y < 0)
		{
			elt->step.y = -1;
			elt->sidedist.y = (elt->player.y - elt->map.y) * elt->deltadist.y;
		}
		else
		{
			elt->step.y = 1;
			elt->sidedist.y = (elt->map.y + 1.0 - elt->player.y) * elt->deltadist.y;
		}
		while (elt->hit == 0)
		{
			if (elt->sidedist.x < elt->sidedist.y)
			{
				elt->sidedist.x += elt->deltadist.x;
				elt->map.x += elt->step.x;
				elt->side = 0;
			}
			else
			{
				elt->sidedist.y += elt->deltadist.y;
				elt->map.y += elt->step.y;
				elt->side = 1;
			}
			if (worldMap[elt->map.x][elt->map.y] > 0) elt->hit = 1;
		}

		if (elt->side == 0)
			elt->perpwalldist = (elt->map.x - elt->player.x + (1 - elt->step.x) / 2) / elt->raydir.x;
		else
			elt->perpwalldist = (elt->map.y - elt->player.y + (1 - elt->step.y) / 2) / elt->raydir.y;
		
		elt->lineheight = (int)(HEIGHT / elt->perpwalldist);

		elt->drawstart = -elt->lineheight / 2 + HEIGHT / 2;
		if (elt->drawstart < 0)
			elt->drawstart = 0;
		elt->drawend = elt->lineheight / 2 + HEIGHT / 2;
		if (elt->drawend >= HEIGHT)
			elt->drawend = HEIGHT - 1;


		//draw sky
		elt->color = 0x00c8fa;
		verline(x, 0, elt->drawstart, elt);

		//draw walls with textures
		if (worldMap[elt->map.x][elt->map.y] == 1)
			elt->color = 0xfcba03;

		//not mine , trying to understand 
		int texNum = worldMap[elt->map.x][elt->map.y] - 1;

		double wallx;
		if (elt->side == 0) wallx = elt->player.y + elt->perpwalldist * elt->raydir.y;
		else				wallx = elt->player.x + elt->perpwalldist * elt->raydir.x;

		wallx -= floor(wallx);

		int texx = (int)(wallx * (double)64);
		if (elt->side == 0 && elt->raydir.x > 0) texx = 64 - texx - 1;
		if (elt->side == 1 && elt->raydir.y < 0) texx = 64 - texx - 1;

		double step = 1.0 * 64/elt->lineheight;

		double texpos = (elt->drawstart - HEIGHT/2 + elt->lineheight / 2) * step;

		for (int i = elt->drawstart; i <= elt->drawend; i++) {
			int texy = (int)texpos & (64 - 1);
			texpos += step;
        	
			if (elt->side == 1 && elt->raydir.y < 0)
				elt->img_data[x + WIDTH*i] = elt->texture[0].img_data[64*texy + texx];
			if (elt->side == 1 && elt->raydir.y > 0)
				elt->img_data[x + WIDTH*i] = elt->texture[1].img_data[64*texy + texx];
			if (elt->side == 0 && elt->raydir.x > 0)
				elt->img_data[x + WIDTH*i] = elt->texture[2].img_data[64*texy + texx];
			if (elt->side == 0 && elt->raydir.x < 0)
				elt->img_data[x + WIDTH*i] = elt->texture[3].img_data[64*texy + texx];
    	}
		
		//draw ground
		elt->color = 0x525b6b;
		verline(x, elt->drawend, HEIGHT - 1, elt);
		
		elt->zbuffer[x] = elt->perpwalldist;
	}

	int i = -1;
	while (++i < elt->sp)
	{
		elt->sporder[i] = i;
		elt->spdist[i] = (elt->player.x - elt->sprts[i].x)*(elt->player.x - elt->sprts[i].x) +
						(elt->player.y - elt->sprts[i].y)*(elt->player.y - elt->sprts[i].y);
	}
	sort(elt);
	i = -1;
	while (++i < elt->sp)
	{
		double spritex = elt->sprts[elt->sporder[i]].x - elt->player.x;
		double spritey = elt->sprts[elt->sporder[i]].y - elt->player.y;

		double det = 1.0 / (elt->plane.x * elt->dir.y - elt->dir.x * elt->plane.y);

		double trx = det * (elt->dir.y * spritex - elt->dir.x * spritey);
		double try = det * (-elt->plane.y * spritex + elt->plane.x * spritey);

		int spritescreenx = (int)((WIDTH / 2) * (1 + trx/try));

		//height of the sprite
		int spriteh = abs((int)(HEIGHT/try));

		int drawstarty = -spriteh / 2 + HEIGHT / 2;
		if (drawstarty < 0) 
			drawstarty = 0;
	
		int drawendy = spriteh / 2 + HEIGHT / 2;
		if (drawendy >= HEIGHT)
			drawendy = HEIGHT - 1;

		//width of the sprite
		int spritew = abs((int)(HEIGHT/try));

		int drawstartx = -spritew / 2 + spritescreenx;
		if (drawstartx < 0) 
			drawstartx = 0;
	
		int drawendx = spritew / 2 + spritescreenx;
		if (drawendx >= WIDTH)
			drawendx = WIDTH - 1;

		int x = drawstartx - 1;

		while (++x < drawendx)
		{
			int texx = (int)(256 * (x - (-spritew / 2 + spritescreenx)) * 64 / spritew) / 256;
			if (try > 0 && x > 0 && x < WIDTH && try < elt->zbuffer[x])
			{
				int y = drawstarty - 1;
				while (++y < drawendy)
				{
					int d = y * 256 - HEIGHT * 128 + spriteh * 128;
					int texy = ((d * 64) / spriteh) / 256;
					int color = elt->sprite.img_data[64 * texy + texx];
					if (color != 0x0000000)
						elt->img_data[x + WIDTH*y] = color;
				}
			}
		}
	}
}

int	key_press(int keycode, void *param)
{
	t_elt *elt = (t_elt*)(param);

	if(keycode == 13)
		elt->move.forward = 1;
	if (keycode == 1)
		elt->move.backward= 1;
	if(keycode == 0)
		elt->move.left = 1;
	if(keycode == 2)
		elt->move.right = 1;
	if (keycode == 124)
		elt->move.leftr = 1;
	if (keycode == 123)
		elt->move.rightr = 1;

	if (keycode == 53)
		close_win(elt);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_elt *elt = (t_elt*)(param);

	if(keycode == 13)
		elt->move.forward = 0;
	if (keycode == 1)
		elt->move.backward= 0;
	if(keycode == 0)
		elt->move.left = 0;
	if (keycode == 2)
		elt->move.right = 0;
	if (keycode == 124)
		elt->move.leftr = 0;
	if (keycode == 123)
		elt->move.rightr = 0;
	return (0);
}



int		walk_arround(void *param)
{
	t_elt *elt = (t_elt*)param;
	if(elt->move.forward == 1)
	{
		if (worldMap[(int)(elt->player.x + elt->dir.x * elt->movespeed)][(int)elt->player.y] == 0)
			elt->player.x += elt->dir.x * (elt->movespeed - 0.01);
		if (worldMap[(int)elt->player.x][(int)(elt->player.y + elt->dir.y * elt->movespeed)] == 0)
			elt->player.y += elt->dir.y * (elt->movespeed - 0.01);
	}
	if (elt->move.backward == 1)
	{
		if (worldMap[(int)(elt->player.x - elt->dir.x * elt->movespeed)][(int)elt->player.y] == 0)
			elt->player.x -= elt->dir.x * (elt->movespeed - 0.01);
		if (worldMap[(int)elt->player.x][(int)(elt->player.y - elt->dir.y * elt->movespeed)] == 0)
			elt->player.y -= elt->dir.y * (elt->movespeed - 0.01);
	}

	if(elt->move.left== 1)
	{
		if (worldMap[(int)(elt->player.x - elt->dir.y * elt->movespeed)][(int)elt->player.y] == 0)
			elt->player.x -= elt->dir.y * (elt->movespeed - 0.01);
		if (worldMap[(int)elt->player.x][(int)(elt->player.y + elt->dir.x * elt->movespeed)] == 0)
			elt->player.y += elt->dir.x * (elt->movespeed - 0.01);
	}

	if(elt->move.right == 1)
	{
		if (worldMap[(int)(elt->player.x + elt->dir.y * elt->movespeed)][(int)elt->player.y] == 0)
			elt->player.x += elt->dir.y * elt->movespeed;
		if (worldMap[(int)elt->player.x][(int)(elt->player.y - elt->dir.x * elt->movespeed)] == 0)
			elt->player.y -= elt->dir.x * elt->movespeed;
	}
	
	if (elt->move.leftr == 1)
	{
		double olddirx = elt->dir.x;
		elt->dir.x = elt->dir.x * cos(-elt->rotspeed) - elt->dir.y * sin(-elt->rotspeed);
		elt->dir.y = olddirx * sin(-elt->rotspeed) + elt->dir.y * cos (-elt->rotspeed);
		double oldplanex = elt->plane.x;
		elt->plane.x = elt->plane.x * cos(-elt->rotspeed) - elt->plane.y * sin(-elt->rotspeed);
		elt->plane.y = oldplanex * sin(-elt->rotspeed) + elt->plane.y * cos (-elt->rotspeed);
	}
	if (elt->move.rightr == 1)
	{
		double olddirx = elt->dir.x;
		elt->dir.x = elt->dir.x * cos(elt->rotspeed) - elt->dir.y * sin(elt->rotspeed);
		elt->dir.y = olddirx * sin(elt->rotspeed) + elt->dir.y * cos (elt->rotspeed);
		double oldplanex = elt->plane.x;
		elt->plane.x = elt->plane.x * cos(elt->rotspeed) - elt->plane.y * sin(elt->rotspeed);
		elt->plane.y = oldplanex * sin(elt->rotspeed) + elt->plane.y * cos(elt->rotspeed);
	}

	//printf("%d  %d   %lf   %lf    %lf   %lf\n",(int)elt->player.x, (int)elt->player.y, elt->dir.x, elt->dir.y, elt->plane.x, elt->plane.y);
	
	
	mlx_destroy_image(elt->mlx_ptr, elt->img_ptr);
	mlx_clear_window(elt->mlx_ptr, elt->win);
	elt->img_ptr = mlx_new_image(elt->mlx_ptr, WIDTH, HEIGHT); 
	elt->img_data = (int*)mlx_get_data_addr(elt->img_ptr, &(elt->bpp), &(elt->sizeline), &(elt->endian));
	draw_map(elt);
	mlx_put_image_to_window(elt->mlx_ptr, elt->win, elt->img_ptr, 0, 0);
	return (0);
}

int main()
{

	t_elt *elt = (t_elt*)malloc(sizeof(t_elt));
	elt->mlx_ptr = mlx_init();
	elt->win= mlx_new_window(elt->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	int a = 64, b = 64;
	elt->img_ptr = mlx_new_image(elt->mlx_ptr, WIDTH, HEIGHT); 
	elt->img_data = (int*)mlx_get_data_addr(elt->img_ptr, &(elt->bpp), &(elt->sizeline), &(elt->endian));
	
	elt->texture[0].img_ptr =  mlx_png_file_to_image ( elt->mlx_ptr, "./pics/greystone.png", &a, &b);
	elt->texture[0].img_data = (int*)mlx_get_data_addr(elt->texture[0].img_ptr, &(elt->texture[0].bpp), &(elt->texture[0].sizeline), &(elt->texture[0].endian));

	elt->texture[1].img_ptr =  mlx_png_file_to_image ( elt->mlx_ptr, "./pics/purplestone.png", &a, &b);
	elt->texture[1].img_data = (int*)mlx_get_data_addr(elt->texture[1].img_ptr, &(elt->texture[1].bpp), &(elt->texture[1].sizeline), &(elt->texture[1].endian));
	
	elt->texture[2].img_ptr =  mlx_png_file_to_image ( elt->mlx_ptr, "./pics/bluestone.png", &a, &b);
	elt->texture[2].img_data = (int*)mlx_get_data_addr(elt->texture[2].img_ptr, &(elt->texture[2].bpp), &(elt->texture[2].sizeline), &(elt->texture[2].endian));

	elt->texture[3].img_ptr =  mlx_png_file_to_image ( elt->mlx_ptr, "./pics/colorstone.png", &a, &b);
	elt->texture[3].img_data = (int*)mlx_get_data_addr(elt->texture[3].img_ptr, &(elt->texture[3].bpp), &(elt->texture[3].sizeline), &(elt->texture[3].endian));

	elt->sprite.img_ptr =  mlx_png_file_to_image ( elt->mlx_ptr, "./pics/barrel.png", &a, &b);
	elt->sprite.img_data = (int*)mlx_get_data_addr(elt->sprite.img_ptr, &(elt->sprite.bpp), &(elt->sprite.sizeline), &(elt->sprite.endian));

	elt->player.x = 18;
	elt->player.y = 12; 
	elt->dir.x = 0; 
	elt->dir.y = -1;
	elt->plane.x = -0.66;
	elt->plane.y = 0;
	

	elt->move.forward = 0;
	elt->move.backward= 0;
	elt->move.left = 0;
	elt->move.right = 0;
	elt->move.leftr = 0;
	elt->move.rightr = 0;

	elt->movespeed = 0.1;
	elt->rotspeed = 0.04;


	elt->sp = 2;
	elt->zbuffer = (double*)malloc(WIDTH*sizeof(double));
	elt->sprts = (t_cam*)malloc(sizeof(t_cam)*elt->sp);
	elt->sporder = (int*)malloc(sizeof(int)*elt->sp);
	elt->spdist = (double*)malloc(sizeof(double)*elt->sp);


	elt->sprts[0].x = 17;
	elt->sprts[0].y = 14;

	elt->sprts[1].x = 18;
	elt->sprts[1].y = 15; 

	draw_map(elt);

	//mlx_put_image_to_window(elt->mlx_ptr, elt->win, elt->img_ptr, 0, 0);

	mlx_loop_hook(elt->mlx_ptr, walk_arround, elt);
	mlx_hook(elt->win, 2, 0, key_press, elt);
	mlx_hook(elt->win, 3, 0, key_release, elt);
	mlx_hook(elt->win, 17, 0, close_win, elt);
	mlx_loop(elt->mlx_ptr);

	return (0);
}
