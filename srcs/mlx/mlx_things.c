/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:56:47 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/13 12:09:44 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	little_red_cross(t_app *app)
{
	exit_error(app, EXIT_SUCCESS);
	return (0);
}

int	init_hook(t_app *app)
{
	mlx_hook(app->img->mlx_win, FocusOut, 1L << 21, pause_on, app);
	mlx_hook(app->img->mlx_win, 17, 0, little_red_cross, app);
	mlx_hook(app->img->mlx_win, KeyPress, KeyPressMask,
		change_motion_keypress, app);
	mlx_hook(app->img->mlx_win, KeyRelease, KeyReleaseMask,
		change_motion_keyrelease, app);
	mlx_hook(app->img->mlx_win, 6, 1L << 6, mouse_motion, app);
	mlx_loop_hook(app->img->mlx, game_loop, app);
	return (0);
}
