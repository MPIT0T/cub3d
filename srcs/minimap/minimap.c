/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:48:23 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/03 10:15:25 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_minimap_pos(t_app *app, t_minimap *mm)
{
	mm->startX = app->pos->posY - 7;
	if (app->pos->posY > (int) app->pos->MAP_WIDTH - 7)
		mm->startX = (int) app->pos->MAP_WIDTH - 14;
	else if (app->pos->posY - 7 < 0)
		mm->startX = 0;
	mm->startY = app->pos->posX - 5;
	if (app->pos->posX > (int) app->pos->MAP_HEIGHT - 5)
		mm->startY = (int) app->pos->MAP_HEIGHT - 10;
	else if (app->pos->posX - 5 < 0)
		mm->startY = 0;
	if (app->pos->MAP_WIDTH >= 14)
		mm->mapSizeX = 14;
	else
		mm->mapSizeX = (int) app->pos->MAP_WIDTH;
	if (app->pos->MAP_HEIGHT >= 10)
		mm->mapSizeY = 10;
	else
		mm->mapSizeY = (int) app->pos->MAP_HEIGHT;
}

void	put_minimap_on_screen(t_app *app, t_minimap *mm)
{
	double	tmp = mm->startX;

	mm->pixY = 0;
	while (mm->pixY < (20 * mm->mapSizeY) + 10)
	{
		mm->startX = tmp;
		mm->pixX = 0;
		while (mm->pixX < (20 * mm->mapSizeX) + 10)
		{
			if (mm->pixY < 5 || mm->pixY >= (20 * mm->mapSizeY))
			{
				px_put(app->img, mm->pixX, mm->pixY, YELLOW);
//				mm->startX += 0.05;
				mm->pixX++;
				continue ;
			}
			if (mm->pixX < 5 || mm->pixX >= (20 * mm->mapSizeX))
			{
				px_put(app->img, mm->pixX, mm->pixY, YELLOW);
//				mm->startX += 0.05;
				mm->pixX++;
				continue ;
			}
			modf(mm->startX, &mm->intX);
			modf(mm->startY, &mm->intY);
			if (app->pos->map[(int) mm->intY][(int) mm->intX] == '1')
				px_put(app->img, mm->pixX, mm->pixY, WHITE);
			else if (app->pos->map[(int) mm->intY][(int) mm->intX] == '0')
				px_put(app->img, mm->pixX, mm->pixY, BLACK);
			if (mm->startX > app->pos->posY - 0.2 && mm->startX < app->pos->posY + 0.2
				&& mm->startY > app->pos->posX - 0.2 && mm->startY < app->pos->posX + 0.2)
				px_put(app->img, mm->pixX, mm->pixY, YELLOW);
			mm->startX += 0.05;
			mm->pixX++;
		}
		mm->startY += 0.05;
		mm->pixY++;
	}
}

void	put_minimap(t_app *app)
{
	t_minimap	mm;

	get_minimap_pos(app, &mm);
	put_minimap_on_screen(app, &mm);
}




















/*

void	make_connections(t_app *app, int x, int y, t_con *connections)
{
	connections->n = false;
	connections->s = false;
	connections->w = false;
	connections->e = false;
	connections->nw = false;
	connections->ne = false;
	connections->sw = false;
	connections->se = false;
	if (x != 0 && app->pos->map[y][x - 1] == '1')
		connections->n = true;
	if (app->pos->map[y][x + 1] == '1')
		connections->s = true;
	if (y != 0 && app->pos->map[y - 1][x] == '1')
		connections->w = true;
	if (app->pos->map[y + 1][x] == '1')
		connections->e = true;
	if (x != 0 && y != 0 && app->pos->map[y - 1][x - 1] == '1')
		connections->nw = true;
	if (x != 0 && app->pos->map[y + 1][x - 1] == '1')
		connections->ne = true;
	if (y != 0 && app->pos->map[y - 1][x + 1] == '1')
		connections->sw = true;
	if (app->pos->map[y + 1][x + 1] == '1')
		connections->se = true;
}

void	put_right_wall(t_app *app, int x, int y)
{
	t_con	cons;

	make_connections(app, x, y, &cons);

}
*/

