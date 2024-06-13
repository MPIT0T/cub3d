/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:19:12 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/13 09:35:59 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_minimap_pos(t_app *app, t_minimap *mm)
{
	if (mm->start_x == -1)
	{
		mm->start_x = app->pos->p_y - (mm->map_size_x / 2);
		if (app->pos->p_y > app->pos->map_width - (mm->map_size_x / 2))
			mm->start_x = app->pos->map_width - mm->map_size_x;
		else if (app->pos->p_y - (mm->map_size_x / 2) < 0)
			mm->start_x = 0;
	}
	if (mm->start_y == -1)
	{
		mm->start_y = app->pos->p_x - (mm->map_size_y / 2);
		if (app->pos->p_x > app->pos->map_height - (mm->map_size_y / 2))
			mm->start_y = app->pos->map_height - mm->map_size_y;
		else if (app->pos->p_x - (mm->map_size_y / 2) < 0)
			mm->start_y = 0;
	}
}

void	put_minimap_frame(t_app *app, t_minimap *mm)
{
	mm->pix_y = 0;
	while (mm->pix_y < ((20 * mm->map_size_y) + 10))
	{
		mm->pix_x = 0;
		while (mm->pix_x < ((20 * mm->map_size_x) + 10))
		{
			if (mm->pix_y < 5 || mm->pix_y >= ((20 * mm->map_size_y) + 5))
				px_put(app->img, mm->pix_x, mm->pix_y, YELLOW);
			if (mm->pix_x < 5 || mm->pix_x >= ((20 * mm->map_size_x) + 5))
				px_put(app->img, mm->pix_x, mm->pix_y, YELLOW);
			mm->pix_x++;
		}
		mm->pix_y++;
	}
}

static void	__put_entities_pixel(t_app *app, t_minimap *mm)
{
	size_t	i;

	i = -1;
	while (++i < GHOSTS_NUMBER)
	{
		if (mm->start_x > app->ghosts[i].y - 0.1
			&& mm->start_x < app->ghosts[i].y + 0.1
			&& mm->start_y > app->ghosts[i].x - 0.1
			&& mm->start_y < app->ghosts[i].x + 0.1)
			px_put(app->img, mm->pix_x, mm->pix_y, RED);
	}
	if (mm->start_x > app->pos->p_y - 0.1
		&& mm->start_x < app->pos->p_y + 0.1
		&& mm->start_y > app->pos->p_x - 0.1
		&& mm->start_y < app->pos->p_x + 0.1)
		px_put(app->img, mm->pix_x, mm->pix_y, YELLOW);
}

static void	__put_minimap_pixel(t_app *app, t_minimap *mm)
{
	modf(mm->start_x, &mm->int_x);
	modf(mm->start_y, &mm->int_y);
	if (app->pos->map[(int) mm->int_y][(int) mm->int_x] == '1')
		px_put(app->img, mm->pix_x, mm->pix_y, WHITE);
	else if (app->pos->map[(int) mm->int_y][(int) mm->int_x] == '2')
		px_put(app->img, mm->pix_x, mm->pix_y, YELLOW);
	else if (app->pos->map[(int) mm->int_y][(int) mm->int_x] == '3')
		px_put(app->img, mm->pix_x, mm->pix_y, GREY);
	else if (app->pos->map[(int) mm->int_y][(int) mm->int_x] == '0'
		|| app->pos->map[(int) mm->int_y][(int) mm->int_x] == ' ')
		px_put(app->img, mm->pix_x, mm->pix_y, BLACK);
	__put_entities_pixel(app, mm);
}

void	put_minimap_on_screen(t_app *app, t_minimap *mm)
{
	double	tmp;

	tmp = mm->start_x;
	mm->pix_y = 5;
	while (mm->pix_y < ((20 * mm->map_size_y) + 5))
	{
		mm->start_x = tmp;
		mm->pix_x = 5;
		while (mm->pix_x < ((20 * mm->map_size_x) + 5))
		{
			__put_minimap_pixel(app, mm);
			mm->start_x += 0.05;
			mm->pix_x++;
		}
		mm->start_y += 0.05;
		mm->pix_y++;
	}
}
