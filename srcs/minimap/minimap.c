/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:48:23 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/31 11:55:57 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_minimap(t_app *app)
{
	t_minimap	mm;

	if (app->pos->posY >= 5)
		mm.startX = app->pos->posY - 5;
	else
		mm.startX = 0;
	if (app->pos->posX >= 5)
		mm.startY = app->pos->posX - 5;
	else
		mm.startY = 0;
	if (app->pos->posY <= app->pos->MAP_WIDTH - 5)
		mm.endX = app->pos->posY + 5;
	else
		mm.endX = 0;
	if (app->pos->posX <= app->pos->MAP_HEIGHT - 5)
		mm.endY = app->pos->posX + 5;
	else
		mm.endY = 0;


	modf(mm.startX, &mm.startXi);
	modf(mm.startY, &mm.startYi);
	modf(mm.endX, &mm.endXi);
	modf(mm.endY, &mm.endYi);

	while (mm.startYi < mm.endYi)
	{
		while (mm.startXi < mm.endXi)
		{
			write(1, &app->pos->map[(int) mm.startYi][(int) mm.startXi], 1);
			mm.startXi++;
		}
		write(1, "\n", 1);
		mm.startYi++;
	}
	write(1, "\n\n\n", 3);
}
