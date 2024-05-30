/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_app.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:27:06 by cesar             #+#    #+#             */
/*   Updated: 2024/05/30 11:33:51 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	malloc_app(t_app *app)
{
	app->img = NULL;
	app->img = malloc(sizeof(t_img));
	if (!app->img)
		exit_error(app, EXIT_MALLOC);
	app->pos = NULL;
	app->pos = malloc(sizeof(t_pos));
	if (!app->pos)
		exit_error(app, EXIT_MALLOC);

	return (0);
}

int	initiate_positions(t_app *app)
{
	app->pos->posX = 22;//x and y start position
	app->pos->posY = 12;  
	app->pos->dirX = -1;//initial direction vector
	app->pos->dirY = 0; 
	app->pos->planeX = 0;//the 2d raycaster version of camera plane
	app->pos->planeY = 0.66; 
	app->pos->time = 0; //time of current frame
	app->pos->oldTime = 0; //time of previous frame
	app->pos->h = 1;
	app->pos->moveSpeed = 0.05;
	app->pos->rotSpeed = 0.05;
	app->pos->motion_up = false;
	app->pos->motion_down = false;
	app->pos->rotate_left = false;
	app->pos->rotate_right = false;
	return (0);
}

int	get_images(t_tex *tex, t_img *img)
{
	tex->img = mlx_xpm_file_to_image(img->mlx, tex->file,
		&tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->data = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_length, &tex->endian);
	return (0);
}

int	initiate_textures(t_app *app)
{
	app->pos->tex = malloc(4 * sizeof(t_tex));
	if (!app->pos->tex)
		return (app->err = 1);

	app->pos->tex[0].file = ft_strdup("textures/wall_north.xpm");
	app->pos->tex[1].file = ft_strdup("textures/wall_south.xpm");
	app->pos->tex[2].file = ft_strdup("textures/wall_east.xpm");
	app->pos->tex[3].file = ft_strdup("textures/wall_west.xpm");
	int	i = -1;
	app->pos->textures = malloc(4 * sizeof(uint32_t *));
	if (!app->pos->textures)
		exit_error(app, EXIT_MALLOC);
	while (++i < 4)
	{
		app->pos->textures[i] = malloc(TEX_WIDTH * TEX_HEIGHT * sizeof(uint32_t));
		if (!app->pos->textures[i])
			exit_error(app, EXIT_MALLOC);
	}
	i = -1;
	while (++i < 4)
	{
		get_images(&app->pos->tex[i], app->img);
		if (!app->pos->tex[i].img)
			exit_error(app, EXIT_MALLOC);
	}
	return (0);
}

int	initiate_mlx(t_app *app)
{
	app->img->mlx = NULL;
	app->img->mlx = mlx_init();
	if (!app->img->mlx)
		exit_error(app, EXIT_MLX);
	app->img->mlx_win = NULL;
	app->img->mlx_win = mlx_new_window(app->img->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!app->img->mlx_win)
		exit_error(app, EXIT_MLX);
	app->img->img = NULL;
	app->img->img = mlx_new_image(app->img->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!app->img->img)
		exit_error(app, EXIT_MALLOC);
	app->img->addr = NULL;
	app->img->addr = mlx_get_data_addr(app->img->img, &app->img->bits_per_pixel,
			&app->img->line_length, &app->img->endian);
	if (!app->img->addr)
		exit_error(app, EXIT_MALLOC);
	return (0);
}

int	construct_app(t_app *app)
{
	malloc_app(app);
	initiate_positions(app);
	return (0);
}