/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/06 14:56:44 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int isValid(int x, int y, t_pos *pos)
{
    return (x >= 0 && x < pos->MAP_WIDTH && y >= 0 && y < pos->MAP_HEIGHT && pos->map[y][x] != '1');
}

t_dir turn(t_dir dir, int choice)
{
    return ((dir + choice) % 4);
}

static	void apply_changes(t_ghost *ghost, t_dir dir, t_pos *pos)
{
	int	last_x;
	int	last_y;

	last_x = ghost->x;
	last_y = ghost->y;
	ghost->x += dx[dir] * ghost->move_speed;
	ghost->y += dy[dir] * ghost->move_speed;
	printf("went %d\n", dir);
	if ((int)ghost->x != last_x || (int)ghost->y != last_y)
	{
		pos->map[last_y][last_x] = '0';
		pos->map[(int)ghost->y][(int)ghost->x] = 'G';
	}
}

static	void	wall_following(t_ghost *ghost, t_pos *pos)
{
	ssize_t	i;

	i = -1;
	// ghost->dir = UP;
	while (++i < 4)
	{
		if (isValid(ghost->x + dx[ghost->dir], ghost->y + dy[ghost->dir], pos))
		{
			return (apply_changes(ghost, ghost->dir, pos));
		}
		else
		{
			printf("failed to go %d\n", ghost->dir);
			ghost->dir = (ghost->dir + 1) % 4;
		}
	}
}

int	ghosts_are_coming(t_app *app)
{
	ssize_t	i;

	i = -1;
	while (++i < GHOSTS_NUMBER)
	{
        wall_following(&app->ghosts[i], app->pos);
	}
	return (0);
}