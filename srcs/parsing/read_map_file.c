/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:32:10 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/11 09:35:11 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*__read_entire_file(t_app *app, int fd)
{
	ssize_t	sz;
	char	buff[1025];
	char	*result_str;

	sz = 1;
	result_str = NULL;
	while (sz)
	{
		sz = read(fd, buff, 1024);
		if (sz == -1)
		{
			ft_free(result_str);
			exit_parsing_error(app, "error reading file");
		}
		if (sz == 0 && !result_str)
			break ;
		buff[sz] = '\0';
		result_str = ft_strjoin_free(result_str, buff, 1);
		if (!result_str)
			exit_parsing_error(app, "malloc error");
		ft_bzero(buff, 1025);
	}
	return (result_str);
}

char	*read_map_file(t_app *app, const char *path_to_map)
{
	char	*result_str;
	int		fd;

	fd = open(path_to_map, O_RDONLY);
	if (fd == -1)
		exit_parsing_error(app, "error opening file");
	result_str = __read_entire_file(app, fd);
	close(fd);
	if (!result_str)
		exit_parsing_error(app, "error reading file");
	return (result_str);
}
