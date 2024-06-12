/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:07:29 by cesar             #+#    #+#             */
/*   Updated: 2024/06/12 12:39:42 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	top_left(t_pos *pos, t_ghost *ghost)
{
	ssize_t	y;
	ssize_t	x;

	y = 0;
	while (y < pos->MAP_HEIGHT / 2)
	{
		x = 0;
		while (x < pos->MAP_WIDTH / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x;
				ghost->y = y;
				printf("top left at [%f][%f]\n", ghost->y, ghost->x);

				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	top_right(t_pos *pos, t_ghost *ghost)
{
	ssize_t	y;
	ssize_t	x;

	y = 0;
	while (y < pos->MAP_HEIGHT / 2)
	{
		x = pos->MAP_WIDTH - 1;
		while (x >= pos->MAP_WIDTH / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x;
				ghost->y = y;
				// pos->map[y][x] = 'G';
				printf("top right at [%f][%f]\n", ghost->y, ghost->x);

				return (1);
			}
			x--;
		}
		y++;
	}
	return (0);
}

int	bottom_left(t_pos *pos, t_ghost *ghost)
{
	ssize_t	y;
	ssize_t	x;

	y = pos->MAP_HEIGHT - 1;
	while (y >= pos->MAP_HEIGHT / 2)
	{
		x = 0;
		while (x < pos->MAP_WIDTH / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x;
				ghost->y = y;
				// pos->map[y][x] = 'G';
				printf("bottom left at [%f][%f]\n", ghost->y, ghost->x);

				return (1);
			}
			x++;
		}
		y--;
	}
	return (0);
}

int	bottom_right(t_pos *pos, t_ghost *ghost)
{
	ssize_t	y;
	ssize_t	x;

	y = pos->MAP_HEIGHT - 1;
	while (y >= pos->MAP_HEIGHT / 2)
	{
		x = pos->MAP_WIDTH - 1;
		while (x >= pos->MAP_WIDTH / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x;
				ghost->y = y;
				printf("bottom right at [%f][%f]\n", ghost->y, ghost->x);
				// pos->map[y][x] = 'G';
				return (1);
			}
			x--;
		}
		y--;
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

