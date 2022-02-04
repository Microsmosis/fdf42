/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:33:58 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/04 18:19:58 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* int	func1(int keycode, t_inits *ptrs)
{
	ptrs = NULL;
	ft_putnbr(keycode);
	return (0);
} */

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

t_dbls	initializer_doubles(t_inits ptrs)
{
	t_dbls	d_s;

	d_s.deltax = ptrs.endx - ptrs.x;
	d_s.deltay = ptrs.endy - ptrs.y;
	if (ptrs.y == ptrs.endy)
		d_s.deltaz = ptrs.endzx - ptrs.beginz;
	else
		d_s.deltaz = ptrs.endzy - ptrs.beginz;
	d_s.pixels = sqrt((d_s.deltax * d_s.deltax)
			+ (d_s.deltay * d_s.deltay) + (d_s.deltaz * d_s.deltaz));
	d_s.deltax /= d_s.pixels;
	d_s.deltay /= d_s.pixels;
	d_s.deltaz /= d_s.pixels;
	d_s.pixelx = ptrs.x;
	d_s.pixely = ptrs.y;
	d_s.pixelz = ptrs.beginz;
	return (d_s);
}

int	draw_line(void *mlx, void *win, t_inits ptrs)
{
	t_dbls	d_s;

	d_s = initializer_doubles(ptrs);
	while (d_s.pixels)
	{
		if (ptrs.projection == 1)
		{
			d_s.iso_x = (d_s.pixelx - d_s.pixely) / sqrt(ptrs.rot1);
			d_s.iso_y = (d_s.pixelx + (2 * d_s.pixely) - d_s.pixelz) / sqrt(ptrs.rot2);
			ptrs.color -= 1;
			mlx_pixel_put(mlx, win, d_s.iso_x, d_s.iso_y, ptrs.color);
		}
		else
			mlx_pixel_put(mlx, win, d_s.pixelx, d_s.pixely, ptrs.color);
		d_s.pixelx += d_s.deltax;
		d_s.pixely += d_s.deltay;
		d_s.pixelz += d_s.deltaz;
		--d_s.pixels;
	}
	return (1);
}

t_inits	initializer_ints(t_inits ptrs)
{
	ptrs.x++;
	ptrs.y++;
	ptrs.x = (ptrs.x * ptrs.width) + ptrs.offsetx;
	ptrs.y = (ptrs.y * ptrs.height) + ptrs.offsety;
	ptrs.endx = ptrs.x + ptrs.width;
	ptrs.endy = ptrs.y;
	ptrs.beginz *= ptrs.height / 2;
	ptrs.endzx *= ptrs.height / 2;
	ptrs.endzy *= ptrs.height / 2;
	return (ptrs);
}

void	draw_end_liney(void *mlx, void *win, t_inits ptrs)
{
	if (ptrs.beginz > 99 || ptrs.endzy > 99
		|| ptrs.beginz < -99 || ptrs.endzy < -99)
		exit (1);
	ptrs.x++;
	ptrs.y++;
	ptrs.x = (ptrs.x * ptrs.width) + ptrs.offsetx;
	ptrs.y = (ptrs.y * ptrs.height) + ptrs.offsety;
	ptrs.endx = ptrs.x;
	ptrs.endy = ptrs.y - ptrs.height;
	ptrs.beginz *= ptrs.height / 2;
	ptrs.endzy *= ptrs.height / 2;
	draw_line(mlx, win, ptrs);
}

void	draw_end_linex(void *mlx, void *win, t_inits ptrs)
{
	if (ptrs.beginz > 99 || ptrs.endzx > 99
		|| ptrs.beginz < -99 || ptrs.endzx < -99)
		exit (1);
	ptrs.x++;
	ptrs.y++;
	ptrs.x = (ptrs.x * ptrs.width) + ptrs.offsetx;
	ptrs.y = (ptrs.y * ptrs.height) + ptrs.offsety;
	ptrs.endx = ptrs.x - ptrs.width;
	ptrs.endy = ptrs.y;
	ptrs.beginz *= ptrs.height / 2;
	ptrs.endzx *= ptrs.height / 2;
	draw_line(mlx, win, ptrs);
}

