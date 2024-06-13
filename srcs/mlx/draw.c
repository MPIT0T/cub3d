/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:09:19 by cesar             #+#    #+#             */
/*   Updated: 2024/06/13 11:05:39 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	px_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREEN_WIDTH || x <= 0 || y >= SCREEN_HEIGHT || y <= 0)
		return ;
	dst = img->addr + (y * img->line_length + x
			* (int)(img->bits_per_pixel * 0.125));
	*(unsigned int *)dst = color;
}

static void	px_put_here(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREEN_WIDTH || x <= 0 || y >= SCREEN_HEIGHT || y <= 0)
		return ;
	dst = img->addr + (y * img->line_length + x
			* (int)(img->bits_per_pixel * 0.125));
	*(unsigned int *)dst = color;
}

void	draw_screen(t_pos *pos, t_img *img)
{
	ssize_t	y;
	ssize_t	x;

	y = -1;
	x = -1;
	while (++y < SCREEN_HEIGHT)
	{
		while (++x < SCREEN_WIDTH)
			px_put_here(img, x, y, pos->px[y][x]);
		x = -1;
	}
}
