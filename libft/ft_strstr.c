/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:51:00 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/25 12:39:41 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	i2;
	int	i3;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		i2 = 0;
		i3 = i;
		while (haystack[i3] != '\0' && needle[i2] == haystack[i3])
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
