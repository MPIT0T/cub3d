/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:06:59 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/28 14:07:44 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	__verify_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

static int	__verify_color(t_color *color)
{
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (1);
	return (0);
}

static int	__verify_path_ext(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5)
		return (1);
	if (path[len - 1] != 'm' || path[len - 2] != 'p'
		|| path[len - 3] != 'x' || path[len - 4] != '.')
		return (1);
	return (0);
}

void	verify_infos(t_data *data)
{
	if (__verify_path(data->map->no) || __verify_path(data->map->so)
		|| __verify_path(data->map->we) || __verify_path(data->map->ea))
		exit_parsing_error(data, "invalid texture path");
	if (__verify_path_ext(data->map->no) || __verify_path_ext(data->map->so)
		|| __verify_path_ext(data->map->we) || __verify_path_ext(data->map->ea))
		exit_parsing_error(data, "invalid texture image format (.xpm required)");
	if (__verify_color(data->map->c) || __verify_color(data->map->f))
		exit_parsing_error(data, "invalid color format");
}
