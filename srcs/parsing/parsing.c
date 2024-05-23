/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:25:18 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/23 18:49:25 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_default_texture(char *id)
{
	if (ft_strcmp(id, ID_NORTH) == 0)
		return (DEFAULT_NORTH);
	if (ft_strcmp(id, ID_SOUTH) == 0)
		return (DEFAULT_SOUTH);
	if (ft_strcmp(id, ID_WEST) == 0)
		return (DEFAULT_WEST);
	if (ft_strcmp(id, ID_EAST) == 0)
		return (DEFAULT_EAST);
	if (ft_strcmp(id, ID_FLOOR) == 0)
		return (DEFAULT_FLOOR);
	if (ft_strcmp(id, ID_CEILING) == 0)
		return (DEFAULT_CEILING);
}

char	*get_texture(t_data *data, char *str, char *id)
{
	size_t	i;
	size_t	size;
	char	*result;

	i = 0;
	size = 0;
	while (str[i] && ft_strncmp(&str[i], id, ft_strlen(id)))
		i++;
	if (str[i] == '\0')
		return (get_default_texture(id));
	i += ft_strlen(id);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '.')
		return (NULL);	//TODO erreur syntaxe
	if (str[++i] != '/')
		return (NULL);	//TODO erreur syntaxe
	i++;
	while (str[i + size] && !ft_isblank(str[i + size]))
	{

	}
}

int	fill_map_data(t_data *data, char *full_file_string)
{
	data->map->no = get_texture()
}

int	parsing_map(t_data *data, const char *path_to_map)
{
	char	*map_full_str;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		exit_error(data, 1);
	map_full_str = read_map_file(data, path_to_map);
	if (map_full_str == NULL)
	{
		ft_printf_fd(2, "`%s' is an empty map.\n");
		exit_error(data, 0);
	}
	fill_map_data(data, map_full_str);
	return (0);
}
