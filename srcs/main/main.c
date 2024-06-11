/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:28:36 by cesar             #+#    #+#             */
/*   Updated: 2024/06/05 16:14:55 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_args(int ac, char **av)
{
	size_t	len;

	if (ac < 2)
		ft_printf_fd(2, "%s: map not provided\n", ERRMSG);
	if (ac > 2)
		ft_printf_fd(2, "%s: too many arguments\n", ERRMSG);
	len = ft_strlen(av[1]);
	if (ac == 2)
	{
		if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u'
			|| av[1][len - 3] != 'c' || av[1][len - 4] != '.')
			ft_printf_fd(2, "%s: bad map extension\n", ERRMSG);
		else
			return ;
		exit(EXIT_ARGS);
	}
	exit(EXIT_ARGS);
}

int	game_loop(t_app *app)
{
	mlx_mouse_move(app->img->mlx, app->img->mlx_win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	motion(app);
	clear_px_buffer(app->pos->px);
	new_image(app);
	// print_map(app->pos);
	ghosts_are_coming(app);
	raycasting_loop(app->pos, app->img, app);
	return (0);
}

int	little_red_cross(t_app *app)
{
	exit_error(app, EXIT_SUCCESS);
	return (0);
}

int	init_hook(t_app *app)
{
	mlx_hook(app->img->mlx_win, 17, 0, little_red_cross, app);
	mlx_hook(app->img->mlx_win, KeyPress, KeyPressMask, change_motion_keypress, app);
	mlx_hook(app->img->mlx_win, KeyRelease, KeyReleaseMask, change_motion_keyrelease, app);
	mlx_hook(app->img->mlx_win, 6, 1L<<6, mouse_motion, app);
	mlx_loop_hook(app->img->mlx, game_loop, app);
	return (0);
}

void	set_camera_pos_and_dir(t_app *app)
{
	size_t	x;
	size_t	y;

	app->pos->dirX = 0;
	app->pos->dirY = 0;
	app->pos->planeX = 0;
	app->pos->planeY = 0;
	y = -1;
	while (app->pos->map[++y])
	{
		x = -1;
		while (app->pos->map[y][++x])
		{
			if (ft_strchr("NSWE", app->pos->map[y][x]))
			{
				if (app->pos->map[y][x] == 'N')
				{
					app->pos->dirX = -1;
					app->pos->planeY = 0.66;
				}
				if (app->pos->map[y][x] == 'S')
				{
					app->pos->dirX = 1;
					app->pos->planeY = -0.66;
				}
				if (app->pos->map[y][x] == 'W')
				{
					app->pos->dirY = 1;
					app->pos->planeX = 0.66;
				}
				if (app->pos->map[y][x] == 'E')
				{
					app->pos->dirY = -1;
					app->pos->planeX = -0.66;
				}
				app->pos->posY = ((double) x) + 0.5;
				app->pos->posX = ((double) y) + 0.5;
				app->pos->map[y][x] = '0';
			}
		}
	}
}

int	initiate_positions(t_app *app)
{
	set_camera_pos_and_dir(app);
	app->pos->time = 0;
	app->pos->oldTime = 0;
	app->pos->h = 1;
	app->pos->moveSpeed = 0.05;
	app->pos->rotSpeedArrows = 0.05;
	app->pos->rotSpeedMouse = 0.00;
	app->pos->motion_up = false;
	app->pos->motion_down = false;
	app->pos->rotate_left_arrows = false;
	app->pos->rotate_right_arrows = false;
	app->pos->rotate_right_mouse = false;
	app->pos->rotate_right_mouse = false;
	app->pos->pointing_door = none;
	return (0);
}

int main(int ac, char **av)
{
	t_app	app;

	app.err = 0;
	ft_check_args(ac, av);
	if (construct_app(&app))
		return (EXIT_MALLOC);
	parsing(&app, av[1]);
	initiate_positions(&app);
	initiate_mlx(&app);
	initiate_textures(&app);
	if (pop_some_ghosts(&app) == 1)
		exit_error(&app, EXIT_MALLOC);
	raycasting_loop(app.pos, app.img, &app);
	init_hook(&app);
	mlx_loop(app.img->mlx);
	free_app(&app);
	return (EXIT_SUCCESS);
}
