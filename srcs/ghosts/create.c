/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:49 by cesar             #+#    #+#             */
/*   Updated: 2024/06/06 10:13:05 by cefuente         ###   ########.fr       */
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

void	apply_initial_dir(t_ghost *ghost)
{
	if (ghost->dir == N)
	{
		ghost->dir_x = 0;
		ghost->dir_y = -1;
	}
	else if (ghost->dir == S)
	{
		ghost->dir_x = 0;
		ghost->dir_y = 1;
	}
	else if (ghost->dir == E)
	{
		ghost->dir_x = 1;
		ghost->dir_y = 0;
	}
	else if (ghost->dir == W)
	{
		ghost->dir_x = -1;
		ghost->dir_y = 0;
	}
}

int	initial_dir(t_ghost *ghost)
{
	static int	i = 0;

	if (i > 1)
		i = 0;
	if (i == 0)
		ghost->dirset = {0, 1, 2, 3};
	else if (i == 1)
		ghost->dirset = {0, 3, 2, 1};
	i++;
	return (0);
}

int	set_walls(t_ghost *ghost, char **map, int height)
{
	ssize_t	i;

	i = -1;
	ghost->walls = malloc(4 * sizeof(int));
	if (!ghost->walls)
		return (1);
	while (++i < 4)
		ghost->walls[i] = false;
	ghost->wall_following = false;
	return (0);
}

int	pop_some_ghosts(t_app *app)
{
	ssize_t	i;
	int		quarter;
	t_list	*new;

	i = -1;
	app->ghosts_lst = NULL;
	quarter = get_opposite_of_player(app->pos);
	app->ghosts = malloc(GHOSTS_NUMBER * sizeof(t_ghost));
	if (!app->ghosts)
		exit_error(app, EXIT_MALLOC);
	while (++i < GHOSTS_NUMBER)
	{
		spawning_point(app->pos, &app->ghosts[i], quarter);
		app->ghosts[i].move_speed = 0.05;
		if (initial_dir(&app->ghosts[i]) == 1)
			exit_error(app, EXIT_MALLOC);
		apply_initial_dir(&app->ghosts[i]);
		if (set_walls(&app->ghosts[i], app->pos->map, app->pos->MAP_HEIGHT) == 1)
			exit_error(app, EXIT_MALLOC);
		new = ft_lstnew(&app->ghosts[i]);
		if (!new)
			exit_error(app, EXIT_MALLOC);
		ft_lstadd_back(&app->ghosts_lst, new);
	}
	return (0);
}
