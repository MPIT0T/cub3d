/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:48:23 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/31 18:46:11 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_minimap(t_app *app)
{
	t_minimap	mm;

	if (app->pos->posY >= 5 && app->pos->posY <= app->pos->MAP_WIDTH - 5)
	{
		mm.startX = app->pos->posY - 5;
		mm.endX = app->pos->posY + 5;
	}
	else if (app->pos->posY > app->pos->MAP_WIDTH - 5)
	{
		mm.startX = app->pos->MAP_WIDTH - 11;
		mm.endX = app->pos->MAP_WIDTH - 1;
	}
	else if (app->pos->posY < 5)
	{
		mm.startX = 0;
		mm.endX = 10;
	}

	if (app->pos->posX >= 5 && app->pos->posX <= app->pos->MAP_HEIGHT - 5)
	{
		mm.startY = app->pos->posX - 5;
		mm.endY = app->pos->posX + 5;
	}
	else if (app->pos->posX > app->pos->MAP_HEIGHT - 5)
	{
		mm.startY = app->pos->MAP_HEIGHT - 11;
		mm.endY = app->pos->MAP_HEIGHT - 1;
	}
	else if (app->pos->posX < 5)
	{
		mm.startY = 0;
		mm.endY = 10;
	}

	char	dir = 'P';
/*
	if (app->pos->dirX < 0)
		dir = 'N';
	if (app->pos->dirX > 0)
		dir = 'S';
	if (app->pos->dirY < 0)
		dir = 'W';
	if (app->pos->dirY > 0)
		dir = 'E';*/

	modf(mm.startY, &mm.startYi);
	modf(mm.endY, &mm.endYi);

	double	posX;
	double	posY;

	modf(app->pos->posY, &posX);
	modf(app->pos->posX, &posY);

	while (mm.startYi <= mm.endYi)
	{
		modf(mm.startX, &mm.startXi);
		modf(mm.endX, &mm.endXi);
		while (mm.startXi <= mm.endXi)
		{
			if (mm.startXi == posX && mm.startYi == posY)
				printf("%c", dir);
			else
				printf("%c", app->pos->map[(int) mm.startYi][(int) mm.startXi]);
			mm.startXi++;
		}
		printf("\n");
		mm.startYi++;
	}
	printf("\n\n");
}
