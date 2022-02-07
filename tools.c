/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:20:01 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/07 10:22:50 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	***ft_read(const int fd, const int fd2)
{
	char	***map;
	char	*line;
	int		i;
	t_rnc	value;

	value = row_count(fd);
	map = malloc_grid(value, 0, 0);
	i = 0;
	while (get_next_line(fd2, &line) == 1)
	{
		map[i] = ft_strsplit(line, ' ');
		i++;
		free (line);
	}
	valid_map(map, 0, 0, 0);
	return (map);
}

char	***malloc_grid(t_rnc value, int i, int j)
{
	char	***map;

	map = (char ***)malloc(sizeof(char **) * value.rows);
	while (i < value.rows)
	{
		map[i] = (char **)malloc(sizeof(char *) * value.columns + 1);
		i++;
	}
	map[i] = NULL;
	i = 0;
	while (i < value.rows)
	{
		while (j < value.columns)
		{
			map[i][j] = ft_strnew(2);
			j++;
		}
		j = 0;
		i++;
	}
	return (map);
}

void	valid_map(char ***map, int i, int j, int count)
{
	while (map[i] != '\0')
	{
		while (map[i][j] != '\0')
		{
			j++;
		}
		if (i == 0)
			count = j;
		if (i > 0 && j != count)
			exit (1);
		j = 0;
		i++;
	}
}

t_rnc	row_count(int fd)
{
	t_rnc	value;
	char	*line;

	value.rows = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (value.rows == 0)
		{
			value.columns = ft_strlen(line);
		}
		value.rows++;
		free (line);
	}
	free (line);
	value.columns = value.columns - (value.columns / 2);
	close (fd);
	return (value);
}
