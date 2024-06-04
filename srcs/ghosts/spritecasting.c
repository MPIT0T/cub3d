/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:42:31 by cesar             #+#    #+#             */
/*   Updated: 2024/06/04 23:42:42 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	sort_sprites(t_pos *pos, t_list **ghosts_lst)
{
	t_list	*tmp;
	t_list	*next;
	int		swapped;

	swapped = 1;
	tmp = *ghosts_lst;
	while (swapped)
	{
		((t_ghost *)tmp->content)->player_dist = ((pos->posX - ((t_ghost *)tmp->content)->x)
			* (pos->posX - ((t_ghost *)tmp->content)->x)
			+ (pos->posY - ((t_ghost *)tmp->content)->y)
			* (pos->posY - ((t_ghost *)tmp->content)->y));
		next = tmp->next;
		if (((t_ghost *)tmp->next->content)->player_dist > ((t_ghost *)tmp->next->content)->player_dist)
		{
			tmp->content = ((t_ghost *)tmp->next->content);
			next->content = (t_ghost *)tmp->content;
			swapped = 1;
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	find_sprites_to_render(t_sprt *sprt, t_pos *pos)
{
	ssize_t	y;
	ssize_t	x;
	int		d;
	uint32_t	color;

	sprt->tex_content = (uint32_t *)pos->tex[7].data;
	x = sprt->x_start - 1;
	while (++x < sprt->x_end)
	{
		sprt->tex_x = (int)(256 * (x - (-sprt->width / 2 + sprt->spriteScreenX)) * TEX_WIDTH / sprt->width) / 256;
		if (sprt->trans_Y > 0 && x > 0 && x < SCREEN_WIDTH && sprt->trans_Y < pos->z_prox[x])
		{
			y = sprt->y_start - 1;
			while (++y < sprt->y_end)
			{
				d = y * 256 - SCREEN_HEIGHT * 128 + sprt->height * 128;
				sprt->tex_y = ((d * TEX_HEIGHT) / sprt->height) / 256;
				color = sprt->tex_content[TEX_HEIGHT * sprt->tex_y + sprt->tex_x];
				pos->px[y][x] = color;
			}
		}
	}
}

static void	cast_sprites(t_pos *pos, t_list **ghosts_lst, t_sprt *sprt)
{
	t_list *tmp;

	tmp = *ghosts_lst;
	while (tmp)
	{
		sprt->x = ((t_ghost *)tmp->content)->x - pos->posX;
		sprt->y = ((t_ghost *)tmp->content)->y - pos->posY;
		sprt->invDet = 1.0 / (pos->planeX * pos->dirY - pos->dirX * pos->planeX);
		sprt->trans_X = sprt->invDet * (pos->dirY * sprt->x - pos->dirX * sprt->y);
		sprt->trans_Y = sprt->invDet * (-pos->planeY * sprt->x + pos->planeX * sprt->y);
		sprt->spriteScreenX = (int)((SCREEN_WIDTH / 2) * (1 + sprt->trans_X / sprt->trans_Y));
		sprt->height  = fabs(SCREEN_HEIGHT / (sprt->trans_Y));
		sprt->y_start = -sprt->height / 2 + SCREEN_HEIGHT / 2;
		if (sprt->y_start < 0)
			sprt->y_start = 0;
		sprt->y_end = sprt->height / 2 + SCREEN_HEIGHT / 2;
		if (sprt->y_end >= SCREEN_HEIGHT)
			sprt->y_end = SCREEN_HEIGHT - 1;
		sprt->width = fabs(SCREEN_HEIGHT / sprt->trans_Y);
		sprt->x_start = -sprt->width / 2 + sprt->spriteScreenX;
		if (sprt->x_end >= SCREEN_WIDTH)
			sprt->x_end = SCREEN_WIDTH - 1;
		find_sprites_to_render(sprt, pos);
		tmp = tmp->next;
	}
}

int	sort_and_cast_sprites(t_pos *pos, t_list **ghosts_lst)
{
	t_sprt	sprt;

	sort_sprites(pos, ghosts_lst);
	cast_sprites(pos, ghosts_lst, &sprt);
	return (0);
}
