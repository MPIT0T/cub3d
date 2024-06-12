/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/12 10:00:05 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int isValid(t_ghost *ghost, t_dir dir, t_pos *pos, t_d d)
{
	int	y;
	int	x;

	y = ghost->x + (d.x[dir] * ghost->move_speed);
	x = ghost->y + (d.y[dir] * ghost->move_speed);
    return (x > 0 && x < pos->MAP_WIDTH && y > 0 && y < pos->MAP_HEIGHT
		&& (pos->map[y][x] == '0' || pos->map[y][x] == 'G'));
}


static	void moove_to(t_ghost *ghost, t_dir dir, t_d d)
{
	ghost->x += d.x[dir] * ghost->move_speed;
	ghost->y += d.y[dir] * ghost->move_speed;
	ghost->dir = dir;
}

static void	wall_following_2(t_ghost *ghost, t_pos *pos, t_d d)
{
	if (ghost->dir == EAST)
	{
		if (isValid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
		if (isValid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
		if (isValid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
		if (isValid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
	}
	else if (ghost->dir == WEST)
	{
		if (isValid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
		if (isValid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
		if (isValid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
		if (isValid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
	}
}

static void	wall_following_1(t_ghost *ghost, t_pos *pos, t_d d)
{
	if (ghost->dir == NORTH)
	{
		if (isValid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
		if (isValid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
		if (isValid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
		if (isValid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
	}
	else if (ghost->dir == SOUTH)
	{
		if (isValid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
		if (isValid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
		if (isValid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
		if (isValid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
	}
	else
		wall_following_2(ghost, pos, d);
}

int	ghosts_are_coming(t_app *app)
{
	ssize_t		i;
	t_d			d = { {-1, 1, 0, 0}, {0, 0, 1, -1} };

	i = -1;
	while (++i < GHOSTS_NUMBER)
        wall_following_1(&app->ghosts[i], app->pos, d);
	return (0);
}