/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:07:41 by cesar             #+#    #+#             */
/*   Updated: 2024/06/03 23:33:50 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	xline_textured(t_pos *pos, t_horiztex *horiztex, int start, int end)
{
	while (start < end)
	{
		horiztex->cellX = (int) horiztex->floorX;
		horiztex->cellY = (int) horiztex->floorY;
		horiztex->tx = (int) (TEX_WIDTH * (horiztex->floorX - horiztex->cellX)) & (TEX_WIDTH - 1);
		horiztex->ty = (int) (TEX_HEIGHT * (horiztex->floorY - horiztex->cellY)) & (TEX_HEIGHT - 1);
		horiztex->floorX += horiztex->floorStepX;
		horiztex->floorY += horiztex->floorStepY;
		horiztex->floor_tex_px = horiztex->floor_tex_content[TEX_WIDTH * horiztex->ty + horiztex->tx];
		horiztex->roof_tex_px = horiztex->roof_tex_content[TEX_WIDTH * horiztex->ty + horiztex->tx];
		pos->px[horiztex->y][start] = horiztex->floor_tex_px;
		pos->px[SCREEN_HEIGHT - horiztex->y - 1][start] = horiztex->roof_tex_px;
		start++;
	}
	return (0);
}

int	get_horizontal_texture(t_pos *pos, t_horiztex *horiztex)
{
	ssize_t	y;

	y = -1;
	horiztex->roof_tex_content = (uint32_t *) pos->tex[4].data;
	horiztex->floor_tex_content = (uint32_t *) pos->tex[5].data;
	while (++y < SCREEN_HEIGHT)
	{	
		horiztex->y = y;
		horiztex->rayDirX0 = pos->dirX - pos->planeX;
		horiztex->rayDirY0 = pos->dirY - pos->planeY;
		horiztex->rayDirX1 = pos->dirX + pos->planeX;
		horiztex->rayDirY1 = pos->dirY + pos->planeY;
		horiztex->p = y - SCREEN_HEIGHT * 0.5;
		horiztex->posZ = SCREEN_HEIGHT * 0.5;
		horiztex->rowDistance = horiztex->posZ / horiztex->p;
		horiztex->floorStepX = horiztex->rowDistance * (horiztex->rayDirX1 - horiztex->rayDirX0) / SCREEN_WIDTH;
		horiztex->floorStepY = horiztex->rowDistance * (horiztex->rayDirY1 - horiztex->rayDirY0) / SCREEN_WIDTH;
		horiztex->floorX = pos->posX + horiztex->rowDistance * horiztex->rayDirX0;
		horiztex->floorY = pos->posY + horiztex->rowDistance * horiztex->rayDirY0;
		xline_textured(pos, horiztex, 0, SCREEN_WIDTH);
	}
	return (0);
}
