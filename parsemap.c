#include "raycaster.h"

int nbr_words(char **tab)
{
	int i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

static void	fill_textures(int id, char *str, t_elt *elt)
{
	//write(1, "hi\n", 3);
	int a = 64;
	int b = 64;
	elt->texture[id].img_ptr =  mlx_png_file_to_image ( elt->mlx_ptr, str, &a, &b);
	elt->texture[id].img_data = (int*)mlx_get_data_addr(elt->texture[id].img_ptr, &(elt->texture[id].bpp), &(elt->texture[id].sizeline), &(elt->texture[id].endian));
}

static void get_color(int id, char *str, t_elt *elt)
{
	char **colors = ft_split(str, ',');
	if (nbr_words(colors) == 3)
	{
		t_color c;
		c.red = ft_atoi(colors[0]);
		c.green = ft_atoi(colors[1]);
		c.blue = ft_atoi(colors[2]);
		if (id == 1)
			elt->floor_color = (c.red << 16) + (c.green << 8) + (c.blue);
		if (id == 2)
			elt->ceil_color = (c.red << 16) + (c.green << 8) + (c.blue);
	}
	else
		exit(0);
}

char *get_string(char *str)
{
	int i = 0;
	int size = ft_strlen(str);
	while (str[i] != '\0' && i < size - 1)
	{
		int j = i;
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
	return str;
}

void check_line(char *str, t_elt *elt)
{
	static int var = 0;
	int a = 64;
	int b = 64;
	size_t len = ft_strlen(str);
	if (len > 0)
	{
		char **tab = ft_split(str, ' ');
		int size = nbr_words(tab);
		//printf("%s,   %s,  %d\n", tab[0], tab[1], size);
		if (size == 3 && ft_strcmp(tab[0], "R") == 0)
		{
			if (var == 1)
				exit(0);
			int w = ft_atoi(tab[1]);
			int h = ft_atoi(tab[2]);
			elt->w = w > 1920 ? 1920 : w;
			elt->h = h > 1080 ? 1080 : h;
			elt->w = w < 100 ? 100 : w;
			elt->h = h < 100 ? 100 : h;
		}
		else if (size == 2)
		{
			if (var == 1)
				exit(0);
			if (ft_strcmp(tab[0], "NO") == 0)
				fill_textures(3, tab[1], elt);
			else if (ft_strcmp(tab[0], "SO") == 0)
				fill_textures(2, tab[1], elt);
			else if (ft_strcmp(tab[0], "WE") == 0)
				fill_textures(1, tab[1], elt);
			else if (ft_strcmp(tab[0], "EA") == 0)
				fill_textures(0, tab[1], elt);
			else if (ft_strcmp(tab[0], "S") == 0)
			{
				elt->sprite.img_ptr =  mlx_png_file_to_image (elt->mlx_ptr, tab[1], &a, &b);
				elt->sprite.img_data = (int*)mlx_get_data_addr(elt->sprite.img_ptr, &(elt->sprite.bpp), &(elt->sprite.sizeline), &(elt->sprite.endian));
			}
			else if (ft_strcmp(tab[0], "F") == 0)
				get_color(1, tab[1], elt);
			else if (ft_strcmp(tab[0], "C") == 0)
				get_color(2, tab[1], elt);
			//printf("%s\n", tab[1]);
		}
		else if (size >= 3)
		{
			if (var == 0)
				elt->mapwidth = size;
			var = 1;
			if (elt->mapwidth != size)
				exit(0);
			elt->worldmap = ft_strjoin(elt->worldmap, get_string(str));
		}
		else if (size == 0 && var == 1)
		{
			exit(0);
		}
	}
}

void read_map(char *str, t_elt *elt)
{
	int fd ;
	char *line;
	int x;
	if ((fd = open(str, O_RDONLY)) == -1)
		exit(0);
	while (1)
	{
		x = get_next_line(fd, &line);
		check_line(line, elt);
		if (x == 0)
			break;
	}
}

void	fill_direction(char c, t_elt *elt)
{ 
	if (c == 'S')
	{
		elt->dir.x = 1; 
		elt->dir.y = 0;
		elt->plane.x = 0;
		elt->plane.y = -0.66;
	}
	else if (c == 'N')
	{
		elt->dir.x = -1; 
		elt->dir.y = 0;
		elt->plane.x = 0;
		elt->plane.y = 0.66;
	}
	else if (c == 'W')
	{
		elt->dir.x = 0; 
		elt->dir.y = 1;
		elt->plane.x = 0.66;
		elt->plane.y = 0;
	}
	else if (c == 'E')
	{
		elt->dir.x = 0; 
		elt->dir.y = -1;
		elt->plane.x = -0.66;
		elt->plane.y = 0;
	}
}

void	make_map(t_elt *elt)
{
	elt->mapheight = ft_strlen(elt->worldmap)/elt->mapwidth;
	//printf("%s\n %d, %d, %zu\n", elt->worldmap, elt->mapheight, elt->mapwidth, ft_strlen(elt->worldmap));
	int k = 0;
	elt->world = (int**)malloc(sizeof(int*) * elt->mapheight);
	for(int i = 0; i < elt->mapheight; i++)
	{
		elt->world[i] = (int*)malloc(sizeof(int) * elt->mapwidth);
		for(int j = 0; j < elt->mapwidth; j++)
		{
			if (ft_isdigit(elt->worldmap[k]))
				elt->world[i][j] = elt->worldmap[k++] - '0';
			else
			{
				elt->world[i][j] = 0;
				elt->player.x = i;
				elt->player.y = j;
				fill_direction(elt->worldmap[k++], elt);
			}
			if (elt->worldmap[k] == '2')
				elt->sp++;
		}
	}
}

void	take_pos(t_elt *elt)
{
	elt->zbuffer = (double*)malloc(WIDTH*sizeof(double));
	elt->sprts = (t_cam*)malloc(sizeof(t_cam)*elt->sp);
	elt->sporder = (int*)malloc(sizeof(int)*elt->sp);
	elt->spdist = (double*)malloc(sizeof(double)*elt->sp);
	int k = 0;
	for(int i = 0; i < elt->mapheight; i++)
	{
		for(int j = 0; j < elt->mapwidth; j++)
		{
			if (elt->world[i][j] == 2)
			{
				elt->world[i][j] = 0;
				elt->sprts[k].x = i + 0.5;
				elt->sprts[k].y = j + 0.5;
				k++;
			}
		}
	}
}

/* int  main(int n, char **argv)
{
	if (n == 2)
	{
		t_elt elt;
		elt.sp = 0;
		elt.mlx_ptr = mlx_init();
		elt.worldmap = ft_strdup("");
		read_map(argv[1], &elt);
		make_map(&elt);
		take_pos(&elt);
		elt.win = mlx_new_window(elt.mlx_ptr, elt.w, elt.h, "cub3D");
		
		mlx_loop(elt.mlx_ptr);
	}
	return (0);
} */