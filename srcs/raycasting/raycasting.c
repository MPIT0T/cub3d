/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:42:53 by cefuente          #+#    #+#             */
/*   Updated: 2024/06/19 10:41:10 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	get_ray_length(t_pos *pos, int x)
{
	pos->cam_x = 2 * x / (double)(SCREEN_WIDTH) - 1;
	pos->raydir_x = pos->p_dir_x + pos->surf_x * pos->cam_x;
	pos->raydir_y = pos->p_dir_y + pos->surf_y * pos->cam_x;
	pos->map_x = (int)pos->p_x;
	pos->map_y = (int)pos->p_y;
	if (pos->raydir_x == 0)
		pos->raydelta_x = 1e30;
	else
		pos->raydelta_x = fabs(1 / pos->raydir_x);
	if (pos->raydir_y == 0)
		pos->raydelta_y = 1e30;
	else
		pos->raydelta_y = fabs(1 / pos->raydir_y);
	pos->hit = 0;
	return (0);
}

static int	get_tile_size(t_pos *pos)
{
	if (pos->raydir_x < 0)
	{
		pos->step_x = -1;
		pos->raydist_x = (pos->p_x - pos->map_x) * pos->raydelta_x;
	}
	else
	{
		pos->step_x = 1;
		pos->raydist_x = (pos->map_x + 1.0 - pos->p_x) * pos->raydelta_x;
	}
	if (pos->raydir_y < 0)
	{
		pos->step_y = -1;
		pos->raydist_y = (pos->p_y - pos->map_y) * pos->raydelta_y;
	}
	else
	{
		pos->step_y = 1;
		pos->raydist_y = (pos->map_y + 1.0 - pos->p_y) * pos->raydelta_y;
	}
	return (0);
}

static int	dda(t_pos *pos)
{
	pos->found_door = false;
	while (1)
	{
		if (pos->raydist_x < pos->raydist_y)
		{
			pos->raydist_x += pos->raydelta_x;
			pos->map_x += pos->step_x;
			pos->side = 0;
			which_dir(pos, "NS", 1);
		}
		else
		{
			pos->raydist_y += pos->raydelta_y;
			pos->map_y += pos->step_y;
			pos->side = 1;
			which_dir(pos, "WE", 2);
		}
		check_door(pos);
		if (pos->map[pos->map_x][pos->map_y] == '1')
			return (0);
		if (pos->map[pos->map_x][pos->map_y] == '2')
			return (pos->wall_dir = 'D', 0);
	}
}

static int	line_height(t_pos *pos, size_t x)
{
	if (pos->side == 0)
		pos->wall_dist = (pos->raydist_x - pos->raydelta_x);
	else
		pos->wall_dist = (pos->raydist_y - pos->raydelta_y);
	pos->z_prox[x] = pos->wall_dist;
	pos->line_height = (size_t) SCREEN_HEIGHT / pos->wall_dist;
	pos->draw_start = (SCREEN_HEIGHT * 0.5) - (pos->line_height * 0.5);
	if (pos->draw_start < 0)
		pos->draw_start = 0;
	pos->draw_end = (SCREEN_HEIGHT * 0.5) + (pos->line_height * 0.5);
	if (pos->draw_end > SCREEN_HEIGHT)
		pos->draw_end = SCREEN_HEIGHT;
	return (0);
}

int	raycasting_loop(t_pos *pos, t_img *img, t_app *app)
{
	size_t		x;
	t_walltex	walltex;
	t_horiztex	horiztex;

	x = -1;
	if (pos->floor_tex == true || pos->roof_tex == true)
		get_horizontal_texture(pos, &horiztex);
	while (++x < SCREEN_WIDTH)
	{
		pos->column = x;
		get_ray_length(pos, x);
		get_tile_size(pos);
		dda(pos);
		line_height(pos, x);
		walltex.x = x;
		get_wall_texture(app, pos, &walltex);
	}
	sort_and_cast_sprites(pos, &app->ghosts_lst);
	draw_screen(pos, img);
	put_minimap(app);
	mlx_put_image_to_window(img->mlx, img->mlx_win,
		img->img, 0, 0);
	put_door_button(app);
	return (0);
}
