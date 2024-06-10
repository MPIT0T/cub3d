/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:45:58 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/10 16:58:44 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	toggle_door(t_app *app, int x, int y)
{
	if (app->pos->map[x][y] == '2')
		app->pos->map[x][y] = '3';
	else if (app->pos->map[x][y] == '3')
		app->pos->map[x][y] = '2';
}

static void	put_butt(t_app *app, const int x, const int y)
{
	if (app->pos->map[x][y] == '2')
	{
		mlx_put_image_to_window(app->img->mlx,
			app->img->mlx_win,
			app->pos->tex[8].img,
			(SCREEN_WIDTH / 2) - 254,
			(SCREEN_HEIGHT) - 120);
	}
	if (app->pos->map[x][y] == '3')
	{
		mlx_put_image_to_window(app->img->mlx,
			app->img->mlx_win,
			app->pos->tex[9].img,
			(SCREEN_WIDTH / 2) - 271,
			(SCREEN_HEIGHT) - 120);
	}
}

void	open_door(t_app *app)
{
	if (app->pos->pointing_door == north)
		toggle_door(app, (int) app->pos->posX - 1, (int) app->pos->posY);
	if (app->pos->pointing_door == south)
		toggle_door(app, (int) app->pos->posX + 1, (int) app->pos->posY);
	if (app->pos->pointing_door == west)
		toggle_door(app, (int) app->pos->posX, (int) app->pos->posY - 1);
	if (app->pos->pointing_door == east)
		toggle_door(app, (int) app->pos->posX, (int) app->pos->posY + 1);
}

int	put_door_button(t_app *app)
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

void	door_dir(t_pos *pos)
{
	double	pos_x;
	double	pos_y;

	modf(pos->posX, &pos_x);
	modf(pos->posY, &pos_y);
	if (pos->mapX == pos_x - 1 && pos->mapY == pos_y)
		pos->pointing_door = north;
	else if (pos->mapX == pos_x + 1 && pos->mapY == pos_y)
		pos->pointing_door = south;
	else if (pos->mapY == pos_y - 1 && pos->mapX == pos_x)
		pos->pointing_door = west;
	else if (pos->mapY == pos_y + 1 && pos->mapX == pos_x)
		pos->pointing_door = east;
	pos->found_door = true;
}
