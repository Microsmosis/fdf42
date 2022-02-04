/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:42:38 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/04 16:59:46 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(void *mlx, void *win, char ***map, int size);

int	func(int keycode, t_inits *ptrs)
{
	if (keycode == 53)
		exit (0);
	if (keycode == 49)
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
	if (keycode == 24)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, ptrs->map, ++ptrs->size);
	}
	if (keycode == 27)
	{
		mlx_clear_window(ptrs->mlx_ptr, ptrs->win_ptr);
		draw_map(ptrs->mlx_ptr, ptrs->win_ptr, ptrs->map, --ptrs->size);
	}
	return (0);
	
}
