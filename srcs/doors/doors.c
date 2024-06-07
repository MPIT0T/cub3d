/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:45:58 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/07 18:16:25 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	door_dir(t_pos *pos)
{
	double	posX;
	double	posY;

	modf(pos->posX, &posX);
	modf(pos->posY, &posY);
	if (pos->mapX == posX - 1 && pos->mapY == posY)
		pos->pointing_door = north;
	else if (pos->mapX == posX + 1 && pos->mapY == posY)
		pos->pointing_door = south;
	else if (pos->mapY == posY - 1 && pos->mapX == posX)
		pos->pointing_door = west;
	else if (pos->mapY == posY + 1 && pos->mapX == posX)
		pos->pointing_door = east;
	pos->found_door = true;
}

void	open_door(t_app *app)
{
	if (app->pos->pointing_door == north)
	{
		if (app->pos->map[(int) app->pos->posX - 1][(int) app->pos->posY] == '2')
			app->pos->map[(int) app->pos->posX - 1][(int) app->pos->posY] = '3';
		else if (app->pos->map[(int) app->pos->posX - 1][(int) app->pos->posY] == '3')
			app->pos->map[(int) app->pos->posX - 1][(int) app->pos->posY] = '2';
	}
	if (app->pos->pointing_door == south)
	{
		if (app->pos->map[(int) app->pos->posX + 1][(int) app->pos->posY] == '2')
			app->pos->map[(int) app->pos->posX + 1][(int) app->pos->posY] = '3';
		else if (app->pos->map[(int) app->pos->posX + 1][(int) app->pos->posY] == '3')
			app->pos->map[(int) app->pos->posX + 1][(int) app->pos->posY] = '2';
	}
	if (app->pos->pointing_door == west)
	{
		if (app->pos->map[(int) app->pos->posX][(int) app->pos->posY - 1] == '2')
			app->pos->map[(int) app->pos->posX][(int) app->pos->posY - 1] = '3';
		else if (app->pos->map[(int) app->pos->posX][(int) app->pos->posY - 1] == '3')
			app->pos->map[(int) app->pos->posX][(int) app->pos->posY - 1] = '2';
	}
	if (app->pos->pointing_door == east)
	{
		if (app->pos->map[(int) app->pos->posX][(int) app->pos->posY + 1] == '2')
			app->pos->map[(int) app->pos->posX][(int) app->pos->posY + 1] = '3';
		else if (app->pos->map[(int) app->pos->posX][(int) app->pos->posY + 1] == '3')
			app->pos->map[(int) app->pos->posX][(int) app->pos->posY + 1] = '2';
	}
}

void	put_open_door(t_app *app)
{
	uint32_t	color;
	int			startX;
	int			startY;
	int			texX;
	int			texY;

	startX = (SCREEN_WIDTH / 2) - 254;
	startY = (SCREEN_HEIGHT) - 120;
	texY = 0;
	while (texY < 60)
	{
		texX = 0;
		while (texX < 508)
		{
			color = app->pos->tex[8].data[texY * 508 + texX];
			px_put(app->img, startX + texX, startY + texY, color);
			texX++;
		}
		texY++;
	}
}

void	put_close_door(t_app *app)
{
	uint32_t	color;
	int			startX;
	int			startY;
	int			texX;
	int			texY;

	startX = (SCREEN_WIDTH / 2) - 271;
	startY = (SCREEN_HEIGHT) - 120;
	texY = 0;
	while (texY < 60)
	{
		texX = 0;
		while (texX < 543)
		{
			color = (uint32_t) app->pos->tex[9].data[(texY * 543) + texX];
			px_put(app->img, startX + texX, startY + texY, color);
			texX++;
		}
		texY++;
	}
}

void	put_butt(t_app *app, int x, int y)
{
	if (app->pos->map[x][y] == '2')
		put_close_door(app);
	if (app->pos->map[x][y] == '3')
		put_close_door(app);

}

int		put_door_button(t_app *app)
{
	if (app->pos->pointing_door == north)
		put_butt(app, (int) app->pos->posX - 1, (int) app->pos->posY);
	if (app->pos->pointing_door == south)
		put_butt(app, (int) app->pos->posX + 1, (int) app->pos->posY);
	if (app->pos->pointing_door == west)
		put_butt(app, (int) app->pos->posX, (int) app->pos->posY - 1);
	if (app->pos->pointing_door == east)
		put_butt(app, (int) app->pos->posX, (int) app->pos->posY + 1);
	return (0);
}
