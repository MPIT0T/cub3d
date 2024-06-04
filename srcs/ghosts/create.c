/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:49 by cesar             #+#    #+#             */
/*   Updated: 2024/06/04 23:45:31 by cesar            ###   ########.fr       */
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

void	initial_direction(t_ghost *ghost)
{
	if (ghost->dir == 'N')
	{
		ghost->dir_x = 0;
		ghost->dir_y = -1;
	}
	else if (ghost->dir == 'S')
	{
		ghost->dir_x = 0;
		ghost->dir_y = 1;
	}
	else if (ghost->dir == 'E')
	{
		ghost->dir_x = 1;
		ghost->dir_y = 0;
	}
	else if (ghost->dir == 'W')
	{
		ghost->dir_x = -1;
		ghost->dir_y = 0;
	}
}

int	generate_dir_charset(t_ghost *ghost)
{
	static int	i = 0;

	if (i > 1)
		i = 0;
	if (i == 0)
	{
		ghost->y_dirs_pref = ft_strdup("NS");
		ghost->x_dirs_pref = ft_strdup("EW");
		ghost->dir = ghost->y_dirs_pref[0];
	}
	else if (i == 1)
	{
		ghost->y_dirs_pref = ft_strdup("SN");
		ghost->x_dirs_pref = ft_strdup("WE");
		ghost->dir = ghost->x_dirs_pref[0];
	}
	i++;
	if (!ghost->y_dirs_pref || !ghost->x_dirs_pref)
		return (1);
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
		app->ghosts[i].move_speed = 0.20;
		if (generate_dir_charset(&app->ghosts[i]) == 1)
			exit_error(app, EXIT_MALLOC);
		initial_direction(&app->ghosts[i]);
		new = ft_lstnew(&app->ghosts[i]);
		if (!new)
			exit_error(app, EXIT_MALLOC);
		ft_lstadd_back(app->ghosts_lst, new);
	}
	return (0);
}
