/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:27:04 by llonnrot          #+#    #+#             */
/*   Updated: 2021/12/30 12:33:34 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	ft_error(t_gnl vrbls)
{
	ft_strdel(&vrbls.temp);
	ft_strdel(&vrbls.temp2);
	ft_strdel(&vrbls.buffer);
	return (-1);
}

static	int	ft_return_1_or_0(const int fd, t_gnl vrbls,
								char **statik, char **line)
{
	if (vrbls.readret == 0 && ft_strlen(vrbls.temp) == 0)
	{
		*line = vrbls.temp;
		ft_strdel(&statik[fd]);
		return (0);
	}
	else
	{
		*line = vrbls.temp;
		if (ft_strcmp(statik[fd], vrbls.temp) == 0)
		{
			ft_strdel(&statik[fd]);
			return (1);
		}
		vrbls.temp2 = ft_strdup((ft_strchr(statik[fd], NL) + 1));
		ft_strdel(&statik[fd]);
		statik[fd] = ft_strdup(vrbls.temp2);
		ft_strdel(&vrbls.temp2);
		return (1);
	}
}

static t_gnl	ft_read(const int fd, t_gnl vrbls, char **statik)
{
	while (vrbls.readret)
	{
		vrbls.readret = read(fd, vrbls.buffer, BUFF_SIZE);
		if (vrbls.readret < 0)
		{
			vrbls.readret = -1;
			return (vrbls);
		}
		ft_strdel(&statik[fd]);
		statik[fd] = ft_strjoin(vrbls.temp, vrbls.buffer);
		ft_strdel(&vrbls.temp);
		vrbls.temp = ft_strdup(statik[fd]);
		ft_bzero(vrbls.buffer, ft_strlen(vrbls.buffer));
		if (ft_strchr(statik[fd], NL))
			break ;
	}
	ft_strdel(&vrbls.buffer);
	ft_strdel(&statik[fd]);
	statik[fd] = ft_strjoin(vrbls.temp2, vrbls.temp);
	ft_strdel(&vrbls.temp2);
	ft_strdel(&vrbls.temp);
	vrbls.temp = ft_strsub(statik[fd], 0, ft_count_c(statik[fd], '\n'));
	return (vrbls);
}

static int	ft_return_1(const int fd, t_gnl vrbls, char **statik, char **line)
{
	*line = ft_strsub(statik[fd], 0, ft_count_c(statik[fd], '\n'));
	ft_strdel(&vrbls.temp2);
	vrbls.temp2 = ft_strdup(statik[fd]);
	ft_strdel(&statik[fd]);
	statik[fd] = ft_strsub(vrbls.temp2, ft_count_c(vrbls.temp2, '\n') + 1,
			ft_strlen(ft_strchr(vrbls.temp2, NL) + 1));
	ft_strdel(&vrbls.temp);
	ft_strdel(&vrbls.temp2);
	ft_strdel(&vrbls.buffer);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*statik[FD_SIZE];
	t_gnl		vrbls;

	vrbls.readret = 1;
	vrbls.temp = ft_strnew(BUFF_SIZE);
	vrbls.temp2 = ft_strnew(BUFF_SIZE);
	vrbls.buffer = ft_strnew(BUFF_SIZE);
	if (line == NULL || fd < 0 || fd >= FD_SIZE || BUFF_SIZE == 0)
		return (ft_error(vrbls));
	if (statik[fd] != NULL)
	{
		if (ft_strchr(statik[fd], NL))
			return (ft_return_1(fd, vrbls, statik, line));
		else
		{
			ft_strdel(&vrbls.temp2);
			vrbls.temp2 = ft_strsub(statik[fd], 0, ft_strlen(statik[fd]));
		}
	}
	vrbls = ft_read(fd, vrbls, statik);
	if (vrbls.readret == -1)
		return (ft_error(vrbls));
	return (ft_return_1_or_0(fd, vrbls, statik, line));
}

/*#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int fd = open("yea", O_RDONLY);
	char *line;
	
	printf("return ; %d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	free(line);
	printf("return ; %d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	free(line);
	printf("return ; %d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	free(line);
	return (0);
} */