/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:07:41 by cesar             #+#    #+#             */
/*   Updated: 2024/06/13 10:38:56 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	xline_textured(t_pos *pos, t_horiztex *horiztex, int start, int end)
{
	while (start < end)
	{
		horiztex->roof_x = (int) horiztex->floor_x;
		horiztex->roof_y = (int) horiztex->floor_y;
		horiztex->t_x = (int)(TEX_WIDTH
				* (horiztex->floor_x - horiztex->roof_x)) & (TEX_WIDTH - 1);
		horiztex->t_y = (int)(TEX_HEIGHT
				* (horiztex->floor_y - horiztex->roof_y)) & (TEX_HEIGHT - 1);
		horiztex->floor_x += horiztex->floor_step_x;
		horiztex->floor_y += horiztex->floor_step_y;
		horiztex->floor_tex_px = horiztex->floor_tex_content[TEX_WIDTH
			* horiztex->t_y + horiztex->t_x];
		horiztex->roof_tex_px = horiztex->roof_tex_content[TEX_WIDTH
			* horiztex->t_y + horiztex->t_x];
		if (pos->floor_tex)
			pos->px[horiztex->y][start] = horiztex->floor_tex_px;
		if (pos->roof_tex)
			pos->px[SCREEN_HEIGHT - horiztex->y - 1][start]
				= horiztex->roof_tex_px;
		start++;
	}
	return (0);
}

int	get_horizontal_texture(t_pos *pos, t_horiztex *horiztex)
{
	horiztex->y = -1;
	horiztex->roof_tex_content = (uint32_t *) pos->tex[4].data;
	horiztex->floor_tex_content = (uint32_t *) pos->tex[5].data;
	while (++horiztex->y < SCREEN_HEIGHT)
	{
		horiztex->raydir_x_start = pos->p_dir_x - pos->surf_x;
		horiztex->raydir_y_start = pos->p_dir_y - pos->surf_y;
		horiztex->raydir_x_end = pos->p_dir_x + pos->surf_x;
		horiztex->raydir_y_end = pos->p_dir_y + pos->surf_y;
		horiztex->p = horiztex->y - SCREEN_HEIGHT * 0.5;
		horiztex->pos_z = SCREEN_HEIGHT * 0.5;
		horiztex->row_dist = horiztex->pos_z / horiztex->p;
		horiztex->floor_step_x = horiztex->row_dist * (horiztex->raydir_x_end
				- horiztex->raydir_x_start) / SCREEN_WIDTH;
		horiztex->floor_step_y = horiztex->row_dist * (horiztex->raydir_y_end
				- horiztex->raydir_y_start) / SCREEN_WIDTH;
		horiztex->floor_x = pos->p_x + horiztex->row_dist
			* horiztex->raydir_x_start;
		horiztex->floor_y = pos->p_y + horiztex->row_dist
			* horiztex->raydir_y_start;
		xline_textured(pos, horiztex, 0, SCREEN_WIDTH);
	}
	return (0);
}
