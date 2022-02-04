/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:33:58 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/04 12:25:25 by llonnrot         ###   ########.fr       */
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
	int	endx;
	int	endy;
	int	beginz;
	int	endzx;
	int	endzy;
	int	height;
	int	width;
	int	projection;
}				t_ints;

typedef struct s_doubles
{
	double	deltax;
	double	deltay;
	double	deltaz;
	double	pixelx;
	double	pixely;
	double	pixelz;
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

t_dbls	initializer_doubles(t_ints i_s)
{
	t_dbls	d_s;

	d_s.deltax = i_s.endx - i_s.x;
	d_s.deltay = i_s.endy - i_s.y;
	if (i_s.y == i_s.endy)
		d_s.deltaz = i_s.endzx - i_s.beginz;
	else
		d_s.deltaz = i_s.endzy - i_s.beginz;
	d_s.pixels = sqrt((d_s.deltax * d_s.deltax)
			+ (d_s.deltay * d_s.deltay) + (d_s.deltaz * d_s.deltaz));
	d_s.deltax /= d_s.pixels;
	d_s.deltay /= d_s.pixels;
	d_s.deltaz /= d_s.pixels;
	d_s.pixelx = i_s.x;
	d_s.pixely = i_s.y;
	d_s.pixelz = i_s.beginz;
	return (d_s);
}

int	draw_line(void *mlx, void *win, t_ints i_s, int color)
{
	t_dbls	d_s;

	d_s = initializer_doubles(i_s);
	while (d_s.pixels)
	{
		if (i_s.projection == 1)
		{
			d_s.iso_x = (d_s.pixelx - d_s.pixely) / sqrt(2);
			d_s.iso_y = (d_s.pixelx + (2 * d_s.pixely) - d_s.pixelz) / sqrt(6);
			mlx_pixel_put(mlx, win, d_s.iso_x, d_s.iso_y, color);
		}
		else
			mlx_pixel_put(mlx, win, d_s.pixelx, d_s.pixely, color);
		d_s.pixelx += d_s.deltax;
		d_s.pixely += d_s.deltay;
		d_s.pixelz += d_s.deltaz;
		--d_s.pixels;
	}
	return (1);
}

t_ints	initializer_ints(t_ints i_s, int offsetX, int offsetY)
{
	i_s.x++;
	i_s.y++;
	i_s.x = (i_s.x * i_s.width) + offsetX;
	i_s.y = (i_s.y * i_s.height) + offsetY;
	i_s.endx = i_s.x + i_s.width;
	i_s.endy = i_s.y;
	i_s.beginz *= i_s.height / 2;
	i_s.endzx *= i_s.height / 2;
	i_s.endzy *= i_s.height / 2;
	return (i_s);
}

void	draw_end_liney(void *mlx, void *win, t_ints i_s)
{
	int	offsetX;
	int	offsetY;

	if (i_s.beginz > 99 || i_s.endzy > 99
		|| i_s.beginz < -99 || i_s.endzy < -99)
		exit (1); // maybe have to add some memory freeing before this ?????????
	offsetY = 400;
	offsetX = 400;
	if (i_s.projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	i_s.x++;
	i_s.y++;
	i_s.x = (i_s.x * i_s.width) + offsetX;
	i_s.y = (i_s.y * i_s.height) + offsetY;
	i_s.endx = i_s.x;
	i_s.endy = i_s.y - i_s.height;
	i_s.beginz *= i_s.height / 2;
	i_s.endzy *= i_s.height / 2;
	draw_line(mlx, win, i_s, 0xFFFFFF);
}

void	draw_end_linex(void *mlx, void *win, t_ints i_s)
{
	int	offsetX;
	int	offsetY;

	if (i_s.beginz > 99 || i_s.endzx > 99
		|| i_s.beginz < -99 || i_s.endzx < -99)
		exit (1); // maybe have to add some memory freeing before this ?????????
	offsetY = 400;
	offsetX = 400;
	if (i_s.projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	i_s.x++;
	i_s.y++;
	i_s.x = (i_s.x * i_s.width) + offsetX;
	i_s.y = (i_s.y * i_s.height) + offsetY;
	i_s.endx = i_s.x - i_s.width;
	i_s.endy = i_s.y;
	i_s.beginz *= i_s.height / 2;
	i_s.endzx *= i_s.height / 2;
	draw_line(mlx, win, i_s, 0xFFFFFF);
}

void	draw_corner(void *mlx, void *win, t_ints i_s)
{
	int	offsetX;
	int	offsetY;

	if (i_s.beginz > 99 || i_s.endzx > 99 || i_s.endzy > 99
		|| i_s.beginz < -99 || i_s.endzx < -99 || i_s.endzy < -99)
		exit (1); // maybe have to add some memory freeing before this ?????????
	offsetY = 400;
	offsetX = 400;
	if (i_s.projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	i_s = initializer_ints(i_s, offsetX, offsetY);
	draw_line(mlx, win, i_s, 0xFFFFFF);
	i_s.endx -= i_s.width;
	i_s.endy = i_s.y + i_s.height;
	draw_line(mlx, win, i_s, 0xFFFFFF);
}

t_ints	values(t_ints i_s, char ***map, int x_value, int y_value)
{
	i_s.beginz = ft_atoi(map[i_s.y][i_s.x]);
	i_s.endzx = ft_atoi(map[i_s.y][i_s.x + x_value]);
	i_s.endzy = ft_atoi(map[i_s.y + y_value][i_s.x]);
	return (i_s);
}

t_ints	call_end_liney(void *mlx, void *win, char ***map, t_ints i_s)
{
	while (i_s.y > 0)
	{
		if (i_s.y == 0)
			draw_end_liney(mlx, win, i_s);
		else
		{
			i_s = values(i_s, map, 0, -1);
			draw_end_liney(mlx, win, i_s);
		}
		i_s.y--;
	}
	return (i_s);
}

t_ints	call_end_linex(void *mlx, void *win, char ***map, t_ints i_s)
{
	while (i_s.x > 0)
	{
		if (i_s.x == 0)
			draw_end_linex(mlx, win, i_s);
		else
		{
			i_s = values(i_s, map, -1, 0);
			draw_end_linex(mlx, win, i_s);
		}
		i_s.x--;
	}
	i_s.x = i_s.x_temp;
	return (i_s);
}

t_ints	call_corner(void *mlx, void *win, char ***map, t_ints i_s)
{
	while (map[i_s.y + 1] != '\0')
	{
		while (map[i_s.y][i_s.x + 1] != '\0')
		{
			i_s = values(i_s, map, 1, 1);
			draw_corner(mlx, win, i_s);
			i_s.x++;
		}
		i_s.x_temp = i_s.x;
		i_s.x = 0;
		i_s.y++;
	}
	i_s.x = i_s.x_temp;
	return (i_s);
}

void	draw_map(void *mlx, void *win, char ***map)
{
	t_ints	i_s;

	i_s.projection = 1;
	i_s.y = 0;
	i_s.x = 0;
	i_s.x_temp = 0;
	i_s.height = 24;
	i_s.width = 24;
	i_s = call_corner(mlx, win, map, i_s);
	i_s = call_end_linex(mlx, win, map, i_s);
	i_s = call_end_liney(mlx, win, map, i_s);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	char	***map;
	t_inits	ptrs;
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
