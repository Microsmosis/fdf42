/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:18:52 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/08 20:49:22 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_inits	values(t_inits ptrs, int x_value, int y_value)
{
	ptrs.beginz = ft_atoi(ptrs.map[ptrs.y][ptrs.x]);
	ptrs.endzx = ft_atoi(ptrs.map[ptrs.y][ptrs.x + x_value]);
	ptrs.endzy = ft_atoi(ptrs.map[ptrs.y + y_value][ptrs.x]);
	return (ptrs);
}

t_inits	initializer_ints(t_inits ptrs)
{
	ptrs.x++;
	ptrs.y++;
	ptrs.x = (ptrs.x * ptrs.width) + ptrs.offsetx;
	ptrs.y = (ptrs.y * ptrs.height) + ptrs.offsety;
	ptrs.endx = ptrs.x + ptrs.width;
	ptrs.endy = ptrs.y;
	ptrs.beginz *= ptrs.z_depth;
	ptrs.endzx *= ptrs.z_depth;
	ptrs.endzy *= ptrs.z_depth;
	return (ptrs);
}

t_dbls	initializer_doubles(t_inits ptrs)
{
	t_dbls	d_s;

	d_s.deltax = ptrs.endx - ptrs.x;
	d_s.deltay = ptrs.endy - ptrs.y;
	if (ptrs.y == ptrs.endy)
		d_s.deltaz = ptrs.endzx - ptrs.beginz;
	else
		d_s.deltaz = ptrs.endzy - ptrs.beginz;
	d_s.pixels = sqrt((d_s.deltax * d_s.deltax)
			+ (d_s.deltay * d_s.deltay) + (d_s.deltaz * d_s.deltaz));
	d_s.deltax /= d_s.pixels;
	d_s.deltay /= d_s.pixels;
	d_s.deltaz /= d_s.pixels;
	d_s.pixelx = ptrs.x;
	d_s.pixely = ptrs.y;
	d_s.pixelz = ptrs.beginz;
	return (d_s);
}
