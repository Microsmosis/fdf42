/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:45:09 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/26 15:55:16 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (alst != NULL)
	{
		while (*alst != NULL)
		{
			del((*alst)->content, (*alst)->content_size);
			free (*alst);
			*alst = (*alst)->next;
		}
		*alst = NULL;
	}
}
