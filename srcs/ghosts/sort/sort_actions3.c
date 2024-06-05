/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_actions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:58:58 by cesar             #+#    #+#             */
/*   Updated: 2024/06/05 01:27:14 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	push(t_list **dest, t_list **src)
{
	t_list	*tmp;

	if (*src == NULL)
		return ;
	tmp = *src;
	*src = (*src)->next;
	tmp->next = NULL;
	ft_lstadd_front(dest, tmp);
}

t_list	*lstblast(t_list *lst)
{
	t_list	*blast;

	blast = lst;
	while (blast && blast->next->next)
		blast = blast->next;
	return (blast);
}

int	cost(t_list *lst, int size)
{
	int	cost;

	cost = 0;
	while (lst && (((t_ghost *)lst->content)->is_theone == 0))
	{
		lst = lst->next;
		cost++;
	}
	if (cost <= size / 2)
		return (0);
	return (1);
}

void	rb(t_list **lb)
{
	rotate(lb);
}
