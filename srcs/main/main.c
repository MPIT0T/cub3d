/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:28:36 by cesar             #+#    #+#             */
/*   Updated: 2024/06/14 15:22:11 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(t_app *app)
{
	if (app->pause == false)
	{
		mlx_mouse_move(app->img->mlx, app->img->mlx_win,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	motion(app);
	clear_px_buffer(app->pos->px);
	new_image(app);
	ghosts_are_coming(app);
	raycasting_loop(app->pos, app->img, app);
	return (0);
}

int	main(int ac, char **av)
{
	t_app	app;

	app.err = 0;
	ft_check_args(ac, av);
	if (construct_app(&app))
		return (ft_putstr_fd("Error: malloc\n", 2), EXIT_MALLOC);
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
