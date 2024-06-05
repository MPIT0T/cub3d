/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_actions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:56:19 by cesar             #+#    #+#             */
/*   Updated: 2024/06/05 01:26:31 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	pa(t_list **la, t_list **lb)
{
	push(la, lb);
}

void	pb(t_list **lb, t_list **la)
{
	push(lb, la);
}

void	rotate(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	*lst = (*lst)->next;
	tmp->next = NULL;
	ft_lstadd_back(lst, tmp);
}

void	rotate_to(char list, t_list **lst)
{
	if (list == 'a')
		ra(lst);
	else if (list == 'b')
		rb(lst);
}

void	ra(t_list **la)
{
	rotate(la);
}
