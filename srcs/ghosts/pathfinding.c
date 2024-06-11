/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/11 13:50:05 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};

int isValid(int x, int y, t_pos *pos)
{
    return (x > 0 && x < pos->MAP_WIDTH && y > 0 && y < pos->MAP_HEIGHT && pos->map[y][x] == '0');
}


static	void moove_to(t_ghost *ghost, t_dir dir, t_pos *pos)
{
	// int	last_x;
	// int	last_y;

	// last_x = ghost->x;
	// last_y = ghost->y;
	ghost->x += dx[dir] * ghost->move_speed;
	ghost->y += dy[dir] * ghost->move_speed;
	(void)pos;
	// if ((int)ghost->x != last_x || (int)ghost->y != last_y)
	// {
	// 	pos->map[last_y][last_x] = '0';
	// 	pos->map[(int)ghost->y][(int)ghost->x] = 'G';
	// }
	ghost->dir = dir;
}

static void	wall_following_2(t_ghost *ghost, t_pos *pos)
{
	if (ghost->dir == EAST)
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

static void	wall_following_1(t_ghost *ghost, t_pos *pos)
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