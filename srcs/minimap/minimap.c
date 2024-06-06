/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:48:23 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/06 10:54:45 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_horizontal_cross(t_app *app, int midX, int midY)
{
	px_put(app->img, midX - 5, midY, WHITE);
	px_put(app->img, midX - 4, midY - 1, WHITE);
	px_put(app->img, midX - 4, midY, WHITE);
	px_put(app->img, midX - 4, midY + 1, WHITE);
	px_put(app->img, midX - 3, midY - 1, WHITE);
	px_put(app->img, midX - 3, midY, WHITE);
	px_put(app->img, midX - 3, midY + 1, WHITE);
	px_put(app->img, midX - 2, midY - 1, WHITE);
	px_put(app->img, midX - 2, midY, WHITE);
	px_put(app->img, midX - 2, midY + 1, WHITE);
	px_put(app->img, midX - 1, midY - 1, WHITE);
	px_put(app->img, midX - 1, midY, WHITE);
	px_put(app->img, midX - 1, midY + 1, WHITE);

	px_put(app->img, midX + 1, midY - 1, WHITE);
	px_put(app->img, midX + 1, midY, WHITE);
	px_put(app->img, midX + 1, midY + 1, WHITE);
	px_put(app->img, midX + 2, midY - 1, WHITE);
	px_put(app->img, midX + 2, midY, WHITE);
	px_put(app->img, midX + 2, midY + 1, WHITE);
	px_put(app->img, midX + 3, midY - 1, WHITE);
	px_put(app->img, midX + 3, midY, WHITE);
	px_put(app->img, midX + 3, midY + 1, WHITE);
	px_put(app->img, midX + 4, midY - 1, WHITE);
	px_put(app->img, midX + 4, midY, WHITE);
	px_put(app->img, midX + 4, midY + 1, WHITE);
	px_put(app->img, midX + 5, midY, WHITE);
}

void	put_vertical_cross(t_app *app, int midX, int midY)
{
	px_put(app->img, midX, midY - 5, WHITE);
	px_put(app->img, midX - 1, midY - 4, WHITE);
	px_put(app->img, midX, midY - 4, WHITE);
	px_put(app->img, midX + 1, midY - 4, WHITE);
	px_put(app->img, midX - 1, midY - 3, WHITE);
	px_put(app->img, midX, midY - 3, WHITE);
	px_put(app->img, midX + 1, midY - 3, WHITE);
	px_put(app->img, midX - 1, midY - 2, WHITE);
	px_put(app->img, midX, midY - 2, WHITE);
	px_put(app->img, midX + 1, midY - 2, WHITE);
	px_put(app->img, midX - 1, midY - 1, WHITE);
	px_put(app->img, midX, midY - 1, WHITE);
	px_put(app->img, midX + 1, midY - 1, WHITE);

	px_put(app->img, midX - 1, midY + 1, WHITE);
	px_put(app->img, midX, midY + 1, WHITE);
	px_put(app->img, midX + 1, midY + 1, WHITE);
	px_put(app->img, midX - 1, midY + 2, WHITE);
	px_put(app->img, midX, midY + 2, WHITE);
	px_put(app->img, midX + 1, midY + 2, WHITE);
	px_put(app->img, midX - 1, midY + 3, WHITE);
	px_put(app->img, midX, midY + 3, WHITE);
	px_put(app->img, midX + 1, midY + 3, WHITE);
	px_put(app->img, midX - 1, midY + 4, WHITE);
	px_put(app->img, midX, midY + 4, WHITE);
	px_put(app->img, midX + 1, midY + 4, WHITE);
	px_put(app->img, midX, midY + 5, WHITE);
}

void	put_crosshair(t_app *app)
{
	int		midX;
	int		midY;

	midX = SCREEN_WIDTH / 2;
	midY = SCREEN_HEIGHT / 2;
	put_horizontal_cross(app, midX, midY);
	put_vertical_cross(app, midX, midY);
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
	set_frame_dimensions(app, &mm);
	get_minimap_pos(app, &mm);
	put_minimap_on_screen(app, &mm);
	put_minimap_frame(app, &mm);
	put_crosshair(app);
}
