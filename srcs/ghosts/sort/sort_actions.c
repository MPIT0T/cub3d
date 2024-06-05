/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:51:13 by cesar             #+#    #+#             */
/*   Updated: 2024/06/05 01:26:20 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	reverse_rotate_to(char list, t_list **lst)
{
	if (list == 'a')
		rra(lst);
	// else if (list == 'b')
	// 	rrb(lst);
}

void	reverse_rotate(t_list **lst)
{
	t_list	*blast;
	t_list	*tmp;

	tmp = *lst;
	blast = lstblast(*lst);
	ft_lstadd_front(lst, ft_lstlast(*lst));
	blast->next = NULL;
	(*lst)->next = tmp;
}

void	rra(t_list **la)
{
	reverse_rotate(la);
}

void	sa(t_list **la)
{
	swap(*la);
}

void	swap(t_list *lst)
{
	int	tmp;

	if (!lst || !lst->next)
		return ;
	tmp = ((t_ghost *)lst->content)->player_dist;
	((t_ghost *)lst->content)->player_dist = ((t_ghost *)lst->next->content)->player_dist;
	((t_ghost *)lst->next->content)->player_dist = tmp;
}
