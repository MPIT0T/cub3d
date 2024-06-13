/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:48:23 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/13 09:35:59 by cefuente         ###   ########.fr       */
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
	if (app->pos->map_width >= 14)
		mm->map_size_x = 14;
	if (app->pos->map_height >= 10)
		mm->map_size_y = 10;
	if (mm->map_size_x == -1)
	{
		mm->map_size_x = app->pos->map_width;
		mm->start_x = 0;
	}
	if (mm->map_size_y == -1)
	{
		mm->map_size_y = app->pos->map_height;
		mm->start_y = 0;
	}
}

void	put_minimap(t_app *app)
{
	t_minimap	mm;

	mm.pix_x = -1;
	mm.pix_y = -1;
	mm.start_x = -1;
	mm.start_y = -1;
	mm.int_x = -1;
	mm.int_y = -1;
	mm.map_size_x = -1;
	mm.map_size_y = -1;
	__set_frame_dimensions(app, &mm);
	get_minimap_pos(app, &mm);
	put_minimap_on_screen(app, &mm);
	put_minimap_frame(app, &mm);
	__put_crosshair(app);
}
