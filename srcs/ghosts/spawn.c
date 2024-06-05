/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:07:29 by cesar             #+#    #+#             */
/*   Updated: 2024/06/05 10:04:37 by cesar            ###   ########.fr       */
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
				// pos->map[y][x] = 'G';
				return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
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
				// pos->map[y][x] = 'G';
				return (0);
			}
			y++;
		}
		x--;
	}
	return (1);
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
				// pos->map[y][x] = 'G';
				return (0);
			}
			y--;
		}
		x++;
	}
	return (1);
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
				// pos->map[y][x] = 'G';
				return (0);
			}
			y--;
		}
		x--;
	}
	return (1);
}

int	spawning_point(t_pos *pos, t_ghost *ghost, int quarter)
{
	int	err;

	if (quarter == 1)
		err = top_left(pos, ghost);
	if (quarter == 2 || err == 1)
		err = top_right(pos, ghost);
	if (quarter == 3 || err == 1)
		err = bottom_left(pos, ghost);
	if (quarter == 4 || err == 1)
		err = bottom_right(pos, ghost);
	return (0);
}

