/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:34 by cefuente          #+#    #+#             */
/*   Updated: 2024/06/13 10:25:32 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	go_forward(t_pos *pos)
{
	if (pos->map[(int)(pos->p_x + pos->p_dir_x
			* pos->move_speed)][(int)pos->p_y] != '1'
		&& pos->map[(int)(pos->p_x + pos->p_dir_x
		* pos->move_speed)][(int)pos->p_y] != '2')
		pos->p_x += pos->p_dir_x * pos->move_speed;
	if (pos->map[(int)(pos->p_x)][(int)(pos->p_y + pos->p_dir_y
			* pos->move_speed)] != '1'
		&& pos->map[(int)(pos->p_x)][(int)(pos->p_y + pos->p_dir_y
			* pos->move_speed)] != '2')
		pos->p_y += pos->p_dir_y * pos->move_speed;
	return (0);
}

static int	go_backward(t_pos *pos)
{
	if (pos->map[(int)(pos->p_x - pos->p_dir_x
			* pos->move_speed)][(int)pos->p_y] != '1'
		&& pos->map[(int)(pos->p_x - pos->p_dir_x
			* pos->move_speed)][(int)pos->p_y] != '2')
		pos->p_x -= pos->p_dir_x * pos->move_speed;
	if (pos->map[(int)(pos->p_x)][(int)(pos->p_y - pos->p_dir_y
			* pos->move_speed)] != '1'
		&& pos->map[(int)(pos->p_x - pos->p_dir_x
			* pos->move_speed)][(int)pos->p_y] != '2')
		pos->p_y -= pos->p_dir_y * pos->move_speed;
	return (0);
}

static int	go_left(t_pos *pos)
{
	if (pos->map[(int)(pos->p_x - pos->p_dir_y
			* pos->move_speed)][(int)pos->p_y] != '1'
		&& pos->map[(int)(pos->p_x - pos->p_dir_y
			* pos->move_speed)][(int)pos->p_y] != '2')
		pos->p_x -= pos->p_dir_y * pos->move_speed;
	if (pos->map[(int)pos->p_x][(int)(pos->p_y + pos->p_dir_x
		* pos->move_speed)] != '1'
		&& pos->map[(int)pos->p_x][(int)(pos->p_y + pos->p_dir_x
			* pos->move_speed)] != '2')
		pos->p_y += pos->p_dir_x * pos->move_speed;
	return (0);
}

static int	go_right(t_pos *pos)
{
	if (pos->map[(int)(pos->p_x + pos->p_dir_y
			* pos->move_speed)][(int)pos->p_y] != '1'
		&& pos->map[(int)(pos->p_x + pos->p_dir_y
			* pos->move_speed)][(int)pos->p_y] != '2')
		pos->p_x += pos->p_dir_y * pos->move_speed;
	if (pos->map[(int)pos->p_x][(int)(pos->p_y - pos->p_dir_x
		* pos->move_speed)] != '1'
		&& pos->map[(int)pos->p_x][(int)(pos->p_y - pos->p_dir_x
			* pos->move_speed)] != '2')
		pos->p_y -= pos->p_dir_x * pos->move_speed;
	return (0);
}

static int	rotate_left_arrows(t_pos *pos)
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

static int	rotate_right_arrows(t_pos *pos)
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

static int	rotate_left_mouse(t_pos *pos)
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

static int	rotate_right_mouse(t_pos *pos)
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

int	motion(t_app *app)
{
	if (app->pos->motion_up)
		go_forward(app->pos);
	if (app->pos->motion_down)
		go_backward(app->pos);
	if (app->pos->motion_left)
		go_left(app->pos);
	if (app->pos->motion_right)
		go_right(app->pos);
	if (app->pos->rotate_left_arrows)
		rotate_left_arrows(app->pos);
	if (app->pos->rotate_right_arrows)
		rotate_right_arrows(app->pos);
	if (app->pos->rotate_left_mouse)
		rotate_left_mouse(app->pos);
	if (app->pos->rotate_right_mouse)
		rotate_right_mouse(app->pos);
	return (0);
}
