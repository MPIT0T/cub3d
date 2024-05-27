/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:28:36 by cesar             #+#    #+#             */
/*   Updated: 2024/05/27 13:53:34 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_map(t_pos *pos, int *err)
{
	(void) err;
	int	tmp[MAP_WIDTH][MAP_HEIGHT] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
    for(int i = 0; i < MAP_WIDTH; i++)
    {
        for(int j = 0; j < MAP_HEIGHT; j++)
        {
            pos->map[i][j] = tmp[i][j];
        }
    }
	return (0);
}

int	raycasting_loop(t_pos *pos, t_img *img)
{
	size_t	x = 0;
	while (x < SCREEN_WIDTH)
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

		//calculate step and initial sideDist
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
		//perform DDA
		while (pos->hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
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
			//Check if ray has hit a wall
			if (pos->map[pos->mapX][pos->mapY] > 0)
				pos->hit = 1;
		}
		if (pos->side == 0)
			pos->perpWallDist = (pos->sideDistX - pos->deltaDistX);
		else
			pos->perpWallDist = (pos->sideDistY - pos->deltaDistY);

		pos->lineHeight = (int)(SCREEN_HEIGHT / pos->perpWallDist);

		pos->drawStart = (-pos->lineHeight / 2) + (SCREEN_HEIGHT / 2);
		if (pos->drawStart < 0)
			pos->drawStart = 0;
		pos->drawEnd = (pos->lineHeight / 2) + (SCREEN_HEIGHT / 2);
		if (pos->drawEnd >= SCREEN_HEIGHT)
			pos->drawEnd = SCREEN_HEIGHT - 1;
		pos->color = 0xFF0000;
		if (pos->side == 1)
			pos->color = 0x990000;
		yline(img, x, pos->drawStart, pos->drawEnd, pos->color);
		x++;
    }

	mlx_put_image_to_window(img->mlx, img->mlx_win,
		img->img, 0, 0);
	return 0;
}

int main(int argc, char **argv)
{
	t_app	app;

	app.err = 0;
	(void) argc;
	(void) argv;
	if (construct_app(&app) == 1)
		return (handle_err(&app));
	if (get_map(app.pos, &app.err) == 1)
		return (handle_err(&app));
	if (initiate_mlx(&app) == 1)
		return (handle_err(&app));
	raycasting_loop(app.pos, app.img);
	mlx_hook(app.img->mlx_win, 2, 1L << 0, key_events, &app);
	mlx_loop(app.img->mlx);
}