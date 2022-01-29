/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:33:58 by llonnrot          #+#    #+#             */
/*   Updated: 2022/01/29 17:20:17 by llonnrot         ###   ########.fr       */
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

int draw_line(void *mlx, void *win, int beginX, int beginY, int beginZ, int endX, int endY, int endZ, int projection, int color)
{
	double	deltaX = endX - beginX;
	double	deltaY = endY - beginY;
	double	deltaZ = endZ - beginZ;

	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));

	deltaX /= pixels;
	deltaY /= pixels;
	deltaZ /= pixels;
	
	double pixelX = beginX;
	double pixelY = beginY;
	double pixelZ = beginZ;
	double	x;
	double	y;
	while (pixels)
	{
		if (projection == 1)
		{
			x = (pixelX - pixelY)/sqrt(2);
			y = (pixelX + (2 * pixelY) - pixelZ)/sqrt(6);
			mlx_pixel_put(mlx, win, x, y, color);
		}
		else
		{
			mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		}
		pixelX += deltaX;
		pixelY += deltaY;
		pixelZ += deltaZ;
		--pixels;
	}
	return (1);
}

void	draw_end_lineY(void *mlx, void *win, int x, int y, int beginZ, int endZy, int height, int width, int projection)
{
	int	offsetX;
	int	offsetY;

	offsetY = 400;
	offsetX = 400;
	if (projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	x += 1;
	y += 1;
	x *= width;
	y *= height;
	beginZ *= height / 4;
	endZy *= height / 4;
	draw_line(mlx, win, x + offsetX, y + offsetY, beginZ, x + offsetX, (y - height) + offsetY, endZy, projection, 0xFFFFFF);
}

void	draw_end_lineX(void *mlx, void *win, int x, int y, int beginZ, int endZx, int height, int width, int projection)
{
	int	offsetX;
	int	offsetY;

	offsetY = 400;
	offsetX = 400;
	if (projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	x += 1;
	y += 1;
	x *= width;
	y *= height;
	beginZ *= height / 4;
	endZx *= height / 4;
	draw_line(mlx, win, x + offsetX, y + offsetY, beginZ, (x - width) + offsetX, y + offsetY, endZx, projection, 0xFFFFFF);
}

void	draw_corner(void *mlx, void *win, int x, int y, int beginZ, int endZx, int endZy, int height, int width, int projection)
{
	int	offsetX;
	int	offsetY;

	offsetY = 400;
	offsetX = 400;
	if (projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	x++;
	y++;
	x *= width;
	y *= height;
	beginZ *= height / 4;
	endZx *= height / 4;
	endZy *= height / 4;
	draw_line(mlx, win, x + offsetX, y + offsetY, beginZ, (x + width) + offsetX, y + offsetY, endZx, projection, 0xFFFFFF);
	draw_line(mlx, win, x + offsetX, y + offsetY, beginZ, x + offsetX, (y + height) + offsetY, endZy, projection, 0xFFFFFF);
}

void	draw_map(void *mlx, void *win, char ***map)
{
	int	y;
	int	x;
	int	x2;
	int	height;
	int	width;
	int	projection = 1;
	y = 0;
	x = 0;
	x2 = 0;
	height = 32;
	width = 32;
	while (map[y + 1] != '\0')
	{
		while (map[y][x + 1] != '\0')
		{
			/* if (map[y][x + 1] == '\0')
				draw_corner(mlx, win, x, y, ft_atoi(map[y][x]), ft_atoi(map[y][x]), ft_atoi(map[y + 1][x]), height, width, projection);
			else */
				draw_corner(mlx, win, x, y, ft_atoi(map[y][x]), ft_atoi(map[y][x + 1]), ft_atoi(map[y + 1][x]), height, width, projection);
			x++;
		}
		x2 = x;
		x = 0;
		y++;
	}
	x = x2;
	while (x2 > 0)
	{
		if (x2 == 0)
			draw_end_lineX(mlx, win, x2, y, ft_atoi(map[y][x2]), ft_atoi(map[y][x2]), height, width, projection);
		else
			draw_end_lineX(mlx, win, x2, y, ft_atoi(map[y][x2]), ft_atoi(map[y][x2 - 1]), height, width, projection);
		x2--;
	}
	while (y > 0)
	{
		if (y == 0)
			draw_end_lineY(mlx, win, x, y, ft_atoi(map[y][x]), ft_atoi(map[y][x]), height, width, projection);
		else
			draw_end_lineY(mlx, win, x, y, ft_atoi(map[y][x]), ft_atoi(map[y - 1][x]), height, width, projection);
		y--;
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
