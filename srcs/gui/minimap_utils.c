/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:19:12 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/12 15:52:02 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_minimap_pos(t_app *app, t_minimap *mm)
{
	if (mm->startX == -1)
	{
		mm->startX = app->pos->p_y - (mm->mapSizeX / 2);
		if (app->pos->p_y > app->pos->MAP_WIDTH - (mm->mapSizeX / 2))
			mm->startX = app->pos->MAP_WIDTH - mm->mapSizeX;
		else if (app->pos->p_y - (mm->mapSizeX / 2) < 0)
			mm->startX = 0;
	}
	if (mm->startY == -1)
	{
		mm->startY = app->pos->p_x - (mm->mapSizeY / 2);
		if (app->pos->p_x > app->pos->MAP_HEIGHT - (mm->mapSizeY / 2))
			mm->startY = app->pos->MAP_HEIGHT - mm->mapSizeY;
		else if (app->pos->p_x - (mm->mapSizeY / 2) < 0)
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

static void	__put_entities_pixel(t_app *app, t_minimap *mm)
{
	size_t	i;

	i = -1;
	while (++i < GHOSTS_NUMBER)
	{
		if (mm->startX > app->ghosts[i].y - 0.1
			&& mm->startX < app->ghosts[i].y + 0.1
			&& mm->startY > app->ghosts[i].x - 0.1
			&& mm->startY < app->ghosts[i].x + 0.1)
			px_put(app->img, mm->pixX, mm->pixY, RED);
	}
	if (mm->startX > app->pos->p_y - 0.1
		&& mm->startX < app->pos->p_y + 0.1
		&& mm->startY > app->pos->p_x - 0.1
		&& mm->startY < app->pos->p_x + 0.1)
		px_put(app->img, mm->pixX, mm->pixY, YELLOW);
}

static void	__put_minimap_pixel(t_app *app, t_minimap *mm)
{
	modf(mm->startX, &mm->intX);
	modf(mm->startY, &mm->intY);
	if (app->pos->map[(int) mm->intY][(int) mm->intX] == '1')
		px_put(app->img, mm->pixX, mm->pixY, WHITE);
	else if (app->pos->map[(int) mm->intY][(int) mm->intX] == '2')
		px_put(app->img, mm->pixX, mm->pixY, YELLOW);
	else if (app->pos->map[(int) mm->intY][(int) mm->intX] == '3')
		px_put(app->img, mm->pixX, mm->pixY, GREY);
	else if (app->pos->map[(int) mm->intY][(int) mm->intX] == '0'
		|| app->pos->map[(int) mm->intY][(int) mm->intX] == ' ')
		px_put(app->img, mm->pixX, mm->pixY, BLACK);
	__put_entities_pixel(app, mm);
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
			__put_minimap_pixel(app, mm);
			mm->startX += 0.05;
			mm->pixX++;
		}
		mm->startY += 0.05;
		mm->pixY++;
	}
}
