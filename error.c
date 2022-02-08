/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:21:34 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/08 20:30:28 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_exit(int i)
{
	if (i == 0)
	{
		ft_putstr("	usage :		./a.out <filename.>\n");
		exit (1);
	}
	else if (i == 1)
	{
		ft_putstr("Error occured when opening file descriptor.\n");
		exit (1);
	}
	else if (i == 2)
	{
		ft_putstr("Empty file.\n");
		exit (1);
	}
	else if (i == 3)
	{
		ft_putstr("Invalid file. ");
		ft_putstr("Valid file consist of rows of equal length of lines.\n");
		exit (1);
	}
}

void	error_exit_01(int i)
{
	if (i == 0)
	{
		ft_putstr("Invalid file. ");
		ft_putstr("Valid file consist of numbers. ");
		ft_putstr("No letters or special characters.\n");
		exit (1);
	}
}
