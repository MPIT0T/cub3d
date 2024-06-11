/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:49 by cesar             #+#    #+#             */
/*   Updated: 2024/06/11 14:26:40 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void 	print_map(t_pos *pos)
{
	ssize_t	y;
	ssize_t	x;

	y = -1;
	x = -1;
	while (++y < pos->MAP_HEIGHT)
	{
		while (++x < pos->MAP_WIDTH)
			printf("%c", pos->map[y][x]);
		x = -1;
		printf("\n");
	}
	printf("\n\n");
}

int	get_opposite_of_player(t_pos *pos)
{
	int	quarter;

	if (pos->posX < pos->MAP_WIDTH * 0.5 && pos->posY < pos->MAP_HEIGHT * 0.5)
		quarter = 4;
	else if (pos->posX >= pos->MAP_WIDTH * 0.5 && pos->posY < pos->MAP_HEIGHT * 0.5)
		quarter = 3;
	else if (pos->posX < pos->MAP_WIDTH * 0.5 && pos->posY >= pos->MAP_HEIGHT * 0.5)
		quarter = 2;
	else
		quarter = 1;
	return (quarter);
}

int	pop_some_ghosts(t_app *app)
{
	ssize_t	i;
	t_list	*new;

	i = -1;
	app->ghosts_lst = NULL;
	app->ghosts = malloc(GHOSTS_NUMBER * sizeof(t_ghost));
	if (!app->ghosts)
		exit_error(app, EXIT_MALLOC);
	while (++i < GHOSTS_NUMBER)
	{
		app->ghosts[i].move_speed = 0.15;
		app->ghosts[i].dir = i % 4;
		new = ft_lstnew(&app->ghosts[i]);
		if (!new)
			exit_error(app, EXIT_MALLOC);
		spawning_point(app->pos, &app->ghosts[i]);
		ft_lstadd_back(&app->ghosts_lst, new);
	}
	return (0);
}
 