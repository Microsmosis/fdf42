/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:33:58 by llonnrot          #+#    #+#             */
/*   Updated: 2022/01/27 16:22:25 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include "mlx.h"
#include "get_next_line.h"

typedef struct s_rnc
{
	int	rows;
	int	columns;
}				t_rnc;

typedef struct s_init_p
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_inits;

/* void	draw_end_line(void *mlx, void *win, int x, int y, int pos)
{
	int	y_temp;
	int	offset1;
	int	offset2;
	
	y *= pos;
	x *= pos;
	y_temp = y;
	//offset1 = 400;
	//offset2 = 365;
	while (y > pos)
	{
		draw_line(mlx, win, x + offset1, y + offset1, x + offset1, y + offset2, 0xFFFFFF);
		y -= pos;
	}
	while (x > pos)
	{
		draw_line(mlx, win, x + offset1, y_temp + offset1, x + offset2, y_temp + offset1, 0xFFFFFF);
		x -= pos;
	}
} */

int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX = endX - beginX;
	double	deltaY = endY - beginY;

	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels;
	deltaY /= pixels;

	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (1);
}

int		func(int keycode, t_inits *ptrs)
{
	if (keycode == 53)
		exit (0);
	if (keycode == 49)
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
	return (0);
}

t_rnc	row_count(int fd)
{
	t_rnc	value;
	char	*line;

	value.rows = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (value.rows == 0)
			value.columns = ft_strlen(line);
		value.rows++;
		free (line);
	}
	value.columns = value.columns - (value.columns / 2);
	close (fd);
	return (value);
}

static char	***ft_read(const int fd, const int fd2)
{
	char	***map;
	char	*line;
	int		i;
	int		j;
	t_rnc	value;
	
	i = 0;
	j = 0;
	value = row_count(fd);
	map = (char ***)malloc(sizeof(char **) * value.rows + 1);
	while (i < value.rows)
	{
		map[i] = (char **)malloc(sizeof(char *) * value.columns + 1);
		i++;
	}
	map[i] = NULL;
	i = 0;
	while (i < value.rows)
	{
		while (j < value.columns)
		{
			map[i][j] = ft_strnew(3);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	while (get_next_line(fd2, &line) == 1)
	{
		map[i] = ft_strsplit(line, ' ');
		i++;
		free (line);
	}
	return (map);
}

void	draw_corner(void *mlx, void *win, int x, int y, int tile_size)
{
	//int	offset;

	x++;
	y++;
	x *= tile_size;
	y *= tile_size;
	//offset = 400;
	draw_line(mlx, win, x, y, x + tile_size, y, 0xFFFFFF);
	draw_line(mlx, win, x, y, x, y + tile_size, 0xFFFFFF);
}

void	draw_end_line(void *mlx, void *win, int x, int y, int tile_size)
{
	int	y_temp;
	//int	offset;
	
	y *= tile_size;
	x *= tile_size;
	y_temp = y;
	//offset = 400;
	while (y > tile_size)
	{
		draw_line(mlx, win, x, y, x, y - tile_size, 0xFFFFFF);
		y -= tile_size;
	}
	while (x > tile_size)
	{
		draw_line(mlx, win, x, y_temp, x - tile_size, y_temp, 0xFFFFFF);
		x -= tile_size;
	}
}

void	draw_map(void *mlx, void *win, char ***map)
{
	int	y;
	int	x;
	int x2;
	
	y = 0;
	x = 0;
	x2 = 0;
	while (map[y] != '\0')
	{
		while (map[y][x] != '\0')
		{
			draw_corner(mlx, win, x, y, 35);
			x++;
		}
		x2 = x;
		x = 0;
		y++;
	}
	draw_end_line(mlx, win, ++x2, ++y, 35);
}

int	main(int argc, char **argv)
{
	
	t_inits ptrs;
	int		fd;
	int		fd2;
	char	***map;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		fd2 = open(argv[1], O_RDONLY);
	}
	else
	{
		ft_putstr("	usage :		./a.out <filename.>\n");
		return (1);
	}
	map = ft_read(fd, fd2);
	close (fd);
	close (fd2);
	if (map == NULL)
	{
		printf("error\n");
		return (1);
	}
	ptrs.mlx_ptr = mlx_init();
	ptrs.win_ptr = mlx_new_window(ptrs.mlx_ptr, 1720, 1240, "mlx hive");
	draw_map(ptrs.mlx_ptr, ptrs.win_ptr, map);
	mlx_key_hook(ptrs.win_ptr, &func, &ptrs);
	mlx_loop(ptrs.mlx_ptr);
	return (0);
}
