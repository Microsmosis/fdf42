/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 21:10:37 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/08 21:24:29 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	func9(int keycode, t_inits *ptrs)
{
	if (keycode == 82)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->z_color *= 5;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 65)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->z_color /= 10;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	else
		func10(keycode, ptrs);
	return (0);
}

int	func10(int keycode, t_inits *ptrs)
{
	if (keycode == 83)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->z_color += 10;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	if (keycode == 84)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		ptrs->z_color = 13421258;
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, *ptrs);
	}
	return (0);
}
