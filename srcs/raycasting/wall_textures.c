/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:43:28 by cesar             #+#    #+#             */
/*   Updated: 2024/06/13 10:53:47 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	yline(t_pos *pos, int x, char type)
{
	unsigned int	color;
	int				start;
	int				end;

	if (type == 'c')
	{
		color = pos->c;
		start = 0;
		end = pos->draw_start;
	}
	else
	{
		color = pos->f;
		start = pos->draw_end;
		end = SCREEN_HEIGHT;
	}
	while (start < end)
	{
		pos->px[start][x] = color;
		start++;
	}
	return (0);
}

static int	yline_textured(t_app *app, t_walltex *walltex, int start, int end)
{
	uint32_t	color;

	while (start < end)
	{
		walltex->tex_y = (TEX_HEIGHT - 1) & (int)walltex->tex_pos;
		walltex->tex_pos += walltex->step;
		color = walltex->tex_content[TEX_HEIGHT
			* walltex->tex_y + walltex->tex_x];
		app->pos->px[start][walltex->x] = color;
		start++;
	}
	return (0);
}

static int	get_wallnum(t_walltex *walltex, t_pos *pos)
{
	if (pos->wall_dir == 'N')
		walltex->tex_num = 0;
	else if (pos->wall_dir == 'S')
		walltex->tex_num = 1;
	else if (pos->wall_dir == 'E')
		walltex->tex_num = 2;
	else if (pos->wall_dir == 'W')
		walltex->tex_num = 3;
	else if (pos->wall_dir == 'D')
		walltex->tex_num = 6;
	return (0);
}

int	get_wall_texture(t_app *app, t_pos *pos, t_walltex *walltex)
{
	get_wallnum(walltex, pos);
	walltex->tex_content = (uint32_t *)pos->tex[walltex->tex_num].data;
	if (pos->side == 0)
		walltex->wall_x = pos->p_y + pos->wall_dist * pos->raydir_y;
	else
		walltex->wall_x = pos->p_x + pos->wall_dist * pos->raydir_x;
	walltex->wall_x -= floor(walltex->wall_x);
	walltex->tex_x = (int)(walltex->wall_x * (double)TEX_WIDTH);
	if ((pos->side == 0 && pos->raydir_x > 0)
		|| (pos->side == 1 && pos->raydir_y < 0))
		walltex->tex_x = TEX_WIDTH - walltex->tex_x - 1;
	walltex->step = (double) TEX_HEIGHT / pos->line_height;
	walltex->tex_pos = walltex->step * (pos->draw_start
			- (SCREEN_HEIGHT * 0.5) + (pos->line_height * 0.5));
	yline_textured(app, walltex, pos->draw_start, pos->draw_end);
	if (!pos->roof_tex)
		yline(pos, walltex->x, 'c');
	if (!pos ->floor_tex)
		yline(pos, walltex->x, 'f');
	return (0);
}

void	which_dir(t_pos *pos, char *set, int call)
{
	if (call == 1)
	{
		if (pos->raydir_x < 0)
			pos->wall_dir = set[0];
		else
			pos->wall_dir = set[1];
	}
	else
	{
		if (pos->raydir_y < 0)
			pos->wall_dir = set[0];
		else
			pos->wall_dir = set[1];
	}
}
