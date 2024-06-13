/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:43:28 by cesar             #+#    #+#             */
/*   Updated: 2024/06/12 14:58:35 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	yline(t_app *app, int x, int yStart, int yEnd, int color)
{
	while (yStart < yEnd)
	{
		app->pos->px[yStart][x] = color;
		yStart++;
	}
	return (0);
}

static int	yline_textured(t_app *app, t_walltex *walltex, int start, int end)
{
	uint32_t color;

	while (start < end)
	{
		walltex->texY = (TEX_HEIGHT - 1) & (int)walltex->texPos;
		walltex->texPos += walltex->step;
		color = walltex->tex_content[TEX_HEIGHT * walltex->texY + walltex->texX];
		app->pos->px[start][walltex->x] = color;
		start++;
	}
	return (0);
}

static int	get_wallnum(t_walltex *walltex, t_pos *pos)
{
	if (pos->wallDir == 'N')
		walltex->texNum = 0;
	else if (pos->wallDir == 'S')
		walltex->texNum = 1;
	else if (pos->wallDir == 'E')
		walltex->texNum = 2;
	else if (pos->wallDir == 'W')
		walltex->texNum = 3;
	else if (pos->wallDir == 'D')
		walltex->texNum = 6;
	return (0);
}

int	 get_wall_texture(t_app *app, t_pos *pos, t_walltex *walltex)
{
	get_wallnum(walltex, pos);
	walltex->tex_content = (uint32_t *)pos->tex[walltex->texNum].data;
	if (pos->side == 0)
		walltex->wallX = pos->posY + pos->perpWallDist * pos->rayDirY;
	else
		walltex->wallX = pos->posX + pos->perpWallDist * pos->rayDirX;
	walltex->wallX -= floor(walltex->wallX);
	walltex->texX = (int)(walltex->wallX * (double)TEX_WIDTH);
	if ((pos->side == 0 && pos->rayDirX > 0) || (pos->side == 1 && pos->rayDirY < 0))
		walltex->texX = TEX_WIDTH - walltex->texX - 1;
	walltex->step = (double) TEX_HEIGHT / pos->lineHeight;
	walltex->texPos = walltex->step * (pos->drawStart - (SCREEN_HEIGHT * 0.5) + (pos->lineHeight * 0.5));
	yline_textured(app, walltex, pos->drawStart, pos->drawEnd);
	if (!pos->roof_tex)
		yline(app, walltex->x, 0, pos->drawStart, pos->c);
	if (!pos ->floor_tex)
		yline(app, walltex->x, pos->drawEnd, SCREEN_HEIGHT, pos->f);
	return (0);
}

void	which_dir(t_pos *pos, char *set, int call)
{
	if (call == 1)
	{
		if (pos->rayDirX < 0)
			pos->wallDir = set[0];
		else
			pos->wallDir = set[1];
	}
	else
	{
		if (pos->rayDirY < 0)
			pos->wallDir = set[0];
		else
			pos->wallDir = set[1];
	}
}
