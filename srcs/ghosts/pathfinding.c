/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/11 16:11:22 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};

int isValid(int y, int x, t_pos *pos)
{
    return (x > 0 && x < pos->MAP_WIDTH && y > 0
		&& y < pos->MAP_HEIGHT && (pos->map[y][x] == '0' || pos->map[y][x] == 'G'));
}


static	void moove_to(t_ghost *ghost, t_dir dir)
{
	ghost->x += dx[dir] * ghost->move_speed;
	ghost->y += dy[dir] * ghost->move_speed;
	ghost->dir = dir;
}

static void	wall_following_2(t_ghost *ghost, t_pos *pos)
{
	if (ghost->dir == EAST)
	{
		if (isValid(ghost->x, ghost->y + (dy[SOUTH] * ghost->move_speed), pos))
			return (moove_to(ghost, SOUTH));
		if (isValid(ghost->x + (dx[EAST] * ghost->move_speed), ghost->y, pos))
			return (moove_to(ghost, EAST));
		if (isValid(ghost->x, ghost->y + (dy[NORTH] * ghost->move_speed), pos))
			return (moove_to(ghost, NORTH));
		if (isValid(ghost->x + (dx[WEST] * ghost->move_speed), ghost->y, pos))
			return (moove_to(ghost, WEST));
	}
	else if (ghost->dir == WEST)
	{
		if (isValid(ghost->x, ghost->y + (dy[NORTH] * ghost->move_speed), pos))
			return (moove_to(ghost, NORTH));
		if (isValid(ghost->x + (dx[WEST] * ghost->move_speed), ghost->y, pos))
			return (moove_to(ghost, WEST));
		if (isValid(ghost->x, ghost->y + (dy[SOUTH] * ghost->move_speed), pos))
			return (moove_to(ghost, SOUTH));
		if (isValid(ghost->x + (dx[EAST] * ghost->move_speed), ghost->y, pos))
			return (moove_to(ghost, EAST));
	}
}

static void	wall_following_1(t_ghost *ghost, t_pos *pos)
{
	if (ghost->dir == NORTH)
	{
		if (isValid(ghost->x + (dx[EAST] * ghost->move_speed), ghost->y, pos))
			return (moove_to(ghost, EAST));
		if (isValid(ghost->x, ghost->y + (dy[NORTH] * ghost->move_speed), pos))
			return (moove_to(ghost, NORTH));
		if (isValid(ghost->x + (dx[WEST] * ghost->move_speed), ghost->y, pos))
			return (moove_to(ghost, WEST));
		if (isValid(ghost->x, ghost->y + (dy[SOUTH] * ghost->move_speed), pos))
			return (moove_to(ghost, SOUTH));
	}
	else if (ghost->dir == SOUTH)
	{
		if (isValid(ghost->x + (dx[WEST] * ghost->move_speed), ghost->y, pos))
			return (moove_to(ghost, WEST));
		if (isValid(ghost->x, ghost->y + (dy[SOUTH] * ghost->move_speed), pos))
			return (moove_to(ghost, SOUTH));
		if (isValid(ghost->x + (dx[EAST] * ghost->move_speed), ghost->y, pos))
			return (moove_to(ghost, EAST));
		if (isValid(ghost->x, ghost->y + (dy[NORTH] * ghost->move_speed), pos))
			return (moove_to(ghost, NORTH));
	}
	else
		wall_following_2(ghost, pos);
}

int	ghosts_are_coming(t_app *app)
{
	ssize_t	i;

	i = -1;
	while (++i < GHOSTS_NUMBER)
        wall_following_1(&app->ghosts[i], app->pos);
	return (0);
}