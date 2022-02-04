/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:33:20 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/22 18:40:59 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	i2;
	size_t	i3;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		i2 = 0;
		i3 = i;
		while (i3 < len && haystack[i3] && needle[i2] == haystack[i3])
		{	
			i3++;
			i2++;
		}
		if (needle[i2] == '\0')
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}
