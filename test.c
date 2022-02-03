/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:33:58 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/03 21:14:11 by llonnrot         ###   ########.fr       */
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

typedef struct s_ints
{
	int	x;
	int	x_temp;
	int	y;
	int	endX;
	int	endY;
	int	beginZ;
	int	endZx;
	int	endZy;
	int	height;
	int	width;
	int	projection;
}				t_ints;

typedef struct s_doubles
{
	double	deltaX;
	double	deltaY;
	double	deltaZ;
	double	pixelX;
	double	pixelY;
	double	pixelZ;
	double	iso_x;
	double	iso_y;
	int		pixels;
}				t_dbls;

int	func(int keycode, t_inits *ptrs)
{
	if (keycode == 53)
		exit (0);
	if (keycode == 49)
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
	return (0);
}

int	space_count(char *line, int i, int count)
{
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			count++;
		i++;
	}
	if (line[i - 1] == ' ')
		exit (1); // again check memoryleaks etc with this exit ....... 
	return (count);
}

t_rnc	row_count(int fd)
{
	t_rnc	value;
	char	*line;
	int		spaces;

	value.rows = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (value.rows == 0)
		{
			value.columns = ft_strlen(line);
			spaces = space_count(line, 0, 0);
		}
		if (space_count(line, 0, 0) != spaces)
			exit (1);
		value.rows++;
		free (line);
	}
	value.columns = value.columns - (value.columns / 2);
	close (fd);
	return (value);
}

char	***malloc_grid(t_rnc value, int i, int j)
{
	char	***map;

	map = (char ***)malloc(sizeof(char **) * value.rows);
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
			map[i][j] = ft_strnew(2);
			j++;
		}
		j = 0;
		i++;
	}
	return (map);
}

static char	***ft_read(const int fd, const int fd2)
{
	char	***map;
	char	*line;
	int		i;
	t_rnc	value;

	value = row_count(fd);
	map = malloc_grid(value, 0, 0);
	i = 0;
	while (get_next_line(fd2, &line) == 1)
	{
		map[i] = ft_strsplit(line, ' ');
		i++;
		free (line);
	}
	return (map);
}

t_dbls	initializer(t_ints I)
{
	t_dbls	D;

	D.deltaX = I.endX - I.x;
	D.deltaY = I.endY - I.y;
	if (I.y == I.endY)
		D.deltaZ = I.endZx - I.beginZ;
	else
		D.deltaZ = I.endZy - I.beginZ;
	D.pixels = sqrt((D.deltaX * D.deltaX)
			+ (D.deltaY * D.deltaY) + (D.deltaZ * D.deltaZ));
	D.deltaX /= D.pixels;
	D.deltaY /= D.pixels;
	D.deltaZ /= D.pixels;
	D.pixelX = I.x;
	D.pixelY = I.y;
	D.pixelZ = I.beginZ;
	return (D);
}

int	draw_line(void *mlx, void *win, t_ints I, int color)
{
	t_dbls	D;

	D = initializer(I);
	while (D.pixels)
	{
		if (I.projection == 1)
		{
			D.iso_x = (D.pixelX - D.pixelY) / sqrt(2);
			D.iso_y = (D.pixelX + (2 * D.pixelY) - D.pixelZ) / sqrt(6);
			mlx_pixel_put(mlx, win, D.iso_x, D.iso_y, color);
		}
		else
			mlx_pixel_put(mlx, win, D.pixelX, D.pixelY, color);
		D.pixelX += D.deltaX;
		D.pixelY += D.deltaY;
		D.pixelZ += D.deltaZ;
		--D.pixels;
	}
	return (1);
}

void	draw_end_lineY(void *mlx, void *win, t_ints I)
{
	int	offsetX;
	int	offsetY;

	if (I.beginZ > 99 || I.endZy > 99 || I.beginZ < -99 || I.endZy < -99)
		exit (1); // maybe have to add some memory freeing before this ?????????
	offsetY = 400;
	offsetX = 400;
	if (I.projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	I.x += 1;
	I.y += 1;
	I.x = (I.x * I.width) + offsetX;
	I.y = (I.y * I.height) + offsetY;
	I.endX = I.x;
	I.endY = I.y - I.height;
	I.beginZ *= I.height / 2;
	I.endZy *= I.height / 2;
	draw_line(mlx, win, I, 0xFFFFFF);
}

void	draw_end_lineX(void *mlx, void *win, t_ints I)
{
	int	offsetX;
	int	offsetY;

	if (I.beginZ > 99 || I.endZx > 99 || I.beginZ < -99 || I.endZx < -99)
		exit (1); // maybe have to add some memory freeing before this ?????????
	offsetY = 400;
	offsetX = 400;
	if (I.projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	I.x += 1;
	I.y += 1;
	I.x = (I.x * I.width) + offsetX;
	I.y = (I.y * I.height) + offsetY;
	I.endX = I.x - I.width;
	I.endY = I.y;
	I.beginZ *= I.height / 2;
	I.endZx *= I.height / 2;
	draw_line(mlx, win, I, 0xFFFFFF);
}

void	draw_corner(void *mlx, void *win, t_ints I)
{
	int	offsetX;
	int	offsetY;

	if (I.beginZ > 99 || I.endZx > 99 || I.endZy > 99
		|| I.beginZ < -99 || I.endZx < -99 || I.endZy < -99)
		exit (1); // maybe have to add some memory freeing before this ?????????
	offsetY = 400;
	offsetX = 400;
	if (I.projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	I.x++;
	I.y++;
	I.x = (I.x * I.width) + offsetX;
	I.y = (I.y * I.height) + offsetY;
	I.endX = I.x + I.width;
	I.endY = I.y;
	I.beginZ *= I.height / 2;
	I.endZx *= I.height / 2;
	I.endZy *= I.height / 2;
	draw_line(mlx, win, I, 0xFFFFFF);
	I.endX -= I.width;
	I.endY = I.y + I.height;
	draw_line(mlx, win, I, 0xFFFFFF);
}

t_ints	values(t_ints I, char ***map, int x_value, int y_value)
{
	I.beginZ = ft_atoi(map[I.y][I.x]);
	I.endZx = ft_atoi(map[I.y][I.x + x_value]);
	I.endZy = ft_atoi(map[I.y + y_value][I.x]);
	return (I);
}

void	draw_map(void *mlx, void *win, char ***map)
{
	t_ints	I;

	I.projection = 1;
	I.y = 0;
	I.x = 0;
	I.x_temp = 0;
	I.height = 4;
	I.width = 4;
	while (map[I.y + 1] != '\0')
	{
		while (map[I.y][I.x + 1] != '\0')
		{
			I = values(I, map, 1, 1);
			draw_corner(mlx, win, I);
			I.x++;
		}
		I.x_temp = I.x;
		I.x = 0;
		I.y++;
	}
	I.x = I.x_temp;
	while (I.x > 0)
	{
		if (I.x == 0)
			draw_end_lineX(mlx, win, I);
		else
		{
			I = values(I, map, -1, 0);
			draw_end_lineX(mlx, win, I);
		}
		I.x--;
	}
	I.x = I.x_temp;
	while (I.y > 0)
	{
		if (I.y == 0)
			draw_end_lineY(mlx, win, I);
		else
		{
			I = values(I, map, 0, -1);
			draw_end_lineY(mlx, win, I);
		}
		I.y--;
	}
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
