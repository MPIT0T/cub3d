/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:26:17 by cefuente          #+#    #+#             */
/*   Updated: 2024/06/13 12:32:07 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	which_dir(t_pos *pos, char *set, int call)
{
	if (call == 1)
	{
		if (pos->raydir_x < 0)
			pos->wall_dir = set[0];
		else
			pos->wall_dir = set[1];
	}
	else
	{
		if (pos->raydir_y < 0)
			pos->wall_dir = set[0];
		else
			pos->wall_dir = set[1];
	}
}

void	check_door(t_pos *pos)
{
	if (pos->column == SCREEN_WIDTH / 2)
	{
		if (pos->map[pos->map_x][pos->map_y] == '2'
			|| pos->map[pos->map_x][pos->map_y] == '3')
			door_dir(pos);
		else if (pos->found_door == false)
			pos->pointing_door = none;
	}
}
