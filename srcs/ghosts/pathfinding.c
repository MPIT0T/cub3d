/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/13 10:01:52 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_valid(t_ghost *ghost, t_dir dir, t_pos *pos, t_d d)
{
	double	y;
	double	x;

	x = ghost->y + (d.y[dir] * ghost->move_speed);
	y = ghost->x + (d.x[dir] * ghost->move_speed);
	return (x > 0 && x < pos->map_width && y > 0 && y < pos->map_height
		&& (pos->map[(int)y][(int)x] == '0'
		|| pos->map[(int)y][(int)x] == 'G'));
}

static void	moove_to(t_ghost *ghost, t_dir dir, t_d d)
{
	ghost->y += d.y[dir] * ghost->move_speed;
	ghost->x += d.x[dir] * ghost->move_speed;
	ghost->dir = dir;
}

static void	wall_following_2(t_ghost *ghost, t_pos *pos, t_d d)
{
	if (ghost->dir == EAST)
	{
		if (is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
		if (is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
		if (is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
		if (is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
	}
	else if (ghost->dir == WEST)
	{
		if (is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
		if (is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
		if (is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
		if (is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
	}
}

static void	wall_following_1(t_ghost *ghost, t_pos *pos, t_d d)
{
	if (ghost->dir == NORTH)
	{
		if (is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
		if (is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
		if (is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
		if (is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
	}
	else if (ghost->dir == SOUTH)
	{
		if (is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
		if (is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
		if (is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
		if (is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
	}
	else
		wall_following_2(ghost, pos, d);
}

int	ghosts_are_coming(t_app *app)
{
	ssize_t		i;
	const t_d	d = {{-1, 1, 0, 0}, {0, 0, 1, -1}};

	i = -1;
	while (++i < GHOSTS_NUMBER)
		wall_following_1(&app->ghosts[i], app->pos, d);
	return (0);
}
