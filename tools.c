/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:20:01 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/07 16:47:35 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_inits	ft_read(t_inits ptrs, const int fd, const int fd2)
{
	char	*line;
	int		i;

	ptrs = row_count(fd, ptrs);
	ptrs = malloc_grid(ptrs, 0, 0);
	i = 0;
	//free_map(ptrs); // i guess free function works because it frees everything else but not the 16 bytes;
	while (get_next_line(fd2, &line) == 1)
	{
		ptrs.map[i] = ft_strsplit(line, ' ');
		i++;
		free (line);
	}
	valid_map(ptrs.map, 0, 0, 0);
	return (ptrs);
}

t_inits	malloc_grid(t_inits ptrs, int i, int j)
{
	ptrs.map = (char ***)malloc(sizeof(char **) * ptrs.rows + 1);
	while (i < ptrs.rows)
	{
		ptrs.map[i] = (char **)malloc(sizeof(char *) * ptrs.columns + 1);
		i++;
	}
	ptrs.map[i] = NULL;
	i = 0;
	while (i < ptrs.rows)
	{
		while (j < ptrs.columns)
		{
			ptrs.map[i][j] = ft_strnew(2);
			j++;
		}
		j = 0;
		i++;
	}
	return (ptrs);
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
	ptrs.columns = ptrs.columns - (ptrs.columns / 2);
	close (fd);
	return (ptrs);
}

void	free_map(t_inits ptrs)
{
	if (ptrs.rows == 0)
	{
		free(ptrs.map);
	}
	int	temp;
	printf("rows ; %d\n", ptrs.rows);
	printf("columns ; %d\n", ptrs.columns);
	ptrs.columns--;
	ptrs.rows--;
	temp = ptrs.columns;
	while (ptrs.rows >= 0)
	{
		while (ptrs.columns >= 0)
		{
			free(ptrs.map[ptrs.rows][ptrs.columns]);
			ptrs.columns--;
		}
		ptrs.columns = temp;
		free(ptrs.map[ptrs.rows]);
		ptrs.rows--;
	}
	//free(ptrs.map);
}
