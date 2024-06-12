/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:10:44 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/12 14:22:23 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_start_pos(t_app *app, char dir, int x, int y)
{
	if (dir == 'N')
	{
		app->pos->dirX = -1;
		app->pos->planeY = 0.66;
	}
	if (dir == 'S')
	{
		app->pos->dirX = 1;
		app->pos->planeY = -0.66;
	}
	if (dir == 'E')
	{
		app->pos->dirY = 1;
		app->pos->planeX = 0.66;
	}
	if (dir == 'W')
	{
		app->pos->dirY = -1;
		app->pos->planeX = -0.66;
	}
	app->pos->posY = x + 0.5;
	app->pos->posX = y + 0.5;
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
	app->pos->time = 0;
	app->pos->oldTime = 0;
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
