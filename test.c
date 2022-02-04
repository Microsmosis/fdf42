/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:33:58 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/04 16:14:31 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	func(int keycode, t_inits *ptrs)
{
	if (keycode == 53)
		exit (0);
	if (keycode == 49)
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
	/* if (keycode == 24)
	{
		zoom in
	}
	if (keycode == 27)
	{
		zoom out
	} */
	return (0);
}

int	func1(int keycode, t_inits *ptrs)
{
	ptrs = NULL;
	ft_putnbr(keycode);
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
		{
			value.columns = ft_strlen(line);
		}
		value.rows++;
		free (line);
	}
	free (line);
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

void	valid_map(char ***map, int i, int j, int count)
{
	while (map[i] != '\0')
	{
		while (map[i][j] != '\0')
		{
			j++;
		}
		if (i == 0)
			count = j;
		if (i > 0 && j != count)
			exit (1);
		j = 0;
		i++;
	}
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
	valid_map(map, 0, 0, 0);
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
		exit (1);
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
		exit (1);
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
		exit (1);
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

void	draw_map(void *mlx, void *win, char ***map, int size)
{
	t_ints	i_s;

	i_s.projection = 1;
	i_s.y = 0;
	i_s.x = 0;
	i_s.x_temp = 0;
	i_s.height = size;
	i_s.width = size;
	i_s = call_corner(mlx, win, map, i_s);
	i_s = call_end_linex(mlx, win, map, i_s);
	i_s = call_end_liney(mlx, win, map, i_s);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	int		size = 24;
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
		exit (1);
	}
	if (fd == -1 || fd2 == -1)
		exit (1);
	map = ft_read(fd, fd2);
	close (fd);
	close (fd2);
	if (map == NULL)
	{
		ft_putstr("error\n");
		exit (1);
	}
	ptrs.mlx_ptr = mlx_init();
	ptrs.win_ptr = mlx_new_window(ptrs.mlx_ptr, 1720, 1240, "mlx hive");
	draw_map(ptrs.mlx_ptr, ptrs.win_ptr, map, size);
	mlx_key_hook(ptrs.win_ptr, &func, &ptrs);
	mlx_loop(ptrs.mlx_ptr);
	exit (0);
}