void	draw_corner(void *mlx, void *win, t_inits ptrs)
{
	if (ptrs.beginz > 99 || ptrs.endzx > 99 || ptrs.endzy > 99
		|| ptrs.beginz < -99 || ptrs.endzx < -99 || ptrs.endzy < -99)
		exit (1);
	ptrs = initializer_ints(ptrs);
	draw_line(mlx, win, ptrs);
	ptrs.endx -= ptrs.width;
	ptrs.endy = ptrs.y + ptrs.height;
	draw_line(mlx, win, ptrs);
}

t_inits	values(t_inits ptrs, int x_value, int y_value)
{
	ptrs.beginz = ft_atoi(ptrs.map[ptrs.y][ptrs.x]);
	ptrs.endzx = ft_atoi(ptrs.map[ptrs.y][ptrs.x + x_value]);
	ptrs.endzy = ft_atoi(ptrs.map[ptrs.y + y_value][ptrs.x]);
	return (ptrs);
}

t_inits	call_end_liney(void *mlx, void *win, t_inits ptrs)
{
	while (ptrs.y > 0)
	{
		if (ptrs.y == 0)
			draw_end_liney(mlx, win, ptrs);
		else
		{
			ptrs = values(ptrs, 0, -1);
			draw_end_liney(mlx, win, ptrs);
		}
		ptrs.y--;
	}
	return (ptrs);
}

t_inits	call_end_linex(void *mlx, void *win, t_inits ptrs)
{
	while (ptrs.x > 0)
	{
		if (ptrs.x == 0)
			draw_end_linex(mlx, win, ptrs);
		else
		{
			ptrs = values(ptrs, -1, 0);
			draw_end_linex(mlx, win, ptrs);
		}
		ptrs.x--;
	}
	ptrs.x = ptrs.x_temp;
	return (ptrs);
}

t_inits	call_corner(void *mlx, void *win, t_inits ptrs)
{
	while (ptrs.map[ptrs.y + 1] != '\0')
	{
		while (ptrs.map[ptrs.y][ptrs.x + 1] != '\0')
		{
			ptrs = values(ptrs, 1, 1);
			ptrs.color -= 2;
			draw_corner(mlx, win, ptrs);
			ptrs.x++;
		}
		ptrs.x_temp = ptrs.x;
		ptrs.x = 0;
		ptrs.y++;
	}
	ptrs.x = ptrs.x_temp;
	return (ptrs);
}

void	draw_map(void *mlx, void *win, t_inits ptrs)
{
	ptrs.y = 0;
	ptrs.x = 0;
	ptrs.x_temp = 0;
	ptrs.height = ptrs.size;
	ptrs.width = ptrs.size;
	ptrs = call_corner(mlx, win, ptrs);
	ptrs = call_end_linex(mlx, win, ptrs);
	ptrs = call_end_liney(mlx, win, ptrs);
}

int	main(int argc, char **argv)
{
	t_inits	ptrs;
	
	ptrs.size = 24;
	ptrs.projection = 1;
	ptrs.color = 500500500;
	ptrs.rot1 = 2;
	ptrs.rot2 = 6;
	ptrs.offsetx = 900;
	ptrs.offsety = -100;
	if (argc == 2)
	{
		ptrs.fd = open(argv[1], O_RDONLY);
		ptrs.fd2 = open(argv[1], O_RDONLY);
	}
	else
	{
		ft_putstr("	usage :		./a.out <filename.>\n");
		exit (1);
	}
	if (ptrs.fd == -1 || ptrs.fd2 == -1)
		exit (1);
	ptrs.map = ft_read(ptrs.fd, ptrs.fd2);
	close (ptrs.fd);
	close (ptrs.fd2);
	if (ptrs.map == NULL)
	{
		ft_putstr("error\n");
		exit (1);
	}
	ptrs.mlx_ptr = mlx_init();
	ptrs.win_ptr = mlx_new_window(ptrs.mlx_ptr, 1720, 1240, "mlx hive");
	draw_map(ptrs.mlx_ptr, ptrs.win_ptr, ptrs);
	mlx_key_hook(ptrs.win_ptr, &func, &ptrs);
	mlx_loop(ptrs.mlx_ptr);
	exit (0);
}
