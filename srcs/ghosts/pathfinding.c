/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/05 20:24:45 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void update_dir(t_ghost *ghost, char dir)
{
    if (dir == 'N')
    {
        ghost->dir = 'N';
        ghost->dir_x = 0;
        ghost->dir_y = -1;        
    }
    else if (dir == 'E')
    {
        ghost->dir = 'E';
        ghost->dir_x = 1;
        ghost->dir_y = 0;
    }
    else if (dir == 'S')
    {
        ghost->dir = 'S';
        ghost->dir_x = 0;
        ghost->dir_y = 1;
    }
    else if (dir == 'W')
    {
        ghost->dir = 'W';
        ghost->dir_x = -1;
        ghost->dir_y = 0;
    }
}


static int try_move(t_ghost *ghost, t_pos *pos, char dir)
{
    int new_x = (int)ghost->x;
    int new_y = (int)ghost->y;

	printf("trying with %c ", dir);
    if (dir == 'N')
        new_y -= 1;
    else if (dir == 'E')
        new_x += 1;
    else if (dir == 'S')
        new_y += 1;
    else if (dir == 'W')
        new_x -= 1;

    // Check if new position is within bounds and not a wall
    if (new_x >= 0 && new_x < pos->MAP_WIDTH && new_y >= 0 && new_y < pos->MAP_HEIGHT)
	{
		if (pos->map[new_y][new_x] != '1')
		{
			printf("and succeeded\n");
			return 1;
		}
	}
	printf("and failed\n");
    return 0;
}


static int new_direction(t_ghost *ghost, t_pos *pos)
{
	// char *dirs_pref;

	// if (ghost->dir == 'N' || ghost->dir == 'S')
	// 	dirs_pref = ghost->x_dirs_pref;
	// else if (ghost->dir == 'E' || ghost->dir == 'W')
	// 	dirs_pref = ghost->y_dirs_pref;
	printf("ghost moving %c, ", ghost->dir);
	if (try_move(ghost, pos, ghost->dirs_pref[0]) == 1)
	{
		update_dir(ghost, ghost->dirs_pref[0]);
		return 1;
	}
	else if (try_move(ghost, pos, ghost->dirs_pref[1]) == 1)
	{
		update_dir(ghost, ghost->dirs_pref[1]);
		return 1;
	}
	else if (try_move(ghost, pos, ghost->dirs_pref[2]) == 1)
	{
		update_dir(ghost, ghost->dirs_pref[2]);
		return 1;
	}
	else if (try_move(ghost, pos, ghost->dirs_pref[3]) == 1)
	{
		update_dir(ghost, ghost->dirs_pref[3]);
		return 1;
	}
	return 0;
}


int	ghosts_are_coming(t_app *app)
{
	ssize_t	i;

	i = -1;
	while (++i < GHOSTS_NUMBER)
	{
		// if (sees_player(&app->ghosts[i], app->pos))
		// 	update_dir(&app->ghosts[i], app->ghosts[i].dir);
        if (new_direction(&app->ghosts[i], app->pos)/* && app->pos->map[(int)(app->ghosts[i].y + (app->ghosts[i].dir_y))][(int)(app->ghosts[i].x)] != '1'*/)
        {
            // Move ghost in the new direction
			if (app->ghosts[i].dir == 'N' || app->ghosts[i].dir == 'S')
				app->ghosts[i].y += app->ghosts[i].dir_y * app->ghosts[i].move_speed;
			else 
				app->ghosts[i].x += app->ghosts[i].dir_x * app->ghosts[i].move_speed;
		}
	}
	return (0);
}