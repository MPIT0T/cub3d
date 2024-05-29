/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:25:18 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/29 11:48:50 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	__fill_map_infos(t_data *data, char *full_file_string)
{
	data->map->no = get_texture(data, full_file_string, ID_NORTH);
	data->map->so = get_texture(data, full_file_string, ID_SOUTH);
	data->map->we = get_texture(data, full_file_string, ID_WEST);
	data->map->ea = get_texture(data, full_file_string, ID_EAST);
	data->map->f = get_color(data, full_file_string, ID_FLOOR);
	data->map->c = get_color(data, full_file_string, ID_CEILING);
	if (!data->map->no || !data->map->so || !data->map->we
		|| !data->map->ea || !data->map->f || !data->map->c)
		exit_parsing_error(data, "wrong or missing texture");
	verify_infos(data);
}

int	parsing(t_data *data, const char *path_to_map)
{
	data->full_file_string = read_map_file(data, path_to_map);
	if (!data->full_file_string)
		exit_parsing_error(data, "empty map");
	__fill_map_infos(data, data->full_file_string);
	parse_map(data, data->full_file_string);
	return (0);
}
