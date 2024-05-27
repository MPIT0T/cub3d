/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:08:19 by cefuente          #+#    #+#             */
/*   Updated: 2024/05/27 16:48:44 by cefuente         ###   ########.fr       */
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
	raycasting_loop(app->pos, app->img, app);
	return (0);
}

int	change_motion_keypress(int key, t_app *app)
{
	if (key == ESC)
		handle_err(app);
	else if (key == UP)
		app->pos->motion_up = true;
	else if (key == DOWN)
		app->pos->motion_down = true;
	else if (key == LEFT)
		app->pos->motion_left = true;
	else if (key == RIGHT)
		app->pos->motion_right = true;
	return (0);
}

int	change_motion_keyrelease(int key, t_app *app)
{
	if (key == UP && app->pos->motion_up == true)
		app->pos->motion_up = false;
	else if (key == DOWN && app->pos->motion_down == true)
		app->pos->motion_down = false;
	else if (key == LEFT && app->pos->motion_left == true)
		app->pos->motion_left = false;
	else if (key == RIGHT && app->pos->motion_right == true)
		app->pos->motion_right = false;
	return (0);	
}

int	key_inputs_loop(t_app *app)
{
	if (app->pos->motion_up)
		go_forward(app->pos);
	else if (app->pos->motion_down)
		go_backward(app->pos);
	else if (app->pos->motion_left)
		go_left(app->pos);
	else if (app->pos->motion_right)
		go_right(app->pos);
	new_image(app);
	return 0;
}

