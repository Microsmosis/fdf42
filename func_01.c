/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:42:38 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/07 16:46:13 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	func(int keycode, t_inits *ptrs)
{
	if (keycode == 53)
	{
		//free_map(*ptrs);
		system ("leaks fdf");
		exit (0);
	}
	if (keycode == 18)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->projection = 0;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 19)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->projection = 1;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	else
		func1(keycode, ptrs);
	return (0);
}

int	func1(int keycode, t_inits *ptrs)
{
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
	else
		func2(keycode, ptrs);
	return (0);
}

int	func2(int keycode, t_inits *ptrs)
{
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
	else
		func3(keycode, ptrs);
	return (0);
}

int	func3(int keycode, t_inits *ptrs)
{
	if (keycode == 69)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->color -= 10;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 126)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->offsety -= 10;
		ptrs->offsetx -= 10;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	else
		func4(keycode, ptrs);
	return (0);
}

int	func4(int keycode, t_inits *ptrs)
{
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
	else
		func5(keycode, ptrs);
	return (0);
}
