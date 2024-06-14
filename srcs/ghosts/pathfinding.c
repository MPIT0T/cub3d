/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/14 12:24:36 by cefuente         ###   ########.fr       */
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
		{
			printf("dir %d is valid\n", dir);
			return (1);
		}
	return (0);
}

static void	moove_to(t_ghost *ghost, t_dir dir, t_d d, int *dec)
{
	int	last_x;
	int	last_y;

	last_x = ghost->x;
	last_y = ghost->y;

	ghost->y += (d.y[dir] * ghost->move_speed);
	ghost->x += (d.x[dir] * ghost->move_speed);
	ghost->dir = dir;
	*dec += 1;
	*dec %= 10;


	// if ((ghost->x != last_x) || ghost->y != last_y)
	// 	has_moved = true;
	// else
	// 	has_moved = false;
}

static void	wall_following_2(t_ghost *ghost, t_pos *pos, t_d d, int *dec)
{
	if (ghost->dir == EAST)
	{
		if (*dec == 0 && is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d, dec));
		if (is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d, dec));
		if (*dec == 0 && is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d, dec));
		if (*dec == 0 && is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d, dec));
	}
	else if (ghost->dir == WEST)
	{
		if (*dec == 0 && is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d, dec));
		if (is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d, dec));
		if (*dec == 0 && is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d, dec));
		if (*dec == 0 && is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d, dec));
	}
}

static void	wall_following_1(t_ghost *ghost, t_pos *pos, t_d d)
{
	static int	dec = 0;

	if (ghost->dir == NORTH)
	{
		if (dec == 0 && is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d, &dec));
		if (is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d, &dec));
		if (dec == 0 && is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d, &dec));
		if (dec == 0 && is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d, &dec));
	}
	else if (ghost->dir == SOUTH)
	{
		if (dec == 0 && is_valid(ghost, WEST, pos, d))
			return (moove_to(ghost, WEST, d, &dec));
		if (is_valid(ghost, SOUTH, pos, d))
			return (moove_to(ghost, SOUTH, d, &dec));
		if (dec == 0 && is_valid(ghost, EAST, pos, d))
			return (moove_to(ghost, EAST, d, &dec));
		if (dec == 0 && is_valid(ghost, NORTH, pos, d))
			return (moove_to(ghost, NORTH, d, &dec));
	}
	else
		wall_following_2(ghost, pos, d, &dec);
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
