/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:43:28 by cesar             #+#    #+#             */
/*   Updated: 2024/06/03 09:30:57 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	px_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREEN_WIDTH || x <= 0 || y >= SCREEN_HEIGHT || y <= 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (int)(img->bits_per_pixel * 0.125));
	*(unsigned int *)dst = color;
}

static int	xline_textured(t_app *app, t_horiztex *horiztex, int start, int end)
{
	float	delta_x;
	float	px;

	delta_x = end - start;
	px = fabs(delta_x);
	delta_x /= px;
	while ((int)(start - end))
	{
		horiztex->cellX = (int) horiztex->floorX;
		horiztex->cellY = (int) horiztex->floorY;
		horiztex->tx = (int) (TEX_WIDTH * (horiztex->floorX - horiztex->cellX)) & (TEX_WIDTH - 1);
		horiztex->ty = (int) (TEX_HEIGHT * (horiztex->floorY - horiztex->cellY)) & (TEX_HEIGHT - 1);
		horiztex->floorX += horiztex->floorStepX;
		horiztex->floorY += horiztex->floorStepY;
		horiztex->floor_tex_px = horiztex->floor_tex_content[TEX_WIDTH * horiztex->ty + horiztex->tx];
		horiztex->roof_tex_px = horiztex->roof_tex_content[TEX_WIDTH * horiztex->ty + horiztex->tx];
		// (void) app;
		px_put(app->img, start, horiztex->y, horiztex->floor_tex_px);
		px_put(app->img, start, SCREEN_HEIGHT - horiztex->y - 1, BLACK);
		start += delta_x;
	}
	return (0);
}

int	draw_horizontal_texture(t_app *app, t_pos *pos, t_horiztex *horiztex)
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
		xline_textured(app, horiztex, 0, SCREEN_WIDTH);
	}
	return (0);
}

static int	yline_textured(t_app *app, t_walltex *walltex, int start, int end)
{
	float	delta_y;
	float	px;
	uint32_t color;

	delta_y = end - start;
	px = fabs(delta_y);
	delta_y /= px;
	while ((int)(start - end))
	{
		walltex->texY = (int)walltex->texPos & (TEX_HEIGHT - 1);
		walltex->texPos += walltex->step;
		color = walltex->tex_content[TEX_HEIGHT * walltex->texY + walltex->texX];
		px_put(app->img, walltex->x, start, color);
		start += delta_y;
	}
	return (0);
}

int	 draw_wall_texture(t_app *app, t_pos *pos, t_walltex *walltex)
{
	if (pos->wallDir == 'N')
		walltex->texNum = 0;
	else if (pos->wallDir == 'S')
		walltex->texNum = 1;
	else if (pos->wallDir == 'E')
		walltex->texNum = 2;
	else if (pos->wallDir == 'W')
		walltex->texNum = 3;
	walltex->tex_content = (uint32_t *)pos->tex[walltex->texNum].data;
	if (pos->side == 0)
		walltex->wallX = pos->posY + pos->perpWallDist * pos->rayDirY;
	else
		walltex->wallX = pos->posX + pos->perpWallDist * pos->rayDirX;
	walltex->wallX -= floor(walltex->wallX);
	walltex->texX = (int)(walltex->wallX * (double)TEX_WIDTH);
	if ((pos->side == 0 && pos->rayDirX > 0) || (pos->side == 1 && pos->rayDirY < 0))
		walltex->texX = TEX_WIDTH - walltex->texX - 1;
	walltex->step = (double)TEX_HEIGHT / pos->lineHeight;
	walltex->texPos = walltex->step * (pos->drawStart - (SCREEN_HEIGHT * 0.5) + (pos->lineHeight * 0.5));
	yline_textured(app, walltex, pos->drawStart, pos->drawEnd);
	return (0);
}
