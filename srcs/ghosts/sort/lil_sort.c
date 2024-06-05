/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lil_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:41:25 by cesar             #+#    #+#             */
/*   Updated: 2024/06/05 01:55:37 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	mark_the_one(t_list **lst)
{
	int		max;
	t_list	*tmp;

	max = get_max(*lst);
	tmp = *lst;
	while (*lst)
	{
		if (((t_ghost *)(*lst)->content)->player_dist == max)
			((t_ghost *)(*lst)->content)->is_theone = 1;
		else
			((t_ghost *)(*lst)->content)->is_theone = 0;
		*lst = (*lst)->next;
	}
	*lst = tmp;
}

void	go_to_the_one(char list, t_list **lst, int size)
{
	void	(*r)(char, t_list **);

	if (cost(*lst, size) == 0)
		r = rotate_to;
	else
		r = reverse_rotate_to;
	while (*lst && ((t_ghost *)(*lst)->content)->is_theone == 0)
		r(list, lst);
}

void	sort_two(t_list **la)
{
	if (((t_ghost *)(*la)->content)->player_dist < ((t_ghost *)(*la)->next->content)->player_dist)
		sa(la);
}

void	sort_three(t_list **la)
{
	int	a;
	int	b;
	int	c;

	a = ((t_ghost *)(*la)->content)->player_dist;
	b = ((t_ghost *)(*la)->next->content)->player_dist;
	c = ((t_ghost *)(*la)->next->next->content)->player_dist;
	if (a > b && b < c && a < c)
		sa(la);
	else if (a > b && b > c)
	{
		sa(la);
		rra(la);
	}
	else if (a > b && b < c)
		ra(la);
	else if (a < b && b > c && a < c)
	{
		sa(la);
		ra(la);
	}
	else if (a < b && b > c)
		rra(la);
}

void	lil_sort(t_list **la, t_list **lb)
{
	int	size;

	size = ft_lstsize(*la);
	if (size == 2)
		return (sort_two(la));
	while (size > 3)
	{
		mark_the_one(la);
		go_to_the_one('a', la, size);
		pb(lb, la);
		size--;
	}
	sort_three(la);
	while (*lb)
		pa(la, lb);
}