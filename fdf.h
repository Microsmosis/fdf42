/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:58:33 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/04 14:59:49 by llonnrot         ###   ########.fr       */
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

#endif