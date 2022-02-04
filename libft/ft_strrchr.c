/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:06:24 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/18 12:52:03 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_slen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strrchr(const char *str, int c)
{
	int	a;
	int	i;

	i = 0;
	a = ft_slen(str);
	while (str[i] != '\0')
	{
		i++;
	}
	while (a >= 0)
	{
		if ((char)c == str[i])
			return (&((char *)str)[i]);
		i--;
		a--;
	}
	return (0);
}
