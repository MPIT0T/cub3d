/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:28:11 by cesar             #+#    #+#             */
/*   Updated: 2024/05/27 15:46:41 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	px_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREEN_WIDTH || x <= 0 || y >= SCREEN_HEIGHT || y <= 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
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
		// if (yStart >= app->pos->drawStart && yStart <= app->pos->drawEnd)
		px_put(app->img, x, yStart, color);
		yStart += delta_y;
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