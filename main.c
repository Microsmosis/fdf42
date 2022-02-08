/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:09:25 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/08 19:41:25 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_straight(void *mlx, void *win, t_inits ptrs)
{
	ptrs = initializer_ints(ptrs);
	draw_line(mlx, win, ptrs);
}

t_inits	main_init(t_inits ptrs)
{
	ptrs.size = 24;
	ptrs.projection = 1;
	ptrs.color = 0xFFFFFFF;
	ptrs.rot1 = 2;
	ptrs.rot2 = 6;
	ptrs.offsetx = 900;
	ptrs.offsety = -100;
	return (ptrs);
}

void	start_mlx(t_inits ptrs)
{
	ptrs.mlx_ptr = mlx_init();
	ptrs.win_ptr = mlx_new_window(ptrs.mlx_ptr, 1720, 1240, "mlx hive");
	draw_map(ptrs.mlx_ptr, ptrs.win_ptr, ptrs);
	mlx_key_hook(ptrs.win_ptr, &func, &ptrs);
	mlx_loop(ptrs.mlx_ptr);
}

void	error_exit(int i)
{
	if (i == 0)
	{
		ft_putstr("	usage :		./a.out <filename.>\n");
		system ("leaks fdf");
		exit (1);
	}
	else if (i == 1)
	{
		ft_putstr("Error occured when opening file descriptor.\n");
		exit (1);
	}
	else if (i == 2)
	{
		ft_putstr("Empty file.");
		system ("leaks fdf");
		exit (1);
	}
}

int	main(int argc, char **argv)
{
	t_inits	ptrs;

	ptrs.projection = 1;
	ptrs = main_init(ptrs);
	if (argc == 2)
	{
		ptrs.fd = open(argv[1], O_RDONLY);
		ptrs.fd2 = open(argv[1], O_RDONLY);
	}
	else
		error_exit(0);
	if (ptrs.fd == -1 || ptrs.fd2 == -1)
		exit (1);
	ptrs = readnalloc(ptrs, ptrs.fd, ptrs.fd2);
	close (ptrs.fd);
	close (ptrs.fd2);
	start_mlx(ptrs);
	exit (0);
}
