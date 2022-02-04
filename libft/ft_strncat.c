/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:31:21 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/17 15:47:29 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int	id;
	int	is;

	id = 0;
	while (s1[id] != '\0')
	{
		id++;
	}
	is = 0;
	while (s2[is] != '\0' && n != 0)
	{
		s1[id] = s2[is];
		id++;
		is++;
		n--;
	}
	s1[id] = '\0';
	return (s1);
}
