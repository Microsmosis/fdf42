/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:42:38 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/04 18:17:59 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(void *mlx, void *win, t_inits ptrs);

int	func(int keycode, t_inits *ptrs)
{
	if (keycode == 53)
		exit (0);
	if (keycode == 49)
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
	if (keycode == 24)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		++ptrs->size;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 27)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		--ptrs->size;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 67)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		--ptrs->rot2;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 78)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		++ptrs->rot2;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 69)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->color -= 100;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 126)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->offsety -= 10;
		ptrs->offsetx -= 10;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 123)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->offsetx -= 10;
		ptrs->offsety += 5;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 125)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->offsety += 10;
		ptrs->offsetx += 10;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 124)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->offsetx += 10;
		ptrs->offsety -= 5;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	return (0);
	
}
