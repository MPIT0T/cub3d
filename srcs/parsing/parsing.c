/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:25:18 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/14 15:00:32 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	__fill_map_infos(t_app *app, char *full_file_string)
{
	app->pos->no = get_texture(app, full_file_string, ID_NORTH);
	app->pos->so = get_texture(app, full_file_string, ID_SOUTH);
	app->pos->ea = get_texture(app, full_file_string, ID_EAST);
	app->pos->we = get_texture(app, full_file_string, ID_WEST);
	app->pos->f = get_color(app, full_file_string, ID_FLOOR);
	app->pos->c = get_color(app, full_file_string, ID_CEILING);
	if (!app->pos->no || !app->pos->so || !app->pos->we
		|| !app->pos->ea)
		exit_parsing_error(app, "wrong or missing texture");
	if (check_multiple_id_instances(full_file_string, ID_NORTH)
		|| check_multiple_id_instances(full_file_string, ID_SOUTH)
		|| check_multiple_id_instances(full_file_string, ID_EAST)
		|| check_multiple_id_instances(full_file_string, ID_WEST)
		|| check_multiple_id_instances(full_file_string, ID_FLOOR)
		|| check_multiple_id_instances(full_file_string, ID_CEILING))
		exit_parsing_error(app, "multiple instances of a texture");
	verify_infos(app);
}

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

int	parsing(t_app *app, const char *path_to_map)
{
	app->full_file_string = read_map_file(app, path_to_map);
	if (!app->full_file_string)
		exit_parsing_error(app, "empty map");
	__fill_map_infos(app, app->full_file_string);
	parse_map(app, app->full_file_string);
	return (0);
}
