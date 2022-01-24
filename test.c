/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:33:58 by llonnrot          #+#    #+#             */
/*   Updated: 2022/01/24 16:48:33 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include "mlx.h"
#include "get_next_line.h"

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

void	square(void *mlx, void *win, int x1, int y1, int x2, int y2)
{
	draw_line(mlx, win, x1, y1, x2, y2, 0xFFFFFF); // higher horizontal 
	draw_line(mlx, win, x1 - 50, y1 + 25, x2 - 50, y2 + 25, 0xFFFFFF); // lower horizontal
	draw_line(mlx, win, x1 - 50, y1 + 25, x2 - 50, y2 - 25, 0xFFFFFF); // left vertical
	draw_line(mlx, win, x1, y1 + 50, x2, y2, 0xFFFFFF); // right vertical
}

void	grid(void *mlx, void *win, int x_len, int y_len)
{
	int		i = 600;
	int		j = 250;
	int		counter = 0;
	int		size = 0;
	
	while (size < y_len)
	{
		while (counter < x_len)
		{
			square(mlx, win, i + 200, j, i + 250, j + 25);
			i += 50;
			j += 25;
			counter++;
		}
		size++;
		counter = 0;
		i = 600;
		j = 250;
		i -= 50 * size;
		j += 25 * size;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		fd;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (1);
	int		len;
	int		count = 0;
	char	*line;
	while (get_next_line(fd, &line) == 1)
	{
		count++;
		len = ft_strlen(line);
	}

	mlx_ptr	= mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 2000, 1250, "mlx hive");
	grid(mlx_ptr, win_ptr, (len / 2) + 1, count);
	mlx_loop(mlx_ptr);
}
