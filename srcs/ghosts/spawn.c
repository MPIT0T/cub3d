/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:07:29 by cesar             #+#    #+#             */
/*   Updated: 2024/06/19 09:42:03 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	top_left(t_pos *pos, t_ghost *ghost)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < pos->map_height / 2)
	{
		x = 0;
		while (x < pos->map_width / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x + 0.5;
				ghost->y = y + 0.5;
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
	size_t	y;
	size_t	x;

	y = 0;
	while (y < pos->map_height / 2)
	{
		x = pos->map_width - 1;
		while (x >= pos->map_width / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x + 0.5;
				ghost->y = y + 0.5;
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
	size_t	y;
	size_t	x;

	y = pos->map_height - 1;
	while (y >= pos->map_height / 2)
	{
		x = 0;
		while (x < pos->map_width / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x + 0.5;
				ghost->y = y + 0.5;
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
	size_t	y;
	size_t	x;

	y = pos->map_height - 1;
	while (y >= pos->map_height / 2)
	{
		x = pos->map_width - 1;
		while (x >= pos->map_width / 2)
		{
			if (pos->map[y][x] == '0')
			{
				ghost->x = x + 0.5;
				ghost->y = y + 0.5;
				return (1);
			}
			x--;
		}
		y--;
	}
	return (0);
}

int	spawning_point(t_pos *pos, t_ghost *ghost)
{
	static ssize_t		j = 0;
	static t_spawn_func	spawn_funcs[]
		= {top_left, top_right, bottom_left, bottom_right};

	if (j > 3)
		j = 0;
	spawn_funcs[j](pos, ghost);
	j++;
	return (0);
}
