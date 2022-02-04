/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:26:25 by llonnrot          #+#    #+#             */
/*   Updated: 2021/12/03 11:50:13 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s)
{
	char	*newstr;
	int		start;
	int		end;
	int		nsi;

	if (s == NULL)
		return (NULL);
	start = 0;
	while (s[start] != '\0' && (s[start] == ' '
			|| s[start] == '\n' || s[start] == '\t'))
		start++;
	end = ft_strlen(s);
	while (end > start && (s[end] == ' ' || s[end] == '\n'
			|| s[end] == '\t' || s[end] == '\0'))
		end--;
	newstr = (char *)malloc(sizeof(char) * (end - start) + 2);
	if (newstr == NULL)
		return (NULL);
	nsi = 0;
	while (start <= end)
		newstr[nsi++] = s[start++];
	newstr[nsi] = '\0';
	return (newstr);
}
