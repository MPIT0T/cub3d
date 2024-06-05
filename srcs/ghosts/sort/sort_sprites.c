/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:28:49 by cesar             #+#    #+#             */
/*   Updated: 2024/06/05 01:55:07 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

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

// void	print_sorted(t_list *la)
// {
// 	while (la)
// 	{
// 		printf("dist is %f\n", ((t_ghost *)la->content)->player_dist);
// 		la = la->next;
// 	}
// 	printf("\n\n");
// }

int	get_max(t_list *la)
{
	int	max;

	max = INT_MIN;
	while (la)
	{
		if (((t_ghost *)la->content)->player_dist > max)
			max = ((t_ghost *)la->content)->player_dist;
		la = la->next;
	}
	return (max);
}

int	sort_sprites(t_list **la)
{
	t_list	*lb;

	lb = NULL;
	lil_sort(la, &lb);
	// print_sorted(*la);
	lstfree(&lb);
	return (0);
}