/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:55:53 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/26 14:43:58 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_end;
	size_t	d_temp;
	size_t	i;

	d_end = ft_strlen(dst);
	d_temp = d_end;
	i = 0;
	if (d_end > dstsize)
		return (ft_strlen(src) + dstsize);
	while (src[i] != '\0' && d_end < dstsize - 1)
	{
		dst[d_end] = src[i];
		i++;
		d_end++;
	}
	dst[d_end] = '\0';
	return (ft_strlen(src) + d_temp);
}
