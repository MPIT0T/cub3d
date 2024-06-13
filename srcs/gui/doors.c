/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:45:58 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/13 09:14:52 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	__toggle_door(t_app *app, int x, int y)
{
	if (app->pos->map[x][y] == '2')
		app->pos->map[x][y] = '3';
	else if (app->pos->map[x][y] == '3')
		app->pos->map[x][y] = '2';
}

static void	__put_butt(t_app *app, int x, int y)
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
		__toggle_door(app, (int) app->pos->p_x - 1, (int) app->pos->p_y);
	if (app->pos->pointing_door == south)
		__toggle_door(app, (int) app->pos->p_x + 1, (int) app->pos->p_y);
	if (app->pos->pointing_door == west)
		__toggle_door(app, (int) app->pos->p_x, (int) app->pos->p_y - 1);
	if (app->pos->pointing_door == east)
		__toggle_door(app, (int) app->pos->p_x, (int) app->pos->p_y + 1);
}

int	put_door_button(t_app *app)
{
	if (app->pos->pointing_door == north)
		__put_butt(app, (int) app->pos->p_x - 1, (int) app->pos->p_y);
	if (app->pos->pointing_door == south)
		__put_butt(app, (int) app->pos->p_x + 1, (int) app->pos->p_y);
	if (app->pos->pointing_door == west)
		__put_butt(app, (int) app->pos->p_x, (int) app->pos->p_y - 1);
	if (app->pos->pointing_door == east)
		__put_butt(app, (int) app->pos->p_x, (int) app->pos->p_y + 1);
	return (0);
}

void	door_dir(t_pos *pos)
{
	double	pos_x;
	double	pos_y;

	modf(pos->p_x, &pos_x);
	modf(pos->p_y, &pos_y);
	if (pos->map_x == pos_x - 1 && pos->map_y == pos_y)
		pos->pointing_door = north;
	else if (pos->map_x == pos_x + 1 && pos->map_y == pos_y)
		pos->pointing_door = south;
	else if (pos->map_y == pos_y - 1 && pos->map_x == pos_x)
		pos->pointing_door = west;
	else if (pos->map_y == pos_y + 1 && pos->map_x == pos_x)
		pos->pointing_door = east;
	pos->found_door = true;
}
