/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:33:58 by llonnrot          #+#    #+#             */
/*   Updated: 2022/01/25 16:24:27 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include "mlx.h"
#include "get_next_line.h"

typedef struct s_init_p
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_inits;

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

void	square2d(void *mlx, void *win, int x1, int y1, int x2, int y2)
{
	draw_line(mlx, win, x1, y1, x2, y2, 0xFFFFFF); // higher horizontal 
	draw_line(mlx, win, x1, y1, x1, y2 + 25, 0xFFFFFF); // left vertical
	draw_line(mlx, win, x1, y1 + 25, x2, y2 + 25, 0xFFFFFF); // lower horizontal
	draw_line(mlx, win, x1 + 25, y1 + 25, x2, y2 - 1, 0xFFFFFF); // right vertical
}

void	grid2(void *mlx, void *win, int x_len, int y_len)
{
	int		i = 100;
	int		j = 125;
	int		k = 200;
	int		counter = 0;
	int		size = 0;
	
	while (size < y_len)
	{
		while (counter < x_len)
		{
			square2d(mlx, win, i, k, j, k);
			i += 25;
			j += 25;
			counter++;
		}
		size++;
		counter = 0;
		i = 100;
		j = 125;
		k += 25;
	}
}

int		func(int keycode, t_inits *ptrs)
{
	if (keycode == 53)
		exit (0);
	if (keycode == 49)
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	
	t_inits ptrs;
	
	int		fd;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
	{
		ft_putstr("	usage :		./a.out <filename.>\n");
		return (1);
	}
	int		x_len;
	int		y_len = 0;
	char	*line;
	while (get_next_line(fd, &line) == 1)
	{
		y_len++;
		x_len = ft_strlen(line);
	}
	ptrs.mlx_ptr	= mlx_init();
	ptrs.win_ptr = mlx_new_window(ptrs.mlx_ptr, 1720, 1240, "mlx hive");
	grid2(ptrs.mlx_ptr, ptrs.win_ptr, (x_len / 2) + 1, y_len);
	mlx_key_hook(ptrs.win_ptr, &func, &ptrs);
	//grid(mlx_ptr, win_ptr, (len / 2) + 1, count);
	mlx_loop(ptrs.mlx_ptr);
}
