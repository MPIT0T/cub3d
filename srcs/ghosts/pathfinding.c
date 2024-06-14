/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/14 13:49:34 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_valid(t_ghost *ghost, t_dir dir, t_pos *pos, t_d d)
{
	double	y;
	double	x;

	if (d.x[dir] >= 0)
		y = ghost->x + (d.x[dir] * 0.5001);
	else
		y = ghost->x + (d.x[dir] * 0.5001);
	if (d.y[dir] >= 0)
		x = ghost->y + (d.y[dir] * 0.5001);
	else
		x = ghost->y + (d.y[dir] * 0.5001);

	if (x > 0 && x < pos->map_width && y > 0 && y < pos->map_height
		&& (pos->map[(int)y][(int)x] == '0'
		|| pos->map[(int)y][(int)x] == '3'))
			return (1);
	return (0);
}

static void	moove_to(t_ghost *ghost, t_dir dir, t_d d)
{
	ghost->y += (d.y[dir] * ghost->move_speed);
	ghost->x += (d.x[dir] * ghost->move_speed);
	ghost->dir = dir;
	ghost->dec += 1;
	ghost->dec %= 10;
}

static void	wall_following_2(t_ghost *ghost, t_pos *pos, t_d d)
{
	if (ghost->dir == EAST)
	{
		if (ghost->dec == 0 && is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
		if (is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
		if (ghost->dec == 0 && is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
		if (ghost->dec == 0 && is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
	}
	else if (ghost->dir == WEST)
	{
		if (ghost->dec == 0 && is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
		if (is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
		if (ghost->dec == 0 && is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
		if (ghost->dec == 0 && is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
	}
}

static void	wall_following_1(t_ghost *ghost, t_pos *pos, t_d d)
{
	if (ghost->dir == NORTH)
	{
		if (ghost->dec == 0 && is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
		if (is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d));
		if (ghost->dec == 0 && is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
		if (ghost->dec == 0 && is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
	}
	else if (ghost->dir == SOUTH)
	{
		if (ghost->dec == 0 && is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d));
		if (is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d));
		if (ghost->dec == 0 && is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d));
		if (ghost->dec == 0 && is_valid(ghost, NORTH, pos, d))
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
