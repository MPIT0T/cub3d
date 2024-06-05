/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:15:39 by cesar             #+#    #+#             */
/*   Updated: 2024/06/05 18:59:57 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	update_dir(t_ghost *ghost, char dir)
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

static int	try_moove(t_ghost *ghost, t_pos *pos, char dir)
{
	if (dir == 'N' && pos->map[(int)(ghost->y - (1))][(int)(ghost->x)] != '1')
		return (1);
	else if (dir == 'E' && pos->map[(int)(ghost->y)][(int)(ghost->x + (1))] != '1')
		return (1);
	else if (dir == 'S' && pos->map[(int)(ghost->y + (1))][(int)(ghost->x)] != '1')
		return (1);
	else if (dir == 'W' && pos->map[(int)(ghost->y)][(int)(ghost->x - (1))] != '1')
		return (1);
	return (0);
}

static int	new_direction(t_ghost *ghost, t_pos *pos)
{
	char	*dirs_pref;

	if (ghost->dir == 'N' || ghost->dir == 'S')
		dirs_pref = ghost->x_dirs_pref;
	else if (ghost->dir == 'E' || ghost->dir == 'W')
		dirs_pref = ghost->y_dirs_pref;
	if (try_moove(ghost, pos, dirs_pref[0]) == 1)
	{
		ghost->dir = dirs_pref[0];
		return (1);
	}
	else if (try_moove(ghost, pos, dirs_pref[1]) == 1)
	{
		ghost->dir = dirs_pref[1];
		return (1);
	}
	return (0);
}

static int		try_same_direction(t_ghost *ghost, t_pos *pos)
{
	int	prev_y;
	int	prev_x;

	prev_y = (int)ghost->y;
	prev_x = (int)ghost->x;
	if ((ghost->dir == 'N' || ghost->dir == 'S') && pos->map[(int)(ghost->y + (ghost->dir_y))][(int)(ghost->x)] != '1')
	{
		// pos->map[(int)ghost->y][(int)ghost->x] = '0';
		ghost->y += ghost->dir_y * ghost->move_speed;
		if ((int)ghost->y != prev_y)
			ghost->memory[prev_y][(int)ghost->x] = 'X';
		// pos->map[(int)ghost->y][(int)ghost->x] = 'G';
		return (1);
	}
	else if ((ghost->dir == 'E' || ghost->dir == 'W') && pos->map[(int)(ghost->y)][(int)(ghost->x + (ghost->dir_x))] != '1')
	{
		// pos->map[(int)ghost->y][(int)ghost->x] = '0';
		ghost->x += ghost->dir_x * ghost->move_speed;
		if ((int)ghost->x != prev_x)
			ghost->memory[(int)ghost->y][prev_x] = 'X';
		// pos->map[(int)ghost->y][(int)ghost->x] = 'G';
		return (1);
	}
	return (0);
}

int	set_boredom(t_ghost *ghost)
{
	if (ghost->memory[(int)ghost->y][(int)ghost->x] != 'X')
	{
		ghost->bored = false;
		return (0);
	}
	else
	{
		ghost->bored = true;
		return (1);
	}
	
}

char	look_for_new_things(t_ghost *ghost)
{
	if (ghost->memory[(int)(ghost->y - (1))][(int)(ghost->x)] != 'X')
		return ('N');
	else if (ghost->memory[(int)(ghost->y)][(int)(ghost->x + (1))] != 'X')
		return ('E');
	else if (ghost->memory[(int)(ghost->y + (1))][(int)(ghost->x)] != 'X')
		return ('S');
	else if (ghost->memory[(int)(ghost->y)][(int)(ghost->x - (1))] != 'X')
		return ('W');
	return (ghost->dir);
}

int	ghosts_are_coming(t_app *app)
{
	ssize_t	i;

	i = -1;
	while (++i < GHOSTS_NUMBER)
	{
		// if (sees_player(&app->ghosts[i], app->pos))
		// 	update_dir(&app->ghosts[i], app->ghosts[i].dir);
		set_boredom(&app->ghosts[i]);
		if (app->ghosts[i].bored == true)
		{
			app->ghosts[i].dir = look_for_new_things(&app->ghosts[i]);
			update_dir(&app->ghosts[i], app->ghosts[i].dir);
		}
		else if (!try_same_direction(&app->ghosts[i], app->pos))
		{
			if (new_direction(&app->ghosts[i], app->pos))
			{
				update_dir(&app->ghosts[i], app->ghosts[i].dir);
			}
			else
				return (1);
		}
	}
	return (0);
}
