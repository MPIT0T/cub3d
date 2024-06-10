/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/07 10:23:28 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};

int isValid(int x, int y, t_pos *pos)
{
    return (x > 0 && x < pos->MAP_WIDTH && y > 0 && y < pos->MAP_HEIGHT && pos->map[y][x] != '1');
}


static	void moove_to(t_ghost *ghost, t_dir dir, t_pos *pos)
{
	int	last_x;
	int	last_y;

	last_x = ghost->x;
	last_y = ghost->y;
	// (void)pos;
	ghost->x += dx[dir] * ghost->move_speed;
	ghost->y += dy[dir] * ghost->move_speed;
	if ((int)ghost->x != last_x || (int)ghost->y != last_y)
	{
		pos->map[last_y][last_x] = '0';
		pos->map[(int)ghost->y][(int)ghost->x] = 'G';
	}
	ghost->dir = dir;
}

static	void	wall_following(t_ghost *ghost, t_pos *pos)
{
	if (ghost->dir == NORTH)
	{
		if (isValid(ghost->x + dx[EAST], ghost->y + dy[EAST], pos))
			return (moove_to(ghost, EAST, pos));
		else if (isValid(ghost->x + dx[NORTH], ghost->y + dy[NORTH], pos))
			return (moove_to(ghost, NORTH, pos));
		else if (isValid(ghost->x + dx[WEST], ghost->y + dy[WEST], pos))
			return (moove_to(ghost, WEST, pos));
		else if (isValid(ghost->x + dx[SOUTH], ghost->y + dy[SOUTH], pos))
			return (moove_to(ghost, SOUTH, pos));
	}
	else if (ghost->dir == SOUTH)
	{
		if (isValid(ghost->x + dx[WEST], ghost->y + dy[WEST], pos))
			return (moove_to(ghost, WEST, pos));
		else if (isValid(ghost->x + dx[SOUTH], ghost->y + dy[SOUTH], pos))
			return (moove_to(ghost, SOUTH, pos));
		else if (isValid(ghost->x + dx[EAST], ghost->y + dy[EAST], pos))
			return (moove_to(ghost, EAST, pos));
		else if (isValid(ghost->x + dx[NORTH], ghost->y + dy[NORTH], pos))
			return (moove_to(ghost, NORTH, pos));
	}
	else if (ghost->dir == EAST)
	{
		if (isValid(ghost->x + dx[SOUTH], ghost->y + dy[SOUTH], pos))
			return (moove_to(ghost, SOUTH, pos));
		else if (isValid(ghost->x + dx[EAST], ghost->y + dy[EAST], pos))
			return (moove_to(ghost, EAST, pos));
		else if (isValid(ghost->x + dx[NORTH], ghost->y + dy[NORTH], pos))
			return (moove_to(ghost, NORTH, pos));
		else if (isValid(ghost->x + dx[WEST], ghost->y + dy[WEST], pos))
			return (moove_to(ghost, WEST, pos));
	}
	else if (ghost->dir == WEST)
	{
		if (isValid(ghost->x + dx[NORTH], ghost->y + dy[NORTH], pos))
			return (moove_to(ghost, NORTH, pos));
		else if (isValid(ghost->x + dx[WEST], ghost->y + dy[WEST], pos))
			return (moove_to(ghost, WEST, pos));
		else if (isValid(ghost->x + dx[SOUTH], ghost->y + dy[SOUTH], pos))
			return (moove_to(ghost, SOUTH, pos));
		else if (isValid(ghost->x + dx[EAST], ghost->y + dy[EAST], pos))
			return (moove_to(ghost, EAST, pos));
	}
}

int	ghosts_are_coming(t_app *app)
{
	ssize_t	i;

	i = -1;
	while (++i < GHOSTS_NUMBER)
        wall_following(&app->ghosts[i], app->pos);
	return (0);
}