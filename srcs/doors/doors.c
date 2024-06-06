/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:45:58 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/06 19:41:19 by mpitot           ###   ########.fr       */
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
	else
		pos->pointing_door = none;
}

void	open_door(t_app *app)
{
	if (app->pos->column == SCREEN_WIDTH / 2)
		return ;
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
/*

void	put_open_door(t_app *app)
{

}

void	put_close_door(t_app *app)
{

}
*/
/*

int		put_door_button(t_app *app)
{
	if (app->pos->pointing_door == north)
	{
		if (app->pos->map[(int) app->pos->posX - 1][(int) app->pos->posY] == '2')
			put_open_door(app);
		if (app->pos->map[(int) app->pos->posX - 1][(int) app->pos->posY] == '3')
			put_close_door(app);
	}
	if (app->pos->pointing_door == south)
	{
		if (app->pos->map[(int) app->pos->posX + 1][(int) app->pos->posY] == '2')
			put_open_door(app);
		if (app->pos->map[(int) app->pos->posX + 1][(int) app->pos->posY] == '3')
			put_close_door(app);
	}
	if (app->pos->pointing_door == west)
	{
		if (app->pos->map[(int) app->pos->posX][(int) app->pos->posY - 1] == '2')
			put_open_door(app);
		if (app->pos->map[(int) app->pos->posX][(int) app->pos->posY - 1] == '3')
			put_close_door(app);
	}
	if (app->pos->pointing_door == east)
	{
		if (app->pos->map[(int) app->pos->posX][(int) app->pos->posY + 1] == '2')
			put_open_door(app);
		if (app->pos->map[(int) app->pos->posX][(int) app->pos->posY + 1] == '3')
			put_close_door(app);
	}
	return (1);
}
*/
