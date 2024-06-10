/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:07:29 by cesar             #+#    #+#             */
/*   Updated: 2024/06/10 16:04:29 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	top_left(t_pos *pos, t_ghost *ghost)
{
	ssize_t	y;
	ssize_t	x;

	x = 0;
	while (x < pos->MAP_WIDTH / 2)
	{
		y = 0;
		while (y < pos->MAP_HEIGHT / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x;
				ghost->y = y;
				pos->map[y][x] = 'G';
				return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	top_right(t_pos *pos, t_ghost *ghost)
{
	ssize_t	y;
	ssize_t	x;

	x = pos->MAP_WIDTH - 1;
	while (x >= pos->MAP_WIDTH / 2)
	{
		y = 0;
		while (y < pos->MAP_HEIGHT / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x;
				ghost->y = y;
				pos->map[y][x] = 'G';
				return (1);
			}
			y++;
		}
		x--;
	}
	return (0);
}

int	bottom_left(t_pos *pos, t_ghost *ghost)
{
	ssize_t	y;
	ssize_t	x;

	x = 0;
	while (x < pos->MAP_WIDTH / 2)
	{
		y = pos->MAP_HEIGHT - 1;
		while (y >= pos->MAP_HEIGHT / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x;
				ghost->y = y;
				pos->map[y][x] = 'G';
				return (1);
			}
			y--;
		}
		x++;
	}
	return (0);
}

int	bottom_right(t_pos *pos, t_ghost *ghost)
{
	ssize_t	y;
	ssize_t	x;

	x = pos->MAP_WIDTH - 1;
	while (x >= pos->MAP_WIDTH / 2)
	{
		y = pos->MAP_HEIGHT - 1;
		while (y >= pos->MAP_HEIGHT / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x;
				ghost->y = y;
				pos->map[y][x] = 'G';
				return (1);
			}
			y--;
		}
		x--;
	}
	return (0);
}

typedef int (*spawn_func)(t_pos *, t_ghost *);

int	spawning_point(t_pos *pos, t_ghost *ghost)
{
	static ssize_t	j = 0;
	spawn_func spawn_funcs[] = {top_left, top_right, bottom_left, bottom_right};

	if (j > 3)
		j = 0;
	spawn_funcs[j](pos, ghost);
	j++;
    return (0);
}

