/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:43:28 by cesar             #+#    #+#             */
/*   Updated: 2024/06/03 11:23:48 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	px_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREEN_WIDTH || x <= 0 || y >= SCREEN_HEIGHT || y <= 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (int)(img->bits_per_pixel * 0.125));
	*(unsigned int *)dst = color;
}

static int	yline(t_app *app, int x, int yStart, int yEnd, int color)
{
	float	delta_y;
	float	px;

	delta_y = yEnd - yStart;
	px = fabs(delta_y);
	delta_y /= px;
	while ((int)(yStart - yEnd))
	{
		px_put(app->img, x, yStart, color);
		yStart += delta_y;
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
	yline(app, walltex->x, 0, pos->drawStart, BLACK);
	yline_textured(app, walltex, pos->drawStart, pos->drawEnd);
	yline(app, walltex->x, pos->drawEnd, SCREEN_HEIGHT, GREY);
	return (0);
}
