/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:25:18 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/03 11:04:50 by cefuente         ###   ########.fr       */
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
