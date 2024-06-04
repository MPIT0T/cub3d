/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:08:19 by cefuente          #+#    #+#             */
/*   Updated: 2024/06/03 23:59:57 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	clear_px_buffer(uint32_t **px)
{
	ssize_t	y;
	ssize_t	x;

	y = -1;
	x = -1;
	while (++y < SCREEN_HEIGHT)
	{
		while (++x < SCREEN_WIDTH)
			px[y][x] = 0;
	}
}

int		new_image(t_app *app)
{
	mlx_destroy_image(app->img->mlx, app->img->img);
	app->img->img = NULL;
	app->img->addr = NULL;
	app->img->bits_per_pixel = 0;
	app->img->line_length = 0;
	app->img->endian = 0;
	app->img->img = mlx_new_image(app->img->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!app->img->img)
		exit_error(app, EXIT_MLX);
	app->img->addr = mlx_get_data_addr(app->img->img, &app->img->bits_per_pixel,
			&app->img->line_length, &app->img->endian);
	if (!app->img->addr)
		exit_error(app, EXIT_MLX);
	return (0);	
}

int	change_motion_keypress(int key, t_app *app)
{
	if (key == XK_Escape)
		exit_error(app, EXIT_SUCCESS);
	if (app->pos->motion_up == false && key == XK_w)
		app->pos->motion_up = true;
	if (app->pos->motion_down == false && key == XK_s)
		app->pos->motion_down = true;
	if (app->pos->motion_left == false && key == XK_a)
		app->pos->motion_left = true;
	if (app->pos->motion_right == false && key == XK_d)
		app->pos->motion_right = true;
	if (app->pos->moveSpeed == 0.05 && key == XK_Shift_L)
		app->pos->moveSpeed = 0.10;
	return (0);
}

int	change_motion_keyrelease(int key, t_app *app)
{
	if (key == XK_w && app->pos->motion_up == true)
		app->pos->motion_up = false;
	if (key == XK_s && app->pos->motion_down == true)
		app->pos->motion_down = false;
	if (key == XK_a && app->pos->motion_left == true)
		app->pos->motion_left = false;
	if (key == XK_d && app->pos->motion_right == true)
		app->pos->motion_right = false;
	if (key == XK_Shift_L && app->pos->moveSpeed == 0.10)
		app->pos->moveSpeed = 0.05;
	return (0);	
}

int	mouse_motion(int x, int y, t_app *app)
{
	(void) y;
	(void) x;
	(void) app;
	int		diff;

	diff = abs(x - (SCREEN_WIDTH / 2));
	app->pos->rotSpeed = ((double) diff) / 400;
//	app->pos->rotSpeedSave = app->pos->rotSpeed;
//	app->pos->rotSpeed = abs(x - (SCREEN_WIDTH / 2));
	if (x < SCREEN_WIDTH / 2)
		app->pos->rotate_left = true;
	else
	{
		app->pos->rotate_left = false;
//		app->pos->rotSpeed = app->pos->rotSpeedSave;
	}
	if (x > SCREEN_WIDTH / 2)
		app->pos->rotate_right = true;
	else
	{
		app->pos->rotate_right = false;
//		app->pos->rotSpeed = app->pos->rotSpeedSave;
	}
	return (0);
}