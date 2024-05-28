/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_app.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:27:06 by cesar             #+#    #+#             */
/*   Updated: 2024/05/27 18:55:47 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	malloc_app(t_app *app)
{
	app->img = NULL;
	app->img = malloc(sizeof(t_img));
	if (!app->img)
		return (app->err = ALLOC_FAILURE);
	app->pos = NULL;
	app->pos = malloc(sizeof(t_pos));
	if (!app->pos)
		return (app->err = ALLOC_FAILURE);
	return (0);
}

int	initiate_positions(t_app *app)
{
	app->pos->posX = 22;//x and y start position
	app->pos->posY = 12;  
	app->pos->dirX = -1;//initial direction vector
	app->pos->dirY = 0; 
	app->pos->planeX = 0;//the 2d raycaster version of camera plane
	app->pos->planeY = 0.66; 
	app->pos->time = 0; //time of current frame
	app->pos->oldTime = 0; //time of previous frame
	app->pos->h = 1;
	app->pos->moveSpeed = 0.1;
	app->pos->rotSpeed = 0.1;
	app->pos->has_mooved = false;
	return (0);
}

int	initiate_mlx(t_app *app)
{
	app->img->mlx = NULL;
	app->img->mlx = mlx_init();
	if (!app->img->mlx)
		return (app->err = ALLOC_FAILURE);
	app->img->mlx_win = NULL;
	app->img->mlx_win = mlx_new_window(app->img->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!app->img->mlx_win)
		return (app->err = ALLOC_FAILURE);
	app->img->img = NULL;
	app->img->img = mlx_new_image(app->img->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!app->img->img)
		return (app->err = ALLOC_FAILURE);
	app->img->addr = NULL;
	app->img->addr = mlx_get_data_addr(app->img->img, &app->img->bits_per_pixel,
			&app->img->line_length, &app->img->endian);
	if (!app->img->addr)
		return (app->err = ALLOC_FAILURE);
	return (0);
}

int	construct_app(t_app *app)
{
	if (malloc_app(app) == ALLOC_FAILURE)
		return (app->err);
	if (initiate_positions(app) == ALLOC_FAILURE)
		return (app->err);

	return (0);
}