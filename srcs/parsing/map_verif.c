/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:47:15 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/29 11:48:50 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_double_nl(const char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\n' && (str[i + 1] == '\n' || !str[i + 1]))
			return (1);
	}
	return (0);
}

int	verify_map_chars(char **map)
{
	size_t	i;
	size_t	j;
	int		player;

	i = -1;
	player = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSWE", map[i][j]))
				player++;
			if (!ft_strchr(MAP_CHARS, map[i][j]))
				return (1);
		}
	}
	if (player != 1)
		return (2);
	return (0);
}

int	verify_map_border(char **map)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
			{
				if (map[i + 1] && map [i + 1][j] == ' ')
					return (1);
				if (i == 0 || (map[i - 1] && map [i - 1][j] == ' '))
					return (1);
				if (map[i][j + 1] && map [i][j + 1] == ' ')
					return (1);
				if (j == 0 || (map[i][j - 1] && map [i][j - 1] == ' '))
					return (1);
			}
		}
	}
	return (0);
}

int	is_map_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isblank(str[i]))
		i++;
	while (str[i] && str[i] == '\n')
		i++;
	if (ft_strncmp(&str[i], ID_NORTH, ft_strlen(ID_NORTH)) == 0
		|| ft_strncmp(&str[i], ID_SOUTH, ft_strlen(ID_SOUTH)) == 0
		|| ft_strncmp(&str[i], ID_WEST, ft_strlen(ID_WEST)) == 0
		|| ft_strncmp(&str[i], ID_EAST, ft_strlen(ID_EAST)) == 0
		|| ft_strncmp(&str[i], ID_FLOOR, ft_strlen(ID_FLOOR)) == 0
		|| ft_strncmp(&str[i], ID_CEILING, ft_strlen(ID_CEILING)) == 0)
		return (0);
	return (1);
}
