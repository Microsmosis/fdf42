/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:45:18 by llonnrot          #+#    #+#             */
/*   Updated: 2021/12/15 12:25:03 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*ns;

	ns = (char *)malloc(sizeof(char) * size + 1);
	if (!ns)
		return (NULL);
	ft_memset(ns, '\0', size + 1);
	return (ns);
}
