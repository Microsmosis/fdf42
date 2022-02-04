/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:16:57 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/25 12:38:40 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			count;

	str = (unsigned char *)s;
	count = 0;
	while (count < n)
	{
		if (str[count] == (unsigned char)c)
			return ((void *)&str[count]);
		count++;
	}
	return (NULL);
}
