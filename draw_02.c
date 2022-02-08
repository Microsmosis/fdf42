/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:15:59 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/08 21:28:05 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	draw_end_linex(void *mlx, void *win, t_inits ptrs)
{
	ptrs.x++;
	ptrs.y++;
	ptrs.x = (ptrs.x * ptrs.width) + ptrs.offsetx;
	ptrs.y = (ptrs.y * ptrs.height) + ptrs.offsety;
	ptrs.endx = ptrs.x - ptrs.width;
	ptrs.endy = ptrs.y;
	ptrs.beginz *= ptrs.z_depth;
	ptrs.endzx *= ptrs.z_depth;
	if (ptrs.beginz > 0 || ptrs.endzx > 0 || ptrs.endzy > 0)
		ptrs.color = ptrs.z_color;
	draw_line(mlx, win, ptrs);
}

void	draw_end_liney(void *mlx, void *win, t_inits ptrs)
{
	ptrs.x++;
	ptrs.y++;
	ptrs.x = (ptrs.x * ptrs.width) + ptrs.offsetx;
	ptrs.y = (ptrs.y * ptrs.height) + ptrs.offsety;
	ptrs.endx = ptrs.x;
	ptrs.endy = ptrs.y - ptrs.height;
	ptrs.beginz *= ptrs.z_depth;
	ptrs.endzy *= ptrs.z_depth;
	if (ptrs.beginz > 0 || ptrs.endzx > 0 || ptrs.endzy > 0)
		ptrs.color = ptrs.z_color;
	draw_line(mlx, win, ptrs);
}

void	straight_line(void *mlx, void *win, t_inits ptrs)
{
	while (ptrs.map[ptrs.y][ptrs.x + 1] != '\0')
	{
		ptrs = values(ptrs, 1, 0);
		draw_straight(mlx, win, ptrs);
		ptrs.x++;
	}
}
