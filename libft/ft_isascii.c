/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:56:04 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/29 19:29:20 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	char	count;

	count = 0;
	if (c < 0 || c > 127)
		return (0);
	while (count <= 127)
	{
		if (count == c)
		{
			return (1);
		}
		count++;
	}
	return (0);
}
