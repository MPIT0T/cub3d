/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:28:11 by cesar             #+#    #+#             */
/*   Updated: 2024/05/30 13:13:59 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	px_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREEN_WIDTH || x <= 0 || y >= SCREEN_HEIGHT || y <= 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (int)(img->bits_per_pixel * 0.125));
	*(unsigned int *)dst = color;
}

int	yline(t_app *app, int x, int yStart, int yEnd, int color)
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

int	yline_textured(t_app *app, t_ctex *ctex, int start, int end)
{
	float	delta_y;
	float	px;
	uint32_t color;

	delta_y = end - start;
	px = fabs(delta_y);
	delta_y /= px;
	while ((int)(start - end))
	{

		ctex->texY = (int)ctex->texPos & (TEX_HEIGHT - 1);
		ctex->texPos += ctex->step;
		color = ctex->texture[TEX_HEIGHT * ctex->texY + ctex->texX];
		px_put(app->img, ctex->x, start, color);
		start += delta_y;
	}
	return (0);
}

int	xline(t_app *app, int y, int xStart, int xEnd, /*uint32_t **px_tab*/ int color)
{
	float	delta_x;
	float	px;

	delta_x = xEnd - xStart;
	px = fabs(delta_x);
	delta_x /= px;
	while ((int)(xStart - xEnd))
	{
		px_put(app->img, xStart, y, /*(int)px_tab[y][xStart]*/ color);
		xStart += delta_x;
	}
	return (0);
}

int	line(t_img *img, int startX, int startY, int nextX, int nextY, int color)
{
	float	delta_x;
	float	delta_y;
	float	px;
	float	i;

	delta_x = nextX - startX;
	delta_y = nextY - startY;
	px = fmax(fabs(delta_x), fabs(delta_y));
	delta_x /= px;
	delta_y /= px;
	i = 0;
	while ((int)(startX - nextX) || (int)(startY - nextY))
	{
		px_put(img, startX, startY, color);
		startX += delta_x;
		startY += delta_y;
		i++;
	}
	return (0);
}