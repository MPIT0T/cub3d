 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:34 by cefuente          #+#    #+#             */
/*   Updated: 2024/06/03 19:47:07 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int		go_forward(t_pos *pos)
{
	if (pos->map[(int)(pos->posX + pos->dirX * pos->moveSpeed)][(int)pos->posY] != '1' && pos->map[(int)(pos->posX + pos->dirX * pos->moveSpeed)][(int)pos->posY] != '2')
		pos->posX += pos->dirX * pos->moveSpeed;
	if (pos->map[(int)(pos->posX)][(int)(pos->posY + pos->dirY * pos->moveSpeed)] != '1' && pos->map[(int)(pos->posX)][(int)(pos->posY + pos->dirY * pos->moveSpeed)] != '2')
		pos->posY += pos->dirY * pos->moveSpeed;
	if (pos->map[(int)(pos->posX + pos->dirX * pos->moveSpeed)][(int)pos->posY] == '2') 
		pos->map[(int)(pos->posX + pos->dirX * pos->moveSpeed)][(int)pos->posY] = '3';
	if (pos->map[(int)(pos->posX)][(int)(pos->posY + pos->dirY * pos->moveSpeed)] == '2')
		pos->map[(int)(pos->posX)][(int)(pos->posY + pos->dirY * pos->moveSpeed)] = '3';
	return (0);
}

static int		go_backward(t_pos *pos)
{
	if (pos->map[(int)(pos->posX - pos->dirX * pos->moveSpeed)][(int)pos->posY] != '1')
		pos->posX -= pos->dirX * pos->moveSpeed;
	if (pos->map[(int)pos->posX][(int)(pos->posY - pos->dirY * pos->moveSpeed)] != '1')
		pos->posY -= pos->dirY * pos->moveSpeed;
	return (0);
}

static int		go_left(t_pos *pos)
{
    if (pos->map[(int)(pos->posX - pos->dirY * pos->moveSpeed)][(int)pos->posY] != '1')
        pos->posX -= pos->dirY * pos->moveSpeed;
    if (pos->map[(int)pos->posX][(int)(pos->posY + pos->dirX * pos->moveSpeed)] != '1')
        pos->posY += pos->dirX * pos->moveSpeed;
    return (0);
}

static int		go_right(t_pos *pos)
{
    if (pos->map[(int)(pos->posX + pos->dirY * pos->moveSpeed)][(int)pos->posY] != '1')
        pos->posX += pos->dirY * pos->moveSpeed;
    if (pos->map[(int)pos->posX][(int)(pos->posY - pos->dirX * pos->moveSpeed)] != '1')
        pos->posY -= pos->dirX * pos->moveSpeed;
    return (0);
}

static int	rotate_left_arrows(t_pos *pos)
{
	pos->oldDirX = pos->dirX;
	pos->dirX = pos->dirX * cos(pos->rotSpeedArrows) - pos->dirY * sin(pos->rotSpeedArrows);
	pos->dirY = pos->oldDirX * sin(pos->rotSpeedArrows) + pos->dirY * cos(pos->rotSpeedArrows);
	pos->oldPlaneX = pos->planeX;
	pos->planeX = pos->planeX * cos(pos->rotSpeedArrows) - pos->planeY * sin(pos->rotSpeedArrows);
	pos->planeY = pos->oldPlaneX * sin(pos->rotSpeedArrows) + pos->planeY * cos(pos->rotSpeedArrows);
	return (0);
}

static int	rotate_right_arrows(t_pos *pos)
{
	pos->oldDirX = pos->dirX;
	pos->dirX = pos->dirX * cos(-pos->rotSpeedArrows) - pos->dirY * sin(-pos->rotSpeedArrows);
	pos->dirY = pos->oldDirX * sin(-pos->rotSpeedArrows) + pos->dirY * cos(-pos->rotSpeedArrows);
	pos->oldPlaneX = pos->planeX;
	pos->planeX = pos->planeX * cos(-pos->rotSpeedArrows) - pos->planeY * sin(-pos->rotSpeedArrows);
	pos->planeY = pos->oldPlaneX * sin(-pos->rotSpeedArrows) + pos->planeY * cos(-pos->rotSpeedArrows);
	return (0);
}

static int	rotate_left_mouse(t_pos *pos)
{
	pos->oldDirX = pos->dirX;
	pos->dirX = pos->dirX * cos(pos->rotSpeedMouse) - pos->dirY * sin(pos->rotSpeedMouse);
	pos->dirY = pos->oldDirX * sin(pos->rotSpeedMouse) + pos->dirY * cos(pos->rotSpeedMouse);
	pos->oldPlaneX = pos->planeX;
	pos->planeX = pos->planeX * cos(pos->rotSpeedMouse) - pos->planeY * sin(pos->rotSpeedMouse);
	pos->planeY = pos->oldPlaneX * sin(pos->rotSpeedMouse) + pos->planeY * cos(pos->rotSpeedMouse);
	return (0);
 }

static int	rotate_right_mouse(t_pos *pos)
{
	pos->oldDirX = pos->dirX;
	pos->dirX = pos->dirX * cos(-pos->rotSpeedMouse) - pos->dirY * sin(-pos->rotSpeedMouse);
	pos->dirY = pos->oldDirX * sin(-pos->rotSpeedMouse) + pos->dirY * cos(-pos->rotSpeedMouse);
	pos->oldPlaneX = pos->planeX;
	pos->planeX = pos->planeX * cos(-pos->rotSpeedMouse) - pos->planeY * sin(-pos->rotSpeedMouse);
	pos->planeY = pos->oldPlaneX * sin(-pos->rotSpeedMouse) + pos->planeY * cos(-pos->rotSpeedMouse);
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
