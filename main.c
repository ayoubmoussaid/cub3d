#include "raycaster.h"

void draw_circle(int x,int y, int radius, int color)
{
    int i,j;
	int x_c = x - radius;
	int y_c = y - radius;
    for (i=0; i<=2*radius; i++)
    {
        for (j=0; j<=2*radius; j++)
        {
            double distance = sqrt((double)(i-radius)*(i-radius) + (j-radius)*(j-radius)) + 0.5;
            if (distance <= radius)
            {
                mlx_pixel_put(mlx_ptr, window, x_c + i, y_c + j, color);
            }
        }
    }
}



void swap(int *x, int *y)
{
	int z;

	z = *x;
	*x = *y;
	*y = z;
}

void draw_line(int x0,int y0,int x1, int y1, int color)
{
	int steep = 0; 
    if (abs(x0 - x1) < abs(y0 - y1)) { 
        swap(&x0, &y0); 
        swap(&x1, &y1); 
        steep = 1; 
    } 
    if (x0 > x1) { 
        swap(&x0, &x1); 
        swap(&y0, &y1); 
    } 
    int dx = x1 - x0; 
    int dy = y1 - y0; 
    float derror = fabs(dy / (float)dx); 
    float error = 0; 
    int y = y0; 
    for (int x = x0; x <= x1; x++) { 
        if (steep) { 
            mlx_pixel_put(mlx_ptr, window, x, y, color);
        } else { 
            mlx_pixel_put(mlx_ptr, window, y, x, color);
        } 
        error += derror; 
        if (error>0.5) { 
            y += (y1 > y0 ? 1 : -1); 
            error -= 1.0; 
        }
    }
}

void	draw_rect(int x,int y, double len,double lar, int color)
{
	int i = 1;
	int j = 0;
	while ( i < (int)len)
	{
		j = 1;
		while (j < (int)lar)
		{
			mlx_pixel_put(mlx_ptr, window, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

t_block **make_map()
{
	char *smap[mapW] ={ "111111111111111111111111111111",
						"100000000011000000000000000001",
						"101100000111000000200000100001",
						"100100000000000000000000100001",
						"101100000111000000000000100001",
						"100000000011000001110111100001",
						"111101111111110111000000100001",
						"111101111111110111010100100001",
						"110000001101010111000000100001",
						"100020000000000011000000100001",
						"100000000000000011010100100001",
						"11000000110101011111011110N001",
						"111101111111010111110111100001",
						"100000000011000000000000000001",
						"111111111111111111111111111111"};
	int n_color = 0xFFFFFF;
	int b_color = 0x6e9eec;

	t_block **map;
	int i = 0, j = 0, k = 0;

	map = (t_block**)malloc(sizeof(t_block*)*mapH);
	while (i < mapH)
		map[i++] = (t_block*)malloc(sizeof(t_block)*mapW);

	i = 0;
	j = 0; 

	while (j < mapH)
	{
		i = 0;
		while(i < mapW)
		{
			if (smap[j][i] == '1')
			{
				map[j][i].type = 1;
				map[j][i].color = b_color;
			}
			else
			{
				map[j][i].type = 0;
				map[j][i].color = n_color;
			}
			map[j][i].pos_x = i*WIDTH/mapW ;
			map[j][i].pos_y = j*HEIGHT/mapH ;
			i++;
		}
		j++;
	}
	return map;
}

void draw_map(t_block **map)
{
	int i = 0, j = 0;

	while (j < mapH)
	{
		i = 0;
		while(i < mapW)
		{
			draw_rect(map[j][i].pos_x, map[j][i].pos_y, WIDTH/mapW, HEIGHT/mapH, map[j][i].color);
			i++;
		}
		j++;
	}
}

int move_it(int x, int y, void *param)
{
	static int more;

	more += 2;
	mlx_clear_window(mlx_ptr, window);
	draw_circle(x, y, HEIGHT/mapH/4 + more, 0xfcba03);
	return 0;
}


int close(void *param)
{
	(void)param;
	exit(0);
}

int main()
{
	
	t_elt elt;

	elt.mlx_ptr = mlx_init();
	elt.win= mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "cub3D");
	
	//t_block **map = make_map();
	//draw_map(map);
	draw_circle(50, 50, HEIGHT/mapH/4, 0xfcba03);
	mlx_hook(window, 6, 0, move_it, NULL);
	mlx_hook(window, 17, 0, close, NULL);
	mlx_loop(mlx_ptr);
}


	
	
	//draw_rect(0, 0, 40, 40, 0x6e9eec);
	//draw_line(10,10,1000,200,0x6e9eec);

/* void draw_image_circle(int x,int y, int radius, int color)
{
    int i, j;
	int     bpp;
	int     size_line;
	int     endian;

	img_ptr = mlx_new_image(mlx_ptr, radius*2, radius*2);
	img_data =  mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
    for (i=0; i<=2*radius; i++)
    {
        for (j=0; j<=2*radius; j++)
        {
            double distance = sqrt((double)(i - radius) * (i - radius) + (j - radius) * (j - radius)) + 0.5;
            if (distance <= radius)
            {
                //mlx_pixel_put(mlx_ptr, window, x_c + i, y_c + j, color);
				img_data[j * radius + i] = color;
            }
        }
    }
	mlx_put_image_to_window(mlx_ptr, window, img_ptr, x - radius, y - radius);
} */