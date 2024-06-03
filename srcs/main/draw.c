/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:28:11 by cesar             #+#    #+#             */
/*   Updated: 2024/06/03 11:00:46 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


// static int	yline_with_stars(t_app *app, int x, int yStart, int yEnd)
// {
// 	float	delta_y;
// 	float	px;
// 	int		color;
// 	delta_y = yEnd - yStart;
// 	px = fabs(delta_y);
// 	delta_y /= px;
// 	while ((int)(yStart - yEnd))
// 	{
// 		if (x * yStart < 100000)
// 			color = YELLOW;
// 		else
// 			color = BLACK;
// 		px_put(app->img, x, yStart, color);
// 		yStart += delta_y;
// 	}
// 	return (0);
// }

// static int	xline_textured(t_app *app, t_horiztex *horiztex, int start, int end)
// {
// 	float	delta_x;
// 	float	px;

// 	delta_x = end - start;
// 	px = fabs(delta_x);
// 	delta_x /= px;
// 	while ((int)(start - end))
// 	{
// 		horiztex->cellX = (int) horiztex->floorX;
// 		horiztex->cellY = (int) horiztex->floorY;
// 		horiztex->tx = (int) (TEX_WIDTH * (horiztex->floorX - horiztex->cellX)) & (TEX_WIDTH - 1);
// 		horiztex->ty = (int) (TEX_HEIGHT * (horiztex->floorY - horiztex->cellY)) & (TEX_HEIGHT - 1);
// 		horiztex->floorX += horiztex->floorStepX;
// 		horiztex->floorY += horiztex->floorStepY;
// 		horiztex->floor_tex_px = horiztex->floor_tex_content[TEX_WIDTH * horiztex->ty + horiztex->tx];
// 		horiztex->roof_tex_px = horiztex->roof_tex_content[TEX_WIDTH * horiztex->ty + horiztex->tx];
// 		// (void) app;
// 		// px_put(app->img, start, horiztex->y, horiztex->roof_tex_px);
// 		px_put(app->img, start, SCREEN_HEIGHT - horiztex->y - 1, horiztex->roof_tex_px);
// 		start += delta_x;
// 	}
// 	return (0);
// }

// int	draw_horizontal_texture(t_app *app, t_pos *pos, t_horiztex *horiztex)
// {
// 	ssize_t	y;

// 	y = -1;
// 	horiztex->roof_tex_content = (uint32_t *) pos->tex[4].data;
// 	horiztex->floor_tex_content = (uint32_t *) pos->tex[5].data;

// 	while (++y < SCREEN_HEIGHT)
// 	{	
// 		horiztex->y = y;
// 		horiztex->rayDirX0 = pos->dirX - pos->planeX;
// 		horiztex->rayDirY0 = pos->dirY - pos->planeY;
// 		horiztex->rayDirX1 = pos->dirX + pos->planeX;
// 		horiztex->rayDirY1 = pos->dirY + pos->planeY;
// 		horiztex->p = y - SCREEN_HEIGHT * 0.5;
// 		horiztex->posZ = SCREEN_HEIGHT * 5;
// 		horiztex->rowDistance = horiztex->posZ / horiztex->p;
// 		horiztex->floorStepX = horiztex->rowDistance * (horiztex->rayDirX1 - horiztex->rayDirX0) / SCREEN_WIDTH;
// 		horiztex->floorStepY = horiztex->rowDistance * (horiztex->rayDirY1 - horiztex->rayDirY0) / SCREEN_WIDTH;
// 		horiztex->floorX = pos->posX + horiztex->rowDistance * horiztex->rayDirX0;
// 		horiztex->floorY = pos->posY + horiztex->rowDistance * horiztex->rayDirY0;
// 		xline_textured(app, horiztex, 0, SCREEN_WIDTH);
// 	}
// 	return (0);
// }


// int	yline(t_app *app, int x, int yStart, int yEnd, int color)
// {
// 	float	delta_y;
// 	float	px;

// 	delta_y = yEnd - yStart;
// 	px = fabs(delta_y);
// 	delta_y /= px;
// 	while ((int)(yStart - yEnd))
// 	{
// 		px_put(app->img, x, yStart, color);
// 		yStart += delta_y;
// 	}
// 	return (0);
// }


// int	xline(t_app *app, int y, int xStart, int xEnd, /*uint32_t **px_tab*/ int color)
// {
// 	float	delta_x;
// 	float	px;

// 	delta_x = xEnd - xStart;
// 	px = fabs(delta_x);
// 	delta_x /= px;
// 	while ((int)(xStart - xEnd))
// 	{
// 		px_put(app->img, xStart, y, /*(int)px_tab[y][xStart]*/ color);
// 		xStart += delta_x;
// 	}
// 	return (0);
// }

// int	line(t_img *img, int startX, int startY, int nextX, int nextY, int color)
// {
// 	float	delta_x;
// 	float	delta_y;
// 	float	px;
// 	float	i;

// 	delta_x = nextX - startX;
// 	delta_y = nextY - startY;
// 	px = fmax(fabs(delta_x), fabs(delta_y));
// 	delta_x /= px;
// 	delta_y /= px;
// 	i = 0;
// 	while ((int)(startX - nextX) || (int)(startY - nextY))
// 	{
// 		px_put(img, startX, startY, color);
// 		startX += delta_x;
// 		startY += delta_y;
// 		i++;
// 	}
// 	return (0);
// }