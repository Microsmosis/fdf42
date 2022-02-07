/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:58:33 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/07 16:42:35 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx.h"
# include <stdio.h>

/* typedef struct s_rnc
{
	int	rows;
	int	columns;
}				t_rnc;
 */
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
	int		rows;
	int		columns;
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

t_inits	ft_read(t_inits ptrs, const int fd, const int fd2);
t_inits	malloc_grid(t_inits ptrs, int i, int j);
void	valid_map(char ***map, int i, int j, int count);
t_inits	row_count(int fd, t_inits ptrs);
t_inits	values(t_inits ptrs, int x_value, int y_value);
t_inits	initializer_ints(t_inits ptrs);
t_dbls	initializer_doubles(t_inits ptrs);
t_inits	call_end_linex(void *mlx, void *win, t_inits ptrs);
t_inits	call_end_liney(void *mlx, void *win, t_inits ptrs);
void	draw_end_linex(void *mlx, void *win, t_inits ptrs);
void	draw_end_liney(void *mlx, void *win, t_inits ptrs);
t_inits	draw_map(void *mlx, void *win, t_inits ptrs);
t_inits	call_corner(void *mlx, void *win, t_inits ptrs);
void	draw_corner(void *mlx, void *win, t_inits ptrs);
int		draw_line(void *mlx, void *win, t_inits ptrs);
t_inits	main_init(t_inits ptrs);
void	start_mlx(t_inits ptrs);
void	error_exit(int i);
void	free_map(t_inits ptrs);
int		func(int keycode, t_inits *ptrs);
int		func1(int keycode, t_inits *ptrs);
int		func2(int keycode, t_inits *ptrs);
int		func3(int keycode, t_inits *ptrs);
int		func4(int keycode, t_inits *ptrs);
int		func5(int keycode, t_inits *ptrs);
int		func6(int keycode, t_inits *ptrs);
int		func7(int keycode, t_inits *ptrs);

#endif