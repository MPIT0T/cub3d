/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_app.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/31 09:27:33 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3D.h"

int	get_images(t_tex *tex, t_img *img)
{
	tex->img = mlx_xpm_file_to_image(img->mlx, tex->file,
		&tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->data = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (!tex->data)
		return (1);
	return (0);
}

int	initiate_textures(t_app *app)
{
	app->pos->tex = malloc(4 * sizeof(t_tex));
	if (!app->pos->tex)
		exit_error(app, EXIT_MALLOC);

	app->pos->tex[0].file = app->pos->no;
	app->pos->tex[1].file = app->pos->so;
	app->pos->tex[2].file = app->pos->ea;
	app->pos->tex[3].file = app->pos->we;
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
		if (!app->pos->tex[i].data)
			exit_error(app, EXIT_MLX);
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
	app->img = NULL;
	app->img = malloc(sizeof(t_img));
	if (!app->img)
		return (1);
	app->pos = NULL;
	app->pos = malloc(sizeof(t_pos));
	if (!app->pos)
		return (1);
	app->pos->no = NULL;
	app->pos->so = NULL;
	app->pos->ea = NULL;
	app->pos->we = NULL;
	app->pos->f = 0;
	app->pos->c = 0;
	app->full_file_string = NULL;
	return (0);
}
