/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/06 13:11:40 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int isValid(int x, int y, t_pos *pos)
{
    return (x > 0 && x < pos->MAP_WIDTH && y > 0 && y < pos->MAP_HEIGHT && pos->map[y][x] != '1');
}

t_dir turn(t_dir dir, int choice)
{
    return ((dir + choice) % 4);
}

static	void apply_changes(t_ghost *ghost, t_dir dir)
{
	ghost->x += dx[dir] * ghost->move_speed;
	ghost->y += dy[dir] * ghost->move_speed;
}

static	void	wall_following(t_ghost *ghost, t_pos *pos)
{
	t_dir 	new_dir;
	t_dir	dir;

	dir = UP;
	// printf("base dir is %d\n", dir);
	new_dir = UP;
	// printf("trying forward\n");
	if (isValid(ghost->x + dx[dir] , ghost->y + dy[dir], pos))
		return (apply_changes(ghost, dir));
	// printf("trying left\n");
	new_dir = turn(dir, LEFT);
	if (isValid(ghost->x + dx[new_dir], ghost->y + dy[dir], pos))
		return (apply_changes(ghost, new_dir));
	// printf("trying right\n");
	new_dir = turn(dir, RIGHT);
	if (isValid( ghost->x + dx[new_dir], ghost->y + dy[dir], pos))
		return (apply_changes(ghost, new_dir));
	new_dir = turn(dir, DOWN);
	return (apply_changes(ghost, new_dir));
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