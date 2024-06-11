/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/11 14:40:46 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};

int isValid(int x, int y, t_pos *pos)
{
    return (x > 1 && x < pos->MAP_WIDTH - 1 && y > 1
		&& y < pos->MAP_HEIGHT - 1 && (pos->map[y][x] == '0' || pos->map[y][x] == 'G'));
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
		if (isValid(ghost->x + dx[SOUTH], ghost->y + dy[SOUTH], pos))
			return (moove_to(ghost, SOUTH));
		else if (isValid(ghost->x + dx[EAST], ghost->y + dy[EAST], pos))
			return (moove_to(ghost, EAST));
		else if (isValid(ghost->x + dx[NORTH], ghost->y + dy[NORTH], pos))
			return (moove_to(ghost, NORTH));
		else if (isValid(ghost->x + dx[WEST], ghost->y + dy[WEST], pos))
			return (moove_to(ghost, WEST));
	}
	else if (ghost->dir == WEST)
	{
		if (isValid(ghost->x + dx[NORTH], ghost->y + dy[NORTH], pos))
			return (moove_to(ghost, NORTH));
		else if (isValid(ghost->x + dx[WEST], ghost->y + dy[WEST], pos))
			return (moove_to(ghost, WEST));
		else if (isValid(ghost->x + dx[SOUTH], ghost->y + dy[SOUTH], pos))
			return (moove_to(ghost, SOUTH));
		else if (isValid(ghost->x + dx[EAST], ghost->y + dy[EAST], pos))
			return (moove_to(ghost, EAST));
	}
}

static void	wall_following_1(t_ghost *ghost, t_pos *pos)
{
	if (ghost->dir == NORTH)
	{
		if (isValid(ghost->x + dx[EAST], ghost->y + dy[EAST], pos))
			return (moove_to(ghost, EAST));
		else if (isValid(ghost->x + dx[NORTH], ghost->y + dy[NORTH], pos))
			return (moove_to(ghost, NORTH));
		else if (isValid(ghost->x + dx[WEST], ghost->y + dy[WEST], pos))
			return (moove_to(ghost, WEST));
		else if (isValid(ghost->x + dx[SOUTH], ghost->y + dy[SOUTH], pos))
			return (moove_to(ghost, SOUTH));
	}
	else if (ghost->dir == SOUTH)
	{
		if (isValid(ghost->x + dx[WEST], ghost->y + dy[WEST], pos))
			return (moove_to(ghost, WEST));
		else if (isValid(ghost->x + dx[SOUTH], ghost->y + dy[SOUTH], pos))
			return (moove_to(ghost, SOUTH));
		else if (isValid(ghost->x + dx[EAST], ghost->y + dy[EAST], pos))
			return (moove_to(ghost, EAST));
		else if (isValid(ghost->x + dx[NORTH], ghost->y + dy[NORTH], pos))
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