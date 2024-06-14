/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_app.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:58:36 by cefuente          #+#    #+#             */
/*   Updated: 2024/06/14 14:54:28 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_images(t_tex *tex, t_img *img)
{
	tex->img = mlx_xpm_file_to_image(img->mlx, tex->file,
			&tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->data = mlx_get_data_addr(tex->img,
			&tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (!tex->data)
		return (1);
	return (0);
}

int	get_tex_files(t_app *app)
{
	app->pos->tex[0].file = app->pos->no;
	app->pos->tex[1].file = app->pos->so;
	app->pos->tex[2].file = app->pos->ea;
	app->pos->tex[3].file = app->pos->we;
	app->pos->tex[4].file = ROOF_TEX;
	app->pos->tex[5].file = FLOOR_TEX;
	app->pos->tex[6].file = DOOR_TEX;
	app->pos->tex[7].file = GHOST_TEX;
	app->pos->tex[8].file = OPEN_TEX;
	app->pos->tex[9].file = CLOSE_TEX;
	// app->pos->tex[10].file = PAUSE_TEX;
	return (0);
}

int	initiate_textures(t_app *app)
{
	ssize_t	y;
	int		i;

	y = -1;
	i = -1;
	app->pos->px = malloc(SCREEN_HEIGHT * sizeof(uint32_t *));
	while (++y < SCREEN_HEIGHT)
		app->pos->px[y] = malloc(SCREEN_WIDTH * sizeof(uint32_t));
	if (!app->pos->px)
		exit_error(app, EXIT_MALLOC);
	app->pos->tex = malloc(11 * sizeof(t_tex));
	if (!app->pos->tex)
		exit_error(app, EXIT_MALLOC);
	get_tex_files(app);
	while (++i < 10)
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
	mlx_mouse_hide(app->img->mlx, app->img->mlx_win);
	mlx_mouse_move(app->img->mlx, app->img->mlx_win,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return (0);
}

int	construct_app(t_app *app)
{
	app->img = NULL;
	app->img = malloc(sizeof(t_img));
	if (app->img == NULL)
		return (1);
	app->pos = NULL;
	app->pos = ft_calloc(sizeof(t_pos), 1);
	if (app->pos == NULL)
		return (ft_free(app->img), 1);
	app->pos->z_prox = ft_calloc(SCREEN_WIDTH, sizeof(int));
	if (app->pos->z_prox == NULL)
		return (ft_free(app->img), ft_free(app->pos), 1);
	app->pos->no = NULL;
	app->pos->so = NULL;
	app->pos->ea = NULL;
	app->pos->we = NULL;
	app->pos->map = NULL;
	app->pos->f = 0;
	app->pos->c = 0;
	app->full_file_string = NULL;
	app->pos->motion_up = false;
	app->pos->motion_down = false;
	app->pos->motion_left = false;
	app->pos->motion_right = false;
	return (0);
}
