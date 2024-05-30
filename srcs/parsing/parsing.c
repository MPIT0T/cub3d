/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:25:18 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/29 14:25:57 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	__fill_map_infos(t_app *app, char *full_file_string)
{
	app->map->no = get_texture(app, full_file_string, ID_NORTH);
	app->map->so = get_texture(app, full_file_string, ID_SOUTH);
	app->map->we = get_texture(app, full_file_string, ID_WEST);
	app->map->ea = get_texture(app, full_file_string, ID_EAST);
	app->map->f = get_color(app, full_file_string, ID_FLOOR);
	app->map->c = get_color(app, full_file_string, ID_CEILING);
	if (!app->map->no || !app->map->so || !app->map->we
		|| !app->map->ea || !app->map->f || !app->map->c)
		exit_parsing_error(app, "wrong or missing texture");
	verify_infos(app);
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
