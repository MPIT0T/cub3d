/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:25:18 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/28 16:34:06 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isblank(str[i]))
		i++;
	if (ft_strncmp(&str[i], ID_NORTH, ft_strlen(ID_NORTH)) != 0
		|| ft_strncmp(&str[i], ID_SOUTH, ft_strlen(ID_SOUTH)) != 0
		|| ft_strncmp(&str[i], ID_WEST, ft_strlen(ID_WEST)) != 0
		|| ft_strncmp(&str[i], ID_EAST, ft_strlen(ID_EAST)) != 0
		|| ft_strncmp(&str[i], ID_FLOOR, ft_strlen(ID_FLOOR)) != 0
		|| ft_strncmp(&str[i], ID_CEILING, ft_strlen(ID_CEILING)) != 0)
		return (1);
	return (0);
}

void	goto_newline(const char *str, size_t *i)
{
	while (str[*i] && str[*i] != '\n')
		(*i)++;
	if (str[*i] == '\n')
		(*i)++;
}

int	ft_check_double_nl(const char *str)
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

size_t	count_map_lines(char *str)
{

}

size_t	ft_linelen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	ft_free_int_tab(int **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		ft_free(tab[i]);
	ft_free(tab);
}

size_t	ft_copyline_map(int *tab, char *str)
{
	size_t	i;

	i = -1;
	while (str[++i] && str[i] != '\n')
	{
		if (str[i] == ' ')
			tab[i] = VOID;
		else if (str[i] == '1')
			tab[i] = WALL;
		else if (str[i] == '0')
			tab[i] = ROOM;
		else if (str[i] == 'N')
			tab[i] = FACING_NORTH;
		else if (str[i] == 'S')
			tab[i] = FACING_SOUTH;
		else if (str[i] == 'W')
			tab[i] = FACING_WEST;
		else if (str[i] == 'E')
			tab[i] = FACING_EAST;
		else
			return (ft_free(tab), 0);
	}
	return (++i);
}

int		**split_map(t_data *data, char *str)
{
	size_t	i;
	size_t	j;
	size_t	size;
	int		**tab;

	size = count_map_lines(str);
	tab = malloc(sizeof(int *) * (size));
	if (!tab)
		exit_error(data, EXIT_MALLOC);
	i = -1;
	while (++i < size)
	{
		j = 0;
		tab[i] = malloc(sizeof(ft_linelen(&str[j])));
		if (!tab[i])
			return (ft_free_int_tab(tab), exit_error(data, EXIT_MALLOC), NULL);
		j += ft_copyline_map(tab[i], &str[j]);
		if (!tab[i])
			return (ft_free_int_tab(tab),
					exit_parsing_error(data, "map: invalid character"), NULL);
	}
	return (tab);
}

void	parse_map(t_data *data, char *full_file_string)
{
	size_t	i;
	int		**map;

	i = 0;
	while (full_file_string[i] && !is_map_line(&full_file_string[i]))
		goto_newline(full_file_string, &i);
	if (!full_file_string[i])
		exit_parsing_error(data, "map not found in file");
	if (ft_check_double_nl(&full_file_string[i]))
		exit_parsing_error(data, "empty line found in map");
	map = split_map(data, &full_file_string[i]);

}

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

	return (0);
}
