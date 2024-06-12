/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:10:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/12 15:55:04 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_start_pos(t_app *app, char dir, int x, int y)
{
	if (dir == 'N')
	{
		app->pos->p_dir_x = -1;
		app->pos->surf_y = 0.66;
	}
	if (dir == 'S')
	{
		app->pos->p_dir_x = 1;
		app->pos->surf_y = -0.66;
	}
	if (dir == 'E')
	{
		app->pos->p_dir_y = 1;
		app->pos->surf_x = 0.66;
	}
	if (dir == 'W')
	{
		app->pos->p_dir_y = -1;
		app->pos->surf_x = -0.66;
	}
	app->pos->p_y = x + 0.5;
	app->pos->p_x = y + 0.5;
	app->pos->map[y][x] = '0';
}

static void	set_camera_pos_and_dir(t_app *app)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (app->pos->map[++y])
	{
		x = -1;
		while (app->pos->map[y][++x])
		{
			if (ft_strchr("NSWE", app->pos->map[y][x]))
				set_start_pos(app, app->pos->map[y][x], x, y);
		}
	}
}

int	initiate_positions(t_app *app)
{
	set_camera_pos_and_dir(app);
	app->pos->h = 1;
	app->pos->moveSpeed = 0.05;
	app->pos->rotSpeedArrows = 0.05;
	app->pos->rotSpeedMouse = 0.00;
	app->pos->motion_up = false;
	app->pos->motion_down = false;
	app->pos->rotate_left_arrows = false;
	app->pos->rotate_right_arrows = false;
	app->pos->rotate_right_mouse = false;
	app->pos->rotate_right_mouse = false;
	app->pos->floor_tex = false;
	app->pos->roof_tex = false;
	app->pos->pointing_door = none;
	return (0);
}
