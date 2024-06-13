/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:42:35 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/13 10:42:35 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rotate_left_arrows(t_pos *pos)
{
	pos->prev_p_dir_x = pos->p_dir_x;
	pos->p_dir_x = pos->p_dir_x
		* cos(pos->rot_speed_arrows) - pos->p_dir_y
		* sin(pos->rot_speed_arrows);
	pos->p_dir_y = pos->prev_p_dir_x
		* sin(pos->rot_speed_arrows) + pos->p_dir_y
		* cos(pos->rot_speed_arrows);
	pos->prev_surf_x = pos->surf_x;
	pos->surf_x = pos->surf_x * cos(pos->rot_speed_arrows)
		- pos->surf_y * sin(pos->rot_speed_arrows);
	pos->surf_y = pos->prev_surf_x * sin(pos->rot_speed_arrows)
		+ pos->surf_y * cos(pos->rot_speed_arrows);
	return (0);
}

int	rotate_right_arrows(t_pos *pos)
{
	pos->prev_p_dir_x = pos->p_dir_x;
	pos->p_dir_x = pos->p_dir_x * cos(-pos->rot_speed_arrows)
		- pos->p_dir_y * sin(-pos->rot_speed_arrows);
	pos->p_dir_y = pos->prev_p_dir_x * sin(-pos->rot_speed_arrows)
		+ pos->p_dir_y * cos(-pos->rot_speed_arrows);
	pos->prev_surf_x = pos->surf_x;
	pos->surf_x = pos->surf_x * cos(-pos->rot_speed_arrows)
		- pos->surf_y * sin(-pos->rot_speed_arrows);
	pos->surf_y = pos->prev_surf_x * sin(-pos->rot_speed_arrows)
		+ pos->surf_y * cos(-pos->rot_speed_arrows);
	return (0);
}

int	rotate_left_mouse(t_pos *pos)
{
	pos->prev_p_dir_x = pos->p_dir_x;
	pos->p_dir_x = pos->p_dir_x * cos(pos->rot_speed_mouse)
		- pos->p_dir_y * sin(pos->rot_speed_mouse);
	pos->p_dir_y = pos->prev_p_dir_x * sin(pos->rot_speed_mouse)
		+ pos->p_dir_y * cos(pos->rot_speed_mouse);
	pos->prev_surf_x = pos->surf_x;
	pos->surf_x = pos->surf_x * cos(pos->rot_speed_mouse)
		- pos->surf_y * sin(pos->rot_speed_mouse);
	pos->surf_y = pos->prev_surf_x * sin(pos->rot_speed_mouse)
		+ pos->surf_y * cos(pos->rot_speed_mouse);
	return (0);
}

int	rotate_right_mouse(t_pos *pos)
{
	pos->prev_p_dir_x = pos->p_dir_x;
	pos->p_dir_x = pos->p_dir_x * cos(-pos->rot_speed_mouse)
		- pos->p_dir_y * sin(-pos->rot_speed_mouse);
	pos->p_dir_y = pos->prev_p_dir_x * sin(-pos->rot_speed_mouse)
		+ pos->p_dir_y * cos(-pos->rot_speed_mouse);
	pos->prev_surf_x = pos->surf_x;
	pos->surf_x = pos->surf_x * cos(-pos->rot_speed_mouse)
		- pos->surf_y * sin(-pos->rot_speed_mouse);
	pos->surf_y = pos->prev_surf_x * sin(-pos->rot_speed_mouse)
		+ pos->surf_y * cos(-pos->rot_speed_mouse);
	return (0);
}

int	mouse_motion(int x, int y, t_app *app)
{
	int		diff;

	(void) y;
	if (app->pause == true)
		return (0);
	diff = abs(x - (SCREEN_WIDTH / 2));
	app->pos->rot_speed_mouse = ((double) diff) / 1500;
	if (x < SCREEN_WIDTH / 2)
		app->pos->rotate_left_mouse = true;
	else
		app->pos->rotate_left_mouse = false;
	if (x > SCREEN_WIDTH / 2)
		app->pos->rotate_right_mouse = true;
	else
		app->pos->rotate_right_mouse = false;
	return (0);
}
