/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:08:19 by cefuente          #+#    #+#             */
/*   Updated: 2024/05/27 21:52:38 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		new_image(t_app *app)
{
	mlx_destroy_image(app->img->mlx, app->img->img);
	app->img->img = mlx_new_image(app->img->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!app->img->img)
		return (app->err = 1);
	app->img->addr = mlx_get_data_addr(app->img->img, &app->img->bits_per_pixel,
			&app->img->line_length, &app->img->endian);
	if (!app->img->addr)
		return (app->err = 1);
	return (0);
}

int	change_motion_keypress(int key, t_app *app)
{
	if (key == ESC)
	{
		app->err = 3;
		handle_err(app);
	}
	else 
		app->pos->has_mooved = true;
	
	if (key == UP)
		app->pos->motion_up = true;
	if (key == DOWN)
		app->pos->motion_down = true;
	if (key == LEFT)
		app->pos->motion_left = true;
	if (key == RIGHT)
		app->pos->motion_right = true;
	// game_loop(app);
	return (0);
}

int	change_motion_keyrelease(int key, t_app *app)
{
	if (key == UP && app->pos->motion_up == true)
		app->pos->motion_up = false;
	if (key == DOWN && app->pos->motion_down == true)
		app->pos->motion_down = false;
	if (key == LEFT && app->pos->motion_left == true)
		app->pos->motion_left = false;
	if (key == RIGHT && app->pos->motion_right == true)
		app->pos->motion_right = false;

	return (0);	
}

int	motion(t_app *app)
{
	if (app->pos->motion_up == true)
		go_forward(app->pos);
	if (app->pos->motion_down == true)
		go_backward(app->pos);
	if (app->pos->motion_left == true)
		go_left(app->pos);
	if (app->pos->motion_right == true)
		go_right(app->pos);
	return 0;
}

