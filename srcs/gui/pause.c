/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:09:24 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/13 17:08:47 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	pause_on(t_app *app)
{
	mlx_mouse_show(app->img->mlx, app->img->mlx_win);
	app->pause = true;
	return (0);
}

int	pause_off(t_app *app)
{
	app->pause = false;
	return (0);
}

int	pause_toggle(t_app *app)
{
	if (app->pause == true)
	{
		app->pause = false;
		mlx_mouse_hide(app->img->mlx, app->img->mlx_win);
	}
	else if (app->pause == false)
	{
		app->pause = true;
		mlx_mouse_show(app->img->mlx, app->img->mlx_win);
		app->pos->rotate_left_mouse = false;
		app->pos->rotate_right_mouse = false;
		app->pos->rotate_left_arrows = false;
		app->pos->rotate_right_arrows = false;
	}
	return (0);
}

int	put_pause_menu(t_app *app)
{
	if (app->pause == false)
		return (0);
	// mlx_put_image_to_window(app->img->mlx, app->img->mlx_win, &app->pos->tex[10], 0, 0);
	//TODO put pause menu image
	return (1);
}
