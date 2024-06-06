/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/06 11:03:57 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int dx[] = {-1, 0, 1, 0}; // UP, RIGHT, DOWN, LEFT
int dy[] = {0, 1, 0, -1}; // UP, RIGHT, DOWN, LEFT

// Function to check if a cell is within bounds and not a wall
int isValid(int x, int y, t_pos *pos) {
    return x >= 0 && x < pos->MAP_HEIGHT && y >= 0 && y < pos->MAP_WIDTH && pos->map[x][y] == '0';
}

t_dir turnRight(t_dir dir) {
    return (dir + 1) % 4;
}

t_dir turnLeft(t_dir dir) {
    return (dir + 3) % 4;
}

static	void	wall_following(t_ghost *ghost, t_pos *pos)
{
	t_dir 	new_dir;
	t_dir	start_dir;
	t_dir	dir;
	int		new_x;
	int		new_y;

	start_dir = RIGHT;
	dir = start_dir;
	new_dir = new_direction(ghost, pos);
	new_x = ghost->x + dx[new_dir];
	new_y = ghost->y + dy[new_dir];
	if (isValid(new_x, new_y, pos))
	{
		// Move to the new direction
		ghost->x = new_x;
		ghost->y = new_y;
		dir = new_dir;
	}
	else
	{
		// Otherwise, keep the wall on the left
		new_dir = dir;
		new_x = ghost->x + dx[new_dir];
		new_y = ghost->y + dy[new_dir];

		if (isValid(new_x, new_y))
		{
			// Move forward
			ghost->x = new_x;
			ghost->y = new_y;
		}
		else
		{
			// Otherwise, turn right
			dir = turnRight(dir);
		}
	}

}

int	ghosts_are_coming(t_app *app)
{
	ssize_t	i;

	i = -1;
	while (++i < GHOSTS_NUMBER)
	{
        if (new_direction(&app->ghosts[i], app->pos)/* && app->pos->map[(int)(app->ghosts[i].y + (app->ghosts[i].dir_y))][(int)(app->ghosts[i].x)] != '1'*/)
        {
			if (app->ghosts[i].dir == N || app->ghosts[i].dir == S)
				app->ghosts[i].y += app->ghosts[i].dir_y * app->ghosts[i].move_speed;
			else 
				app->ghosts[i].x += app->ghosts[i].dir_x * app->ghosts[i].move_speed;
		}
	}
	return (0);
}