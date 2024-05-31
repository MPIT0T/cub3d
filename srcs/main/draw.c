/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:28:11 by cesar             #+#    #+#             */
/*   Updated: 2024/05/31 15:16:00 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"



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