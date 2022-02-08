/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:48:03 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/08 21:11:03 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	func5(int keycode, t_inits *ptrs)
{
	if (keycode == 124)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->offsetx += 10;
		ptrs->offsety -= 5;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 42)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->color = 500500500;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	else
		func6(keycode, ptrs);
	return (0);
}

int	func6(int keycode, t_inits *ptrs)
{
	if (keycode == 30)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->color = 51200;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 33)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->color = 200200200;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	else
		func7(keycode, ptrs);
	return (0);
}

int	func7(int keycode, t_inits *ptrs)
{
	if (keycode == 35)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->color = 250;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 31)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->color = 9830600;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 34)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->color = 16777215;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	else
		func8(keycode, ptrs);
	return (0);
}

int	func8(int keycode, t_inits *ptrs)
{
	if (keycode == 6)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->z_depth += 1;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 7)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->z_depth -= 1;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	else
		func9(keycode, ptrs);
	return (0);
}
