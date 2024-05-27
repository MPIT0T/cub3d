/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:34 by cefuente          #+#    #+#             */
/*   Updated: 2024/05/27 16:07:13 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		go_forward(t_pos *pos)
{
	if (pos->map[(int)(pos->posX - pos->dirX * pos->moveSpeed)][(int)pos->posY] == 0)
		pos->posX += pos->dirX * pos->moveSpeed;
	if (pos->map[(int)(pos->posX)][(int)(pos->posY + pos->dirY * pos->moveSpeed)] == 0)
		pos->posY += pos->dirY * pos->moveSpeed;
	return (0);
}

int		go_backward(t_pos *pos)
{
	if (pos->map[(int)(pos->posX - pos->dirX * pos->moveSpeed)][(int)pos->posY] == 0)
		pos->posX -= pos->dirX * pos->moveSpeed;
	if (pos->map[(int)pos->posX][(int)(pos->posY - pos->dirY * pos->moveSpeed)] == 0)
		pos->posY -= pos->dirY * pos->moveSpeed;
	return (0);
}

int		go_left(t_pos *pos)
{
	pos->oldDirX = pos->dirX;
	pos->dirX = pos->dirX * cos(pos->rotSpeed) - pos->dirY * sin(pos->rotSpeed);
	pos->dirY = pos->oldDirX * sin(pos->rotSpeed) + pos->dirY * cos(pos->rotSpeed);
	pos->oldPlaneX = pos->planeX;
	pos->planeX = pos->planeX * cos(pos->rotSpeed) - pos->planeY * sin(pos->rotSpeed);
	pos->planeY = pos->oldPlaneX * sin(pos->rotSpeed) + pos->planeY * cos(pos->rotSpeed);
	return (0);
}

int	go_right(t_pos *pos)
{
	pos->oldDirX = pos->dirX;
	pos->dirX = pos->dirX * cos(-pos->rotSpeed) - pos->dirY * sin(-pos->rotSpeed);
	pos->dirY = pos->oldDirX * sin(-pos->rotSpeed) + pos->dirY * cos(-pos->rotSpeed);
	pos->oldPlaneX = pos->planeX;
	pos->planeX = pos->planeX * cos(-pos->rotSpeed) - pos->planeY * sin(-pos->rotSpeed);
	pos->planeY = pos->oldPlaneX * sin(-pos->rotSpeed) + pos->planeY * cos(-pos->rotSpeed);
	return (0);
}
