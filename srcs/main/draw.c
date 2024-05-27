/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:28:11 by cesar             #+#    #+#             */
/*   Updated: 2024/05/25 09:05:52 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	px_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREEN_WIDTH || x <= 0 || y >= SCREEN_HEIGHT || y <= 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// int	line(t_opts *opts, t_img *img, t_pos pos, t_pos npos)
// {
// 	float	delta_x;
// 	float	delta_y;
// 	float	px;
// 	float	i;

// 	colors(opts, &pos);
// 	colors(opts, &npos);
// 	delta_x = npos.x - pos.x;
// 	delta_y = npos.y - pos.y;
// 	px = max(absol(delta_x), absol(delta_y));
// 	delta_x /= px;
// 	delta_y /= px;
// 	i = 0;
// 	while ((int)(pos.x - npos.x) || (int)(pos.y - npos.y))
// 	{
// 		// gradient(&pos, &npos, i, px);
// 		px_put(img, pos.x, pos.y, pos.color);
// 		pos.x += delta_x;
// 		pos.y += delta_y;
// 		i++;t_pos npos
// 	}
// 	return (0);
// }

int vline(t_img *img, int x, int drawStart, int drawEnd, int color)
{
	int	y;
	y = drawStart;
    while (y <= drawEnd)
    {
        px_put(img, x, y, color);
		y++;
    }
    return 0;
}