/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:32:10 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/23 17:32:33 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	__read_entire_file(int fd, char *result_str)
{
	char	*tmp;
	ssize_t	sz;
	char	buff[1025];

	sz = 1;
	while (sz)
	{
		sz = read(fd, buff, 1024);
		if (sz == -1)
			return (free(result_str), 1);
		buff[sz] = '\0';
		tmp = ft_strjoin(result_str, buff);
		free(result_str);
		if (!tmp)
			return (1);
		result_str = tmp;
	}
	return (0);
}

char	*read_map_file(t_data *data, const char *path_to_map)
{
	char	*result_str;
	int		fd;

	fd = open(path_to_map, O_RDONLY);
	if (fd == -1)
		exit_error(data, 1);
	result_str = NULL;
	if (__read_entire_file(fd, result_str))
	{
		perror("cub3d");
		close(fd);
		exit_error(data, 0);
	}
	close(fd);
	return (result_str);
}
