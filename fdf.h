/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:58:33 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/07 11:19:49 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx.h"

typedef struct s_rnc
{
	int	rows;
	int	columns;
}				t_rnc;

typedef struct s_init_p
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	***map;
	int		size;
	int		fd2;
	int		fd;
	int		x;
	int		x_temp;
	int		y;
	int		endx;
	int		endy;
	int		beginz;
	int		endzx;
	int		endzy;
	int		height;
	int		width;
	int		projection;
	int		color;
	int		rot1;
	int		rot2;
	int		offsetx;
	int		offsety;
}				t_inits;

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

int		func(int keycode, t_inits *ptrs);
char	***ft_read(const int fd, const int fd2);
char	***malloc_grid(t_rnc value, int i, int j);
void	valid_map(char ***map, int i, int j, int count);
t_rnc	row_count(int fd);
t_inits	values(t_inits ptrs, int x_value, int y_value);
t_inits	initializer_ints(t_inits ptrs);
t_dbls	initializer_doubles(t_inits ptrs);
t_inits	call_end_linex(void *mlx, void *win, t_inits ptrs);
t_inits	call_end_liney(void *mlx, void *win, t_inits ptrs);
void	draw_end_linex(void *mlx, void *win, t_inits ptrs);
void	draw_end_liney(void *mlx, void *win, t_inits ptrs);
void	draw_map(void *mlx, void *win, t_inits ptrs);
t_inits	call_corner(void *mlx, void *win, t_inits ptrs);
void	draw_corner(void *mlx, void *win, t_inits ptrs);
int		draw_line(void *mlx, void *win, t_inits ptrs);
t_inits	main_init(t_inits ptrs);
void	start_mlx(t_inits ptrs);
void	error_exit(int i);

#endif