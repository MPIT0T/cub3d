/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:42:53 by cefuente          #+#    #+#             */
/*   Updated: 2024/06/12 15:55:04 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	get_ray_length(t_pos *pos, int x)
{
	pos->cam_x = 2 * x / (double)(SCREEN_WIDTH) - 1; //x-coordinate in camera space
	pos->ray_xdir = pos->p_dir_x + pos->surf_x * pos->cam_x;
	pos->ray_ydir = pos->p_dir_y + pos->surf_y * pos->cam_x;
	pos->mapX = (int)pos->p_x;
	pos->mapY = (int)pos->p_y;
	if (pos->ray_xdir == 0)
		pos->deltaDistX = 1e30;
	else
		pos->deltaDistX = fabs(1 / pos->ray_xdir);
	if (pos->ray_ydir == 0)
		pos->deltaDistY = 1e30;
	else
		pos->deltaDistY = fabs(1 / pos->ray_ydir);
	pos->hit = 0;
	return (0);
}

static int	get_tile_size(t_pos *pos)
{
	if (pos->ray_xdir < 0)
	{
		pos->stepX = -1;
		pos->sideDistX = (pos->p_x - pos->mapX) * pos->deltaDistX;
	}
	else
	{
		pos->stepX = 1;
		pos->sideDistX = (pos->mapX + 1.0 - pos->p_x) * pos->deltaDistX;
	}
	if (pos->ray_ydir < 0)
	{
		pos->stepY = -1;
		pos->sideDistY = (pos->p_y - pos->mapY) * pos->deltaDistY;
	}
	else
	{
		pos->stepY = 1;
		pos->sideDistY = (pos->mapY + 1.0 - pos->p_y) * pos->deltaDistY;
	}
	return (0);
}

static int	DDA(t_pos *pos)
{
	pos->found_door = false;
	while (1)
	{
		if (pos->sideDistX < pos->sideDistY)
		{
			pos->sideDistX += pos->deltaDistX;
			pos->mapX += pos->stepX;
			pos->side = 0;
			which_dir(pos, "NS", 1);
		}
		else
		{
			pos->sideDistY += pos->deltaDistY;
			pos->mapY += pos->stepY;
			pos->side = 1;
			which_dir(pos, "WE", 2);
		}
		if (pos->column == SCREEN_WIDTH / 2)
		{
			if (pos->map[pos->mapX][pos->mapY] == '2' || pos->map[pos->mapX][pos->mapY] == '3')
				door_dir(pos);
			else if (pos->found_door == false)
				pos->pointing_door = none;
		}
		if (pos->map[pos->mapX][pos->mapY] == '1')
			return (0);
		if (pos->map[pos->mapX][pos->mapY] == '2')
			return (pos->wallDir = 'D', 0);
	}
}

static int	line_height(t_pos *pos, size_t x)
{
	if (pos->side == 0)
		pos->perpWallDist = (pos->sideDistX - pos->deltaDistX);
	else
		pos->perpWallDist = (pos->sideDistY - pos->deltaDistY);
	pos->z_prox[x] = pos->perpWallDist;
	pos->lineHeight = (int)(SCREEN_HEIGHT / pos->perpWallDist);
	pos->drawStart = (-pos->lineHeight * 0.5) + (SCREEN_HEIGHT * 0.5);
	if (pos->drawStart < 0)
		pos->drawStart = 0;
	pos->drawEnd = (pos->lineHeight * 0.5) + (SCREEN_HEIGHT * 0.5);
	if (pos->drawEnd >= SCREEN_HEIGHT)
		pos->drawEnd = SCREEN_HEIGHT - 1;
	return (0);
}

int	raycasting_loop(t_pos *pos, t_img *img, t_app *app)
{
	size_t		x;
	t_walltex	walltex;
	t_horiztex	horiztex;

	x = -1;
	if (pos->floor_tex || pos->roof_tex)
		get_horizontal_texture(pos, &horiztex);
	while (++x < SCREEN_WIDTH)
	{
		pos->column = x;
		get_ray_length(pos, x);
		get_tile_size(pos);
		DDA(pos);
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
	return 0;
}
