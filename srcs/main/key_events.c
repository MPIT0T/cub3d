/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:08:19 by cefuente          #+#    #+#             */
/*   Updated: 2024/05/27 13:47:01 by cefuente         ###   ########.fr       */
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
	raycasting_loop(app->pos, app->img);
	return (0);
}

int	escaped(int key)
{
	if (key == 65307)
		return (1);
	return (0);
}

int	view_changed(int key, t_app *app)
{
	if (key == 65362) // UP ARROW // 
	{
		if (app->pos->map[(int)(app->pos->posX - app->pos->dirX * app->pos->moveSpeed)][(int)app->pos->posY] == 0)
			app->pos->posX += app->pos->dirX * app->pos->moveSpeed;
		if (app->pos->map[(int)(app->pos->posX)][(int)(app->pos->posY + app->pos->dirY * app->pos->moveSpeed)] == 0)
			app->pos->posY += app->pos->dirY * app->pos->moveSpeed;
		return (1);
	}
	if (key == 65364) // DOWN ARROW //
	{
		if (app->pos->map[(int)(app->pos->posX - app->pos->dirX * app->pos->moveSpeed)][(int)app->pos->posY] == 0)
			app->pos->posX -= app->pos->dirX * app->pos->moveSpeed;
		if (app->pos->map[(int)app->pos->posX][(int)(app->pos->posY - app->pos->dirY * app->pos->moveSpeed)] == 0)
			app->pos->posY -= app->pos->dirY * app->pos->moveSpeed;
		return (1);
	}
	if (key == 65363) // RIGHT ARROW //
	{
		//both camera direction and camera plane must be rotated
		app->pos->oldDirX = app->pos->dirX;
		app->pos->dirX = app->pos->dirX * cos(-app->pos->rotSpeed) - app->pos->dirY * sin(-app->pos->rotSpeed);
		app->pos->dirY = app->pos->oldDirX * sin(-app->pos->rotSpeed) + app->pos->dirY * cos(-app->pos->rotSpeed);
		app->pos->oldPlaneX = app->pos->planeX;
		app->pos->planeX = app->pos->planeX * cos(-app->pos->rotSpeed) - app->pos->planeY * sin(-app->pos->rotSpeed);
		app->pos->planeY = app->pos->oldPlaneX * sin(-app->pos->rotSpeed) + app->pos->planeY * cos(-app->pos->rotSpeed);
		return (1);
	}
	if (key == 65361) // LEFT ARROW //
	{
		//both camera direction and camera plane must be rotated
		app->pos->oldDirX = app->pos->dirX;
		app->pos->dirX = app->pos->dirX * cos(app->pos->rotSpeed) - app->pos->dirY * sin(app->pos->rotSpeed);
		app->pos->dirY = app->pos->oldDirX * sin(app->pos->rotSpeed) + app->pos->dirY * cos(app->pos->rotSpeed);
		app->pos->oldPlaneX = app->pos->planeX;
		app->pos->planeX = app->pos->planeX * cos(app->pos->rotSpeed) - app->pos->planeY * sin(app->pos->rotSpeed);
		app->pos->planeY = app->pos->oldPlaneX * sin(app->pos->rotSpeed) + app->pos->planeY * cos(app->pos->rotSpeed);
		return (1);
	}
	return (0);
}

int	key_events(int key, t_app *app)
{
	if (view_changed(key, app) == 1)
		new_image(app);
	else if (escaped(key) == 1)
	{
		app->err = 3;
		handle_err(app);
	}
	// (void) app;
	// printf("key is %d\n", key);
	return (0);
}