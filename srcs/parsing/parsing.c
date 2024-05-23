/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:25:18 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/23 16:10:52 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_all(int fd)
{
	char	*result_str;
	char	*tmp;
	ssize_t	sz;
	char	buff[1025];

	result_str = NULL;
	sz = 1;
	while (sz)
	{
		sz = read(fd, buff, 1024);
		if (sz == -1)
			return (perror("cub3d:"), free(result_str), NULL);
		buff[sz] = '\0';
		tmp = ft_strjoin(result_str, buff);
		free(result_str);
		if (!tmp)
			return (perror("cub3d:"), NULL);
		result_str = tmp;
	}
	return (result_str);
}

char	*read_map_file(const char *path_to_map)
{
	char	*result_str;
	int		fd;

	fd = open(path_to_map, O_RDONLY);
	if (fd == -1)
		return (perror("cub3d:"), NULL);
	result_str = read_all(fd);
	close(fd);
	return (result_str);
}

int	parsing_map(t_data *data, const char *path_to_map)
{
	char	*map_full_str;

	map_full_str = read_map_file(path_to_map);
	if (map_full_str == NULL)
		exit_error(data);
	// ft_printf("%s\n", map_full_str);
	free(map_full_str);
	return (0);
}