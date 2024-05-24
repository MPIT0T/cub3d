/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_app.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:27:06 by cesar             #+#    #+#             */
/*   Updated: 2024/05/24 10:06:22 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	malloc_app(t_app *app)
{
	app->img = NULL;
	app->img = malloc(sizeof(t_img));
	if (!app->img)
		return (app->err = 1);
	app->pos = NULL;
	app->pos = malloc(sizeof(t_pos));
	if (!app->pos)
		return (app->err = 1);
	return (0);
}

int	initiate_positions(t_app *app)
{
	app->pos->posX = 22;
	app->pos->posY = 12;  //x and y start position
	app->pos->dirX = -1;
	app->pos->dirY = 0; //initial direction vector
	app->pos->planeX = 0;
	app->pos->planeY = 0.66; //the 2d raycaster version of camera plane
	app->pos->time = 0; //time of current frame
	app->pos->oldTime = 0; //time of previous frame
	return (0);
}

int	initiate_mlx(t_app *app)
{
	app->img->mlx = NULL;
	app->img->mlx = mlx_init();
	if (!app->img->mlx)
		return (app->err = 1);
	app->img->mlx_win = NULL;
	app->img->mlx_win = mlx_new_window(app->img->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!app->img->mlx_win)
		return (app->err = 1);
	app->img->img = NULL;
	app->img->img = mlx_new_image(app->img->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!app->img->img)
		return (app->err = 1);
	app->img->addr = NULL;
	app->img->addr = mlx_get_data_addr(app->img->img, &app->img->bits_per_pixel,
			&app->img->line_length, &app->img->endian);
	if (!app->img->addr)
		return (app->err = 1);
	mlx_loop(app->img->mlx);
	return (0);
}

int	construct_app(t_app *app)
{
	if (malloc_app(app) == 1)
		return (app->err);
	if (initiate_positions(app) == 1)
		return (app->err);

	return (0);
}