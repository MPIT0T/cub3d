/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:45:58 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/05 15:09:54 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		is_door_near(t_app *app)
{
	double	x;
	double	y;

	modf(app->pos->posY, &x);
	modf(app->pos->posX, &y);
	if (x != 0 && app->pos->map[(int) x - 1][(int) y] == '2')
		return (1);
	if (y != 0 && app->pos->map[(int) x][(int) y - 1] == '2')
		return (1);
	if (x != app->pos->MAP_WIDTH && app->pos->map[(int) x + 1][(int) y] == '2')
		return (1);
	if (y != app->pos->MAP_HEIGHT && app->pos->map[(int) x][(int) y + 1] == '2')
		return (1);
	return (0);
}

int		put_door_button(t_app *app)
{
	if (is_door_near(app) || app->pos->pointing_door == true)
	{
//		put_door_button(app);
		write(1, "A", 1);
	}
	return (1);
}
