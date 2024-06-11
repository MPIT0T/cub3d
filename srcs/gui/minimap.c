/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:48:23 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/10 17:58:55 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	__put_horizontal_cross(t_app *app, int midX, int midY)
{
	int		i;

	i = -5;
	while (++i < 5)
	{
		if (i != 0)
		{
			px_put(app->img, midX + i, midY -1, WHITE);
			px_put(app->img, midX + i, midY, WHITE);
			px_put(app->img, midX + i, midY + 1, WHITE);
		}
	}
	px_put(app->img, midX - 5, midY, WHITE);
	px_put(app->img, midX + 5, midY, WHITE);
}

static void	__put_vertical_cross(t_app *app, int midX, int midY)
{
	int		i;

	i = -5;
	while (++i < 5)
	{
		if (i != 0)
		{
			px_put(app->img, midX - 1, midY + i, WHITE);
			px_put(app->img, midX, midY + i, WHITE);
			px_put(app->img, midX + 1, midY + i, WHITE);
		}
	}
	px_put(app->img, midX, midY - 5, WHITE);
	px_put(app->img, midX, midY + 5, WHITE);
}

static void	__put_crosshair(t_app *app)
{
	__put_horizontal_cross(app, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	__put_vertical_cross(app, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

static void	__set_frame_dimensions(t_app *app, t_minimap *mm)
{
	if (app->pos->MAP_WIDTH >= 14)
		mm->mapSizeX = 14;
	if (app->pos->MAP_HEIGHT >= 10)
		mm->mapSizeY = 10;
	if (mm->mapSizeX == -1)
	{
		mm->mapSizeX = app->pos->MAP_WIDTH;
		mm->startX = 0;
	}
	if (mm->mapSizeY == -1)
	{
		mm->mapSizeY = app->pos->MAP_HEIGHT;
		mm->startY = 0;
	}
}

void	put_minimap(t_app *app)
{
	t_minimap	mm;

	mm.pixX = -1;
	mm.pixY = -1;
	mm.startX = -1;
	mm.startY = -1;
	mm.intX = -1;
	mm.intY = -1;
	mm.mapSizeX = -1;
	mm.mapSizeY = -1;
	__set_frame_dimensions(app, &mm);
	get_minimap_pos(app, &mm);
	put_minimap_on_screen(app, &mm);
	put_minimap_frame(app, &mm);
	__put_crosshair(app);
}
