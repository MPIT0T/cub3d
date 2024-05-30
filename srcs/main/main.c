/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:28:36 by cesar             #+#    #+#             */
/*   Updated: 2024/05/30 11:13:09 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_data_structs(t_data *data)
{
	data->map = ft_calloc(sizeof(t_map), 1);
	if (!data->map)
		return (1);
	data->map->no = NULL;
	data->map->so = NULL;
	data->map->we = NULL;
	data->map->ea = NULL;
	data->map->f = NULL;
	data->map->c = NULL;
	data->full_file_string = NULL;
	return (0);
}

void	ft_check_args(int ac, char **av)
{
	size_t	len;

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
	if (ac < 2)
		ft_printf_fd(2, "%s: map not provided\n", ERRMSG);
	if (ac > 2)
		ft_printf_fd(2, "%s: too many arguments\n", ERRMSG);
	exit(EXIT_ARGS);
}

int main(int ac, char **av)
{
	t_app	app;

	app.err = 0;
	ft_check_args(ac, av);
	if (init_data_structs(&app))
		return (EXIT_MALLOC);
	parsing(&app, av[1]);
	if (construct_app(&app) == 1)
		return (handle_err(&app));
	if (get_map(app.pos, &app.err) == 1)
		return (handle_err(&app));
	if (initiate_mlx(&app) == 1)
		return (handle_err(&app));
	if (initiate_textures(&app) == 1)
		return (handle_err(&app));
	raycasting_loop(app.pos, app.img, &app);
	init_hook(&app);
	mlx_loop(app.img->mlx);
	free_data(&app);
	return (EXIT_SUCCESS);
}