/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:42:53 by cefuente          #+#    #+#             */
/*   Updated: 2024/05/28 13:13:35 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_ray_length(t_pos *pos, int x)
{
	pos->cameraX = 2 * x / (double)(SCREEN_WIDTH) - 1; //x-coordinate in camera space
	pos->rayDirX = pos->dirX + pos->planeX * pos->cameraX;
	pos->rayDirY = pos->dirY + pos->planeY * pos->cameraX;
	pos->mapX = (int)pos->posX;
	pos->mapY = (int)pos->posY;

	if (pos->rayDirX == 0)
		pos->deltaDistX = 1e30;
	else
		pos->deltaDistX = fabs(1 / pos->rayDirX);
	if (pos->rayDirY == 0)
		pos->deltaDistY = 1e30;
	else
		pos->deltaDistY = fabs(1 / pos->rayDirY);
	pos->hit = 0;
	return (0);
}

static int	get_tile_size(t_pos *pos)
{
	if (pos->rayDirX < 0)
	{
		pos->stepX = -1;
		pos->sideDistX = (pos->posX - pos->mapX) * pos->deltaDistX;
	}
	else
	{
		pos->stepX = 1;
		pos->sideDistX = (pos->mapX + 1.0 - pos->posX) * pos->deltaDistX;
	}
	if (pos->rayDirY < 0)
	{
		pos->stepY = -1;
		pos->sideDistY = (pos->posY - pos->mapY) * pos->deltaDistY;
	}
	else
	{
		pos->stepY = 1;
		pos->sideDistY = (pos->mapY + 1.0 - pos->posY) * pos->deltaDistY;
	}
	return (0);
}

static int	DDA(t_pos *pos)
{
	while (pos->hit == 0)
	{
		if (pos->sideDistX < pos->sideDistY)
		{
			pos->sideDistX += pos->deltaDistX;
			pos->mapX += pos->stepX;
			pos->side = 0;
		}
		else
		{
			pos->sideDistY += pos->deltaDistY;
			pos->mapY += pos->stepY;
			pos->side = 1;
		}
		if (pos->map[pos->mapX][pos->mapY] > 0)
			pos->hit = 1;
	}
	return (0);
}

static int	line_height(t_pos *pos)
{
	if (pos->side == 0)
		pos->perpWallDist = (pos->sideDistX - pos->deltaDistX);
	else
		pos->perpWallDist = (pos->sideDistY - pos->deltaDistY);

	pos->lineHeight = (int)(SCREEN_HEIGHT / pos->perpWallDist);

	pos->drawStart = (-pos->lineHeight * 0.5) + (SCREEN_HEIGHT * 0.5);
	if (pos->drawStart < 0)
		pos->drawStart = 0;
	pos->drawEnd = (pos->lineHeight * 0.5) + (SCREEN_HEIGHT * 0.5);
	if (pos->drawEnd >= SCREEN_HEIGHT)
		pos->drawEnd = SCREEN_HEIGHT - 1;
	return (0);
}

int	raycasting_loop(t_pos *pos, t_img *img, t_app *app)
{
	size_t	x;
	
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		get_ray_length(pos, x);
		get_tile_size(pos);
		DDA(pos);
		line_height(pos);
		pos->color = 0xebab34;
		if (pos->side == 1)
			pos->color = 0xa67924;
		yline(app, x, 0, pos->drawStart, 0x3a8399);
		yline(app, x, pos->drawStart, pos->drawEnd, pos->color);
		yline(app, x, pos->drawEnd, SCREEN_HEIGHT, 0x7a5631);
		x++;
    }
	mlx_put_image_to_window(img->mlx, img->mlx_win,
		img->img, 0, 0);
	return 0;
}

