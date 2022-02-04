/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:30 by llonnrot          #+#    #+#             */
/*   Updated: 2021/12/15 13:13:20 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*res;

	if (size > 4177892)
		return (NULL);
	res = malloc (sizeof(size));
	if (!res)
		return (NULL);
	ft_bzero(res, size);
	return (res);
}
