/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:54:12 by llonnrot          #+#    #+#             */
/*   Updated: 2021/12/15 12:25:07 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		ins;
	int		inf;
	char	*fuze;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	fuze = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!fuze)
		return (NULL);
	ins = 0;
	inf = 0;
	while (s1[ins])
	{
		fuze[inf++] = s1[ins++];
	}
	ins = 0;
	while (s2[ins])
	{
		fuze[inf++] = s2[ins++];
	}
	fuze[inf] = '\0';
	return (fuze);
}
