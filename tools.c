/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:20:01 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/08 20:35:42 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_inits	readnalloc(t_inits ptrs, const int fd, const int fd2)
{
	char	*line;
	int		i;

	ptrs = row_count(fd, ptrs);
	ptrs = malloc_grid(ptrs, 0, 0);
	i = 0;
	free_map(&ptrs);
	while (get_next_line(fd2, &line) == 1)
	{
		ptrs.map[i] = ft_strsplit(line, ' ');
		i++;
		free (line);
	}
	free (line);
	valid_map(ptrs.map, 0, 0, 0);
	return (ptrs);
}

t_inits	malloc_grid(t_inits ptrs, int i, int j)
{
	ptrs.map = (char ***)malloc(sizeof(char **) * (ptrs.rows + 1));
	while (i < ptrs.rows)
	{
		ptrs.map[i] = (char **)malloc(sizeof(char *) * (ptrs.columns + 1));
		i++;
	}
	ptrs.map[i] = NULL;
	j = 0;
	return (ptrs);
}

void	valid_map(char ***map, int i, int j, int count)
{
	int	k;

	k = 0;
	while (map[i] != '\0')
	{
		while (map[i][j] != '\0')
		{
			while (map[i][j][k] != '\0')
			{
				if (map[i][j][k] == '-')
				k++;
				if (ft_isdigit(map[i][j][k]) == 0)
					error_exit_01(0);
				k++;
			}
			k = 0;
			j++;
		}
		if (i == 0)
			count = j;
		if (i > 0 && j != count)
			error_exit (3);
		j = 0;
		i++;
	}
}

t_inits	row_count(int fd, t_inits ptrs)
{
	char	*line;

	ptrs.rows = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (ptrs.rows == 0)
		{
			ptrs.columns = ft_strlen(line);
		}
		ptrs.rows++;
		free (line);
	}
	free (line);
	if (ptrs.rows == 0)
		error_exit (2);
	ptrs.columns = ptrs.columns - (ptrs.columns / 2);
	close (fd);
	ptrs.rows_copy = ptrs.rows;
	return (ptrs);
}

void	free_map(t_inits *ptrs)
{
	while (ptrs->rows >= 0)
	{
		free(ptrs->map[ptrs->rows]);
		ptrs->rows--;
	}
}
