/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:51:38 by llonnrot          #+#    #+#             */
/*   Updated: 2022/01/25 18:01:44 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		counter(char *s, char c)
{
	int	i;
	int	delimiter;

	i = 0;
	delimiter = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			delimiter++;
		i++;
	}
	return (i - delimiter);
}

char	*ft_split(char *s, char c)
{
	int		i;
	int		j;
	char	*splitted;

	i = 0;
	j = 0;
	splitted = ft_strnew(counter(s, c));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		splitted[j] = s[i];
		j++;
		i++;
	}
	return (splitted);
}