/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:29:38 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/25 16:57:53 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	char	count;

	count = 0;
	if (c < 32 || c > 126)
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
