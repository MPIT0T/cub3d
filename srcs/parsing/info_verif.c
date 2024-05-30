/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:06:59 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/30 13:08:09 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	__verify_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	verify_color(t_color *color)
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

void	verify_infos(t_app *app)
{
	if (__verify_path(app->pos->no) || __verify_path(app->pos->so)
		|| __verify_path(app->pos->we) || __verify_path(app->pos->ea))
		exit_parsing_error(app, "invalid texture path");
	if (__verify_path_ext(app->pos->no) || __verify_path_ext(app->pos->so)
		|| __verify_path_ext(app->pos->we) || __verify_path_ext(app->pos->ea))
		exit_parsing_error(app, "invalid texture image format (.xpm required)");
}
