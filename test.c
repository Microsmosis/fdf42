/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:33:58 by llonnrot          #+#    #+#             */
/*   Updated: 2022/01/25 19:47:45 by llonnrot         ###   ########.fr       */
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

/* typedef struct s_init_p
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
} */

/* int		func(int keycode, t_inits *ptrs)
{
	if (keycode == 53)
		exit (0);
	if (keycode == 49)
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
	return (0);
} */

char	*ft_split(char *s, char c);

int		check_spaces(char **map)
{
	int	y;
	int	x;

	y = 0;
	x = 1;
	while (map[y][0] != '\0')
	{
		while (map[y][x] != '\0')
		{
			if (map[y][x] != ' ')
				return (0);
			x += 2;
		}
		x = 1;
		y++;
	}
	return (1);
} 

static char	**validate_and_split(char **map)
{
	int	len1;
	int	len2;
	int	i;

	i = 0;
	if (check_spaces(map) == 0)
		return (NULL);
	while (map[i][0] != '\0')
	{
		len1 = ft_strlen(map[i]);
		len2 = ft_strlen(map[i + 1]);
		if (len1 == len2 || len2 == 0)
		{
			map[i] = ft_split(map[i], ' ');
			i++;
		}
		else
			return (NULL);
	}
	return (map);
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
	}
	close (fd);
	return (value);
}

static char	**ft_read(const int fd, const int fd2)
{
	char	**map;
	char	*line;
	int		i;
	int		x;
	int		y;
	t_rnc	value;
	
	i = 0;
	x = 0;
	y = 0;
	value = row_count(fd);
	map = (char **)malloc(sizeof(char *) * value.rows + 1);
	while (i < 10)
		map[i++] = ft_strnew(value.columns);
	i = 0;
	while (get_next_line(fd2, &line) == 1)
	{
		while (line[i] != '\0')
		{
			map[y][x] = line[i];
			i++;
			x++;
		}
		i = 0;
		x = 0;
		y++;
	}
	return (validate_and_split(map));
}

int	main(int argc, char **argv)
{
	
	//t_inits ptrs;
	int		fd;
	int		fd2;
	char	**map;
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
	if (map == NULL)
	{
		printf("error\n");
		return (1);
	}
	printf("%s\n", map[3]);
	//ptrs.mlx_ptr = mlx_init();
	//ptrs.win_ptr = mlx_new_window(ptrs.mlx_ptr, 1720, 1240, "mlx hive");
	//mlx_key_hook(ptrs.win_ptr, &func, &ptrs);
	//mlx_loop(ptrs.mlx_ptr);
	return (0);
}
