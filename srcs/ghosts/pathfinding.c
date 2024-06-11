/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/11 17:36:35 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};

int isValid(int y, int x, t_pos *pos)
{
	return (x > 0 && x < pos->MAP_WIDTH && y > 0 && y < pos->MAP_HEIGHT && (pos->map[y][x] == '0' || pos->map[y][x] == '3'));
}


static	void moove_to(t_ghost *ghost, t_dir dir)
{
	// return ;
	ghost->x += dx[dir] * ghost->move_speed;
	ghost->y += dy[dir] * ghost->move_speed;
	ghost->dir = dir;
}

static void	wall_following_2(t_ghost *ghost, t_pos *pos)
{
	if (ghost->dir == EAST)
	{
		if (isValid(ghost->x - 0.5 + dx[SOUTH] * ghost->move_speed, ghost->y - 0.5 + dy[SOUTH] * ghost->move_speed, pos))
			return (moove_to(ghost, SOUTH));
		if (isValid(ghost->x - 0.5 + dx[EAST] * ghost->move_speed, ghost->y - 0.5 + dy[EAST] * ghost->move_speed, pos))
			return (moove_to(ghost, EAST));
		if (isValid(ghost->x - 0.5 + dx[NORTH] * ghost->move_speed, ghost->y - 0.5 + dy[NORTH] * ghost->move_speed, pos))
			return (moove_to(ghost, NORTH));
		if (isValid(ghost->x - 0.5 + dx[WEST] * ghost->move_speed, ghost->y - 0.5 + dy[WEST] * ghost->move_speed, pos))
			return (moove_to(ghost, WEST));
	}
	else if (ghost->dir == WEST)
	{
		if (isValid(ghost->x - 0.5 + dx[NORTH] * ghost->move_speed, ghost->y - 0.5 + dy[NORTH] * ghost->move_speed, pos))
			return (moove_to(ghost, NORTH));
		if (isValid(ghost->x - 0.5 + dx[WEST] * ghost->move_speed, ghost->y - 0.5 + dy[WEST] * ghost->move_speed, pos))
			return (moove_to(ghost, WEST));
		if (isValid(ghost->x - 0.5 + dx[SOUTH] * ghost->move_speed, ghost->y - 0.5 + dy[SOUTH] * ghost->move_speed, pos))
			return (moove_to(ghost, SOUTH));
		if (isValid(ghost->x - 0.5 + dx[EAST] * ghost->move_speed, ghost->y - 0.5 + dy[EAST] * ghost->move_speed, pos))
			return (moove_to(ghost, EAST));
	}
}

static void	wall_following_1(t_ghost *ghost, t_pos *pos)
{
	if (ghost->dir == NORTH)
	{
		if (isValid(ghost->x - 0.5 + dx[EAST] * ghost->move_speed, ghost->y - 0.5 + dy[EAST] * ghost->move_speed, pos))
			return (moove_to(ghost, EAST));
		if (isValid(ghost->x - 0.5 + dx[NORTH] * ghost->move_speed, ghost->y - 0.5 + dy[NORTH] * ghost->move_speed, pos))
			return (moove_to(ghost, NORTH));
		if (isValid(ghost->x - 0.5 + dx[WEST] * ghost->move_speed, ghost->y - 0.5 + dy[WEST] * ghost->move_speed, pos))
			return (moove_to(ghost, WEST));
		if (isValid(ghost->x - 0.5 + dx[SOUTH] * ghost->move_speed, ghost->y - 0.5 + dy[SOUTH] * ghost->move_speed, pos))
			return (moove_to(ghost, SOUTH));
	}
	else if (ghost->dir == SOUTH)
	{
		if (isValid(ghost->x - 0.5 + dx[WEST] * ghost->move_speed, ghost->y - 0.5 + dy[WEST] * ghost->move_speed, pos))
			return (moove_to(ghost, WEST));
		if (isValid(ghost->x - 0.5 + dx[SOUTH] * ghost->move_speed, ghost->y - 0.5 + dy[SOUTH] * ghost->move_speed, pos))
			return (moove_to(ghost, SOUTH));
		if (isValid(ghost->x - 0.5 + dx[EAST] * ghost->move_speed, ghost->y - 0.5 + dy[EAST] * ghost->move_speed, pos))
			return (moove_to(ghost, EAST));
		if (isValid(ghost->x - 0.5 + dx[NORTH] * ghost->move_speed, ghost->y - 0.5 + dy[NORTH] * ghost->move_speed, pos))
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