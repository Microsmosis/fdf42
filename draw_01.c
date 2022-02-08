/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:14:23 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/08 18:55:14 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_inits	draw_map(void *mlx, void *win, t_inits ptrs)
{
	ptrs.y = 0;
	ptrs.x = 0;
	ptrs.x_temp = 0;
	ptrs.height = ptrs.size;
	ptrs.width = ptrs.size;
	ptrs = call_corner(mlx, win, ptrs);
	ptrs = call_end_linex(mlx, win, ptrs);
	ptrs = call_end_liney(mlx, win, ptrs);
	return (ptrs);
}

t_inits	call_corner(void *mlx, void *win, t_inits ptrs)
{
	while (ptrs.map[ptrs.y + 1] != '\0')
	{
		while (ptrs.map[ptrs.y][ptrs.x + 1] != '\0')
		{
			ptrs = values(ptrs, 1, 1);
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

void	draw_corner(void *mlx, void *win, t_inits ptrs)
{
	ptrs = initializer_ints(ptrs);
	draw_line(mlx, win, ptrs);
	ptrs.endx -= ptrs.width;
	ptrs.endy = ptrs.y + ptrs.height;
	draw_line(mlx, win, ptrs);
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
			d_s.iso_y = (d_s.pixelx + (2 * d_s.pixely)
					- d_s.pixelz) / sqrt(ptrs.rot2);
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
