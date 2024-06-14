/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:42:31 by cesar             #+#    #+#             */
/*   Updated: 2024/06/14 14:39:25 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	set_player_dist(t_pos *pos, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		((t_ghost *)tmp->content)->player_dist
			= ((pos->p_x - ((t_ghost *)tmp->content)->x)
				* (pos->p_x - ((t_ghost *)tmp->content)->x)
				+ (pos->p_y - ((t_ghost *)tmp->content)->y)
				* (pos->p_y - ((t_ghost *)tmp->content)->y));
		tmp = tmp->next;
	}
	return (0);
}

static void	draw_sprite_px(t_sprt *sprt, t_pos *pos, int y, int x)
{
	uint32_t	color;
	int			d;

	sprt->tex_x = (int)(256 * (((int)x
					- (-sprt->width / 2 + sprt->sprite_x)))
			* TEX_WIDTH / sprt->width) / 256;
	d = ((int)y * 256) - (SCREEN_HEIGHT * 128) + (sprt->height * 128);
	sprt->tex_y = ((d * TEX_HEIGHT) / sprt->height) / 256;
	color = sprt->tex_content[TEX_WIDTH * sprt->tex_y + sprt->tex_x];
	if (color != 0x000000)
		pos->px[y][x] = color;
}

static void	find_sprites_to_render(t_sprt *sprt, t_pos *pos, t_list *ghosts)
{
	t_ghost	*ghost;

	ghost = (t_ghost *)ghosts->content;
	ghost->dx = ghost->x - pos->p_x;
	ghost->dy = ghost->y - pos->p_y;
	ghost->dot_product = ghost->dir_x * ghost->dx + ghost->dir_y * ghost->dy;
	if (ghost->dot_product > 0)
		sprt->tex_content = (uint32_t *)pos->tex[10].data;
	else
		sprt->tex_content = (uint32_t *)pos->tex[7].data;
	while (sprt->x_start < sprt->x_end && sprt->x_start < SCREEN_WIDTH)
	{
		if (sprt->trans_y > 0 && sprt->trans_y
			<= pos->z_prox[sprt->x_start] + 1)
		{
			sprt->y_start = sprt->y_start_flag;
			while (sprt->y_start < sprt->y_end && sprt->y_start < SCREEN_HEIGHT)
			{
				draw_sprite_px(sprt, pos, sprt->y_start, sprt->x_start);
				sprt->y_start++;
			}
		}
		sprt->x_start++;
	}
}

static void	init_sprite(t_sprt *sprt, t_list *tmp, t_pos *pos)
{
	sprt->x = ((t_ghost *)tmp->content)->x - pos->p_x;
	sprt->y = ((t_ghost *)tmp->content)->y - pos->p_y;
	sprt->trans_x = sprt->trans_factor
		* (pos->p_dir_y * sprt->x - pos->p_dir_x * sprt->y);
	sprt->trans_y = sprt->trans_factor * (-pos->surf_y
			* sprt->x + pos->surf_x * sprt->y);
	sprt->sprite_x = (int)((SCREEN_WIDTH / 2)
			* (1 + sprt->trans_x / sprt->trans_y));
	sprt->height = fabs(SCREEN_HEIGHT / sprt->trans_y);
	sprt->width = fabs(SCREEN_HEIGHT / sprt->trans_y);
	sprt->y_start = -sprt->height / 2 + SCREEN_HEIGHT / 2;
	if (sprt->y_start < 0)
		sprt->y_start = 0;
	sprt->y_end = sprt->height / 2 + SCREEN_HEIGHT / 2;
	if (sprt->y_end >= SCREEN_HEIGHT)
		sprt->y_end = SCREEN_HEIGHT - 1;
	sprt->x_start = -sprt->width / 2 + sprt->sprite_x;
	if (sprt->x_start < 0)
		sprt->x_start = 0;
	sprt->x_end = sprt->width / 2 + sprt->sprite_x;
	if (sprt->x_end >= SCREEN_WIDTH)
		sprt->x_end = SCREEN_WIDTH - 1;
	sprt->y_start_flag = sprt->y_start;
}

int	sort_and_cast_sprites(t_pos *pos, t_list **ghosts_lst)
{
	t_sprt	sprt;
	t_list	*tmp;

	tmp = *ghosts_lst;
	sprt.trans_factor = 1 / ((pos->surf_x * pos->p_dir_y)
			- (pos->p_dir_x * pos->surf_y));
	set_player_dist(pos, ghosts_lst);
	sort_list(ghosts_lst);
	while (tmp)
	{
		init_sprite(&sprt, tmp, pos);
		find_sprites_to_render(&sprt, pos, tmp);
		tmp = tmp->next;
	}
	return (0);
}
