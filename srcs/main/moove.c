/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:34 by cefuente          #+#    #+#             */
/*   Updated: 2024/06/12 15:55:04 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int		go_forward(t_pos *pos)
{
	if (pos->map[(int)(pos->p_x + pos->p_dir_x * pos->moveSpeed)][(int)pos->p_y] != '1' && pos->map[(int)(pos->p_x + pos->p_dir_x * pos->moveSpeed)][(int)pos->p_y] != '2')
		pos->p_x += pos->p_dir_x * pos->moveSpeed;
	if (pos->map[(int)(pos->p_x)][(int)(pos->p_y + pos->p_dir_y * pos->moveSpeed)] != '1' && pos->map[(int)(pos->p_x)][(int)(pos->p_y + pos->p_dir_y * pos->moveSpeed)] != '2')
		pos->p_y += pos->p_dir_y * pos->moveSpeed;
	return (0);
}

static int		go_backward(t_pos *pos)
{
	if (pos->map[(int)(pos->p_x - pos->p_dir_x * pos->moveSpeed)][(int)pos->p_y] != '1' && pos->map[(int)(pos->p_x - pos->p_dir_x * pos->moveSpeed)][(int)pos->p_y] != '2')
		pos->p_x -= pos->p_dir_x * pos->moveSpeed;
	if (pos->map[(int)(pos->p_x)][(int)(pos->p_y - pos->p_dir_y * pos->moveSpeed)] != '1' && pos->map[(int)(pos->p_x - pos->p_dir_x * pos->moveSpeed)][(int)pos->p_y] != '2')
		pos->p_y -= pos->p_dir_y * pos->moveSpeed;
	return (0);
}

static int		go_left(t_pos *pos)
{
    if (pos->map[(int)(pos->p_x - pos->p_dir_y * pos->moveSpeed)][(int)pos->p_y] != '1' && pos->map[(int)(pos->p_x - pos->p_dir_y * pos->moveSpeed)][(int)pos->p_y] != '2')
        pos->p_x -= pos->p_dir_y * pos->moveSpeed;
    if (pos->map[(int)pos->p_x][(int)(pos->p_y + pos->p_dir_x * pos->moveSpeed)] != '1' && pos->map[(int)pos->p_x][(int)(pos->p_y + pos->p_dir_x * pos->moveSpeed)] != '2')
        pos->p_y += pos->p_dir_x * pos->moveSpeed;
    return (0);
}

static int		go_right(t_pos *pos)
{
    if (pos->map[(int)(pos->p_x + pos->p_dir_y * pos->moveSpeed)][(int)pos->p_y] != '1' && pos->map[(int)(pos->p_x + pos->p_dir_y * pos->moveSpeed)][(int)pos->p_y] != '2')
        pos->p_x += pos->p_dir_y * pos->moveSpeed;
    if (pos->map[(int)pos->p_x][(int)(pos->p_y - pos->p_dir_x * pos->moveSpeed)] != '1' && pos->map[(int)pos->p_x][(int)(pos->p_y - pos->p_dir_x * pos->moveSpeed)] != '2')
        pos->p_y -= pos->p_dir_x * pos->moveSpeed;
    return (0);
}

static int	rotate_left_arrows(t_pos *pos)
{
	pos->oldDirX = pos->p_dir_x;
	pos->p_dir_x = pos->p_dir_x * cos(pos->rotSpeedArrows) - pos->p_dir_y * sin(pos->rotSpeedArrows);
	pos->p_dir_y = pos->oldDirX * sin(pos->rotSpeedArrows) + pos->p_dir_y * cos(pos->rotSpeedArrows);
	pos->oldPlaneX = pos->surf_x;
	pos->surf_x = pos->surf_x * cos(pos->rotSpeedArrows) - pos->surf_y * sin(pos->rotSpeedArrows);
	pos->surf_y = pos->oldPlaneX * sin(pos->rotSpeedArrows) + pos->surf_y * cos(pos->rotSpeedArrows);
	return (0);
}

static int	rotate_right_arrows(t_pos *pos)
{
	pos->oldDirX = pos->p_dir_x;
	pos->p_dir_x = pos->p_dir_x * cos(-pos->rotSpeedArrows) - pos->p_dir_y * sin(-pos->rotSpeedArrows);
	pos->p_dir_y = pos->oldDirX * sin(-pos->rotSpeedArrows) + pos->p_dir_y * cos(-pos->rotSpeedArrows);
	pos->oldPlaneX = pos->surf_x;
	pos->surf_x = pos->surf_x * cos(-pos->rotSpeedArrows) - pos->surf_y * sin(-pos->rotSpeedArrows);
	pos->surf_y = pos->oldPlaneX * sin(-pos->rotSpeedArrows) + pos->surf_y * cos(-pos->rotSpeedArrows);
	return (0);
}

static int	rotate_left_mouse(t_pos *pos)
{
	pos->oldDirX = pos->p_dir_x;
	pos->p_dir_x = pos->p_dir_x * cos(pos->rotSpeedMouse) - pos->p_dir_y * sin(pos->rotSpeedMouse);
	pos->p_dir_y = pos->oldDirX * sin(pos->rotSpeedMouse) + pos->p_dir_y * cos(pos->rotSpeedMouse);
	pos->oldPlaneX = pos->surf_x;
	pos->surf_x = pos->surf_x * cos(pos->rotSpeedMouse) - pos->surf_y * sin(pos->rotSpeedMouse);
	pos->surf_y = pos->oldPlaneX * sin(pos->rotSpeedMouse) + pos->surf_y * cos(pos->rotSpeedMouse);
	return (0);
 }

static int	rotate_right_mouse(t_pos *pos)
{
	pos->oldDirX = pos->p_dir_x;
	pos->p_dir_x = pos->p_dir_x * cos(-pos->rotSpeedMouse) - pos->p_dir_y * sin(-pos->rotSpeedMouse);
	pos->p_dir_y = pos->oldDirX * sin(-pos->rotSpeedMouse) + pos->p_dir_y * cos(-pos->rotSpeedMouse);
	pos->oldPlaneX = pos->surf_x;
	pos->surf_x = pos->surf_x * cos(-pos->rotSpeedMouse) - pos->surf_y * sin(-pos->rotSpeedMouse);
	pos->surf_y = pos->oldPlaneX * sin(-pos->rotSpeedMouse) + pos->surf_y * cos(-pos->rotSpeedMouse);
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
