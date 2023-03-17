/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:42:41 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 13:12:19 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_lib.h"

void	_iterator(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst -> token);
		lst = lst -> next;
	}
}

void	_del_node(t_list **lst)
{
	t_list	*temp;

	if (!lst)
		return ;
	temp = *lst;
	*lst = (*lst)->next;
	free(temp);
}

void	_del_last_node(t_list **lst)
{
	t_list	*end;
	t_list	*prev;

	end = *lst;
	prev = NULL;
	while (end->next)
	{
		prev = end;
		end = end->next;
	}
	prev->next = NULL;
	free(end);
}

void	_clear_list(t_list **lst)
{
	if (!lst)
		return ;
	while (*lst != NULL)
	{
		list()->_del_node(lst);
	}
	lst = NULL;
}
