 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:34 by cefuente          #+#    #+#             */
/*   Updated: 2024/05/30 15:34:42 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int		go_forward(t_pos *pos)
{
	if (pos->map[(int)(pos->posX + pos->dirX * pos->moveSpeed)][(int)pos->posY] != '1')
		pos->posX += pos->dirX * pos->moveSpeed;
	if (pos->map[(int)(pos->posX)][(int)(pos->posY + pos->dirY * pos->moveSpeed)] != '1')
		pos->posY += pos->dirY * pos->moveSpeed;
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

static int	rotate_left(t_pos *pos)
{
	pos->oldDirX = pos->dirX;
	pos->dirX = pos->dirX * cos(pos->rotSpeed) - pos->dirY * sin(pos->rotSpeed);
	pos->dirY = pos->oldDirX * sin(pos->rotSpeed) + pos->dirY * cos(pos->rotSpeed);
	pos->oldPlaneX = pos->planeX;
	pos->planeX = pos->planeX * cos(pos->rotSpeed) - pos->planeY * sin(pos->rotSpeed);
	pos->planeY = pos->oldPlaneX * sin(pos->rotSpeed) + pos->planeY * cos(pos->rotSpeed);
	return (0);
}

static int	rotate_right(t_pos *pos)
{
	pos->oldDirX = pos->dirX;
	pos->dirX = pos->dirX * cos(-pos->rotSpeed) - pos->dirY * sin(-pos->rotSpeed);
	pos->dirY = pos->oldDirX * sin(-pos->rotSpeed) + pos->dirY * cos(-pos->rotSpeed);
	pos->oldPlaneX = pos->planeX;
	pos->planeX = pos->planeX * cos(-pos->rotSpeed) - pos->planeY * sin(-pos->rotSpeed);
	pos->planeY = pos->oldPlaneX * sin(-pos->rotSpeed) + pos->planeY * cos(-pos->rotSpeed);
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
	if (app->pos->rotate_left)
		rotate_left(app->pos);
	if (app->pos->rotate_right)
		rotate_right(app->pos);
	return (0);
}
