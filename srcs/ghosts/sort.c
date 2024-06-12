/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:33:00 by cesar             #+#    #+#             */
/*   Updated: 2024/06/12 10:51:59 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	lstfree(t_list **lst)
{
	t_list	*tmp;

	if (!*lst || !lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	swap(t_list *a, t_list *b)
{
	t_ghost	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	sort_list(t_list **head)
{
	int		swapped;
	t_list	*ptr1;
	t_list	*lptr;

	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *head;
		while (ptr1->next != lptr)
		{
			if (((t_ghost *)ptr1->content)->player_dist
				< ((t_ghost *)ptr1->next->content)->player_dist)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
