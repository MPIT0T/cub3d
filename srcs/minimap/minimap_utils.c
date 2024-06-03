/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:19:12 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/03 13:31:02 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_frame_dimensions(t_app *app, t_minimap *mm)
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

void	get_minimap_pos(t_app *app, t_minimap *mm)
{
	if (mm->startX == -1)
	{
		mm->startX = app->pos->posY - (mm->mapSizeX / 2);
		if (app->pos->posY > app->pos->MAP_WIDTH - (mm->mapSizeX / 2))
			mm->startX = app->pos->MAP_WIDTH - mm->mapSizeX;
		else if (app->pos->posY - (mm->mapSizeX / 2) < 0)
			mm->startX = 0;
	}
	if (mm->startY == -1)
	{
		mm->startY = app->pos->posX - (mm->mapSizeY / 2);
		if (app->pos->posX > app->pos->MAP_HEIGHT - (mm->mapSizeY / 2))
			mm->startY = app->pos->MAP_HEIGHT - mm->mapSizeY;
		else if (app->pos->posX - (mm->mapSizeY / 2) < 0)
			mm->startY = 0;
	}
}

void	put_minimap_frame(t_app *app, t_minimap *mm)
{
	mm->pixY = 0;
	while (mm->pixY < ((20 * mm->mapSizeY) + 10))
	{
		mm->pixX = 0;
		while (mm->pixX < ((20 * mm->mapSizeX) + 10))
		{
			if (mm->pixY < 5 || mm->pixY >= ((20 * mm->mapSizeY) + 5))
				px_put(app->img, mm->pixX, mm->pixY, YELLOW);
			if (mm->pixX < 5 || mm->pixX >= ((20 * mm->mapSizeX) + 5))
				px_put(app->img, mm->pixX, mm->pixY, YELLOW);
			mm->pixX++;
		}
		mm->pixY++;
	}
}

void	put_minimap_pixel(t_app *app, t_minimap *mm)
{
	modf(mm->startX, &mm->intX);
	modf(mm->startY, &mm->intY);
	if (app->pos->map[(int) mm->intY][(int) mm->intX] == '1')
		px_put(app->img, mm->pixX, mm->pixY, WHITE);
	else if (app->pos->map[(int) mm->intY][(int) mm->intX] == '0')
		px_put(app->img, mm->pixX, mm->pixY, BLACK);
	if (mm->startX > app->pos->posY - 0.1
		&& mm->startX < app->pos->posY + 0.1
		&& mm->startY > app->pos->posX - 0.1
		&& mm->startY < app->pos->posX + 0.1)
		px_put(app->img, mm->pixX, mm->pixY, YELLOW);
}

void	put_minimap_on_screen(t_app *app, t_minimap *mm)
{
	double	tmp;

	tmp = mm->startX;
	mm->pixY = 5;
	while (mm->pixY < ((20 * mm->mapSizeY) + 5))
	{
		mm->startX = tmp;
		mm->pixX = 5;
		while (mm->pixX < ((20 * mm->mapSizeX) + 5))
		{
			put_minimap_pixel(app, mm);
			mm->startX += 0.05;
			mm->pixX++;
		}
		mm->startY += 0.05;
		mm->pixY++;
	}
}
