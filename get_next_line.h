/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:42:20 by llonnrot          #+#    #+#             */
/*   Updated: 2022/01/24 16:35:04 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"

# define BUFF_SIZE 1
# define FD_SIZE 8192
# define NL '\n'

typedef struct s_gnl
{
	char		*buffer;
	char		*temp;
	char		*temp2;
	int			readret;
}				t_gnl;

int	get_next_line(const int fd, char **line);
#endif