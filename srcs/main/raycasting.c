/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:42:53 by cefuente          #+#    #+#             */
/*   Updated: 2024/05/30 10:56:30 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
			if (pos->rayDirX < 0)
				pos->wallDir = 'W';
			else
				pos->wallDir = 'E';
		}
		else
		{
			pos->sideDistY += pos->deltaDistY;
			pos->mapY += pos->stepY;
			pos->side = 1;
			if (pos->rayDirY < 0)
				pos->wallDir = 'N';
			else
				pos->wallDir = 'S';
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

t_tex	*get_textures(t_pos *pos, size_t x, t_app *app)
{
	uint32_t	*texture = NULL;
	
	int 	texX;
	double	wallX;
	double	step;
	double	texPos;
	int		texNum = 0;

	if (pos->wallDir == 'N')
		texNum = 0;
	else if (pos->wallDir == 'S')
		texNum = 1;
	else if (pos->wallDir == 'E')
		texNum = 2;
	else if (pos->wallDir == 'W')
		texNum = 3;
	texture = (uint32_t *)pos->tex[texNum].data;

	if (pos->side == 0)
		wallX = pos->posY + pos->perpWallDist * pos->rayDirY;
	else
		wallX = pos->posX + pos->perpWallDist * pos->rayDirX;
	wallX -= floor(wallX);
	texX = (int)(wallX * (double)64);
	if (pos->side == 0 && pos->rayDirX > 0)
		texX = 64 - texX - 1;
	if (pos->side == 1 && pos->rayDirY < 0)
		texX = 64 - texX - 1;
	step = 1.0 * TEX_HEIGHT / pos->lineHeight;
	texPos = (pos->drawStart - SCREEN_HEIGHT * 0.5 + pos->lineHeight * 0.5) * step;
	int	y;	
	y = pos->drawStart;
	yline(app, x, 0, pos->drawStart, BLACK);
	while (y < pos->drawEnd)
	{
		int	texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		uint32_t color = texture[TEX_HEIGHT * texY + texX];
		px_put(app->img, x, y, color);
		y++;
	}
	yline(app, x, pos->drawEnd, SCREEN_HEIGHT, BLACK);

	return (NULL);
}


int	px_screen(t_app *app)
{
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
		xline(app, y, 0, SCREEN_WIDTH, 0xFFFFFF);
	return (0);
}

int	raycasting_loop(t_pos *pos, t_img *img, t_app *app)
{
	size_t	x;
	
	x = 0;
	(void) app;

	while (x < SCREEN_WIDTH)
	{
		get_ray_length(pos, x);
		get_tile_size(pos);
		DDA(pos);
		line_height(pos);
		get_textures(pos, x, app);
		// pos->color = YELLOW;
		// if (pos->wallDir == 'N' || pos->wallDir == 'W')
		// 	pos->color = YELLOW_SIDE;
		// yline(app, x, 0, pos->drawStart, BLUE);
		// yline(app, x, pos->drawStart, pos->drawEnd, pos->color);
		// yline(app, x, pos->drawEnd, SCREEN_HEIGHT, BROWN);
		x++;
    }
	// px_screen(app);
	mlx_put_image_to_window(img->mlx, img->mlx_win,
		img->img, 0, 0);
	return 0;
}

