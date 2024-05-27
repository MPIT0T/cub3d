/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:28:36 by cesar             #+#    #+#             */
/*   Updated: 2024/05/26 10:48:25 by cesar            ###   ########.fr       */
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
	printf("hey");

	size_t	w = MAP_WIDTH;
	size_t	x = 0;
	while (x < w)
	{
		//calculate ray position and direction
		pos->cameraX = 2 * x / (double)(w) - 1; //x-coordinate in camera space
		pos->rayDirX = pos->dirX + pos->planeX * pos->cameraX;
		pos->rayDirY = pos->dirY + pos->planeY * pos->cameraX;
		x++;

		pos->mapX = (int)pos->posX;
		pos->mapY = (int)pos->posY;

		//length of ray from one x or y-side to next x or y-side
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
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (pos->side == 0)
			pos->perpWallDist = (pos->sideDistX - pos->deltaDistX);
		else
			pos->perpWallDist = (pos->sideDistY - pos->deltaDistY);

		//Calculate height of line to draw on screen
		pos->lineHeight = (int)(pos->h / pos->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		pos->drawStart = -(pos->lineHeight) / 2 + pos->h / 2;
		if(pos->drawStart < 0)
			pos->drawStart = 0;
		pos->drawEnd = pos->lineHeight / 2 + pos->h / 2;
		if (pos->drawEnd >= pos->h)
			pos->drawEnd = pos->h - 1;

		pos->color = 0xFF0000;
		//give x and y sides different brightness
		if (pos->side == 1)
			pos->color = pos->color / 2;

		//draw the pixels of the stripe as a vertical line
		vline(img, x, pos->drawStart, pos->drawEnd, pos->color);
    }
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
	mlx_loop(app.img->mlx);

}