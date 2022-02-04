/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:38:38 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/26 15:50:05 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_freelist(t_list *head)
{
	t_list	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*head;

	if (lst == NULL || f == NULL)
		return (NULL);
	new = f(lst);
	if (new == NULL)
		return (NULL);
	head = new;
	while (lst->next != NULL)
	{
		new->next = f(lst->next);
		if (new->next == NULL)
		{
			ft_freelist(head);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (head);
}
