/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:50:13 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/31 10:49:14 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	__goto_newline(const char *str, size_t *i)
{
	while (str[*i] && str[*i] != '\n')
		(*i)++;
	while (str[*i] == '\n')
		(*i)++;
}

static size_t	__get_longest_line(char **tab)
{
	size_t	i;
	size_t	result;

	i = -1;
	result = 0;
	while (tab[++i])
	{
		if (ft_strlen(tab[i]) > result)
			result = ft_strlen(tab[i]);
	}
	return (result);
}

static char	*__make_new_map_line(char *old_line, size_t len)
{
	char	*new;
	size_t	i;

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);		//TODO remonter l'erreur
	i = -1;
	while (old_line[++i])
		new[i] = old_line[i];
	while (i < len)
		new[i++] = ' ';
	new[len] = '\0';
	ft_free(old_line);
	return (new);
}

static void	__make_map_rect(t_app *app)
{
	size_t	i;

	app->pos->MAP_WIDTH = __get_longest_line(app->pos->map);
	i = -1;
	while (app->pos->map[++i])
	{
		if (ft_strlen(app->pos->map[i]) < (size_t) app->pos->MAP_WIDTH)
		{
			app->pos->map[i] = __make_new_map_line(app->pos->map[i], app->pos->MAP_WIDTH);
			if (!app->pos->map[i])
				exit_error(app, EXIT_MALLOC);
		}
	}
	app->pos->MAP_HEIGHT = i;
}

void	parse_map(t_app *app, char *full_file_string)
{
	size_t	i;

	i = 0;
	while (full_file_string[i] && !is_map_line(&full_file_string[i]))
		__goto_newline(full_file_string, &i);
	if (!full_file_string[i])
		exit_parsing_error(app, "map not found in file");
	if (check_double_nl(&full_file_string[i]))
		exit_parsing_error(app, "empty line found in map");
	app->pos->map = ft_split(&full_file_string[i], '\n');
	if (!app->pos->map)
		exit_error(app, EXIT_MALLOC);
	__make_map_rect(app);
	if (verify_map_chars(app->pos->map))
		exit_parsing_error(app, "invalid map character");
	if (verify_map_border(app->pos->map))
		exit_parsing_error(app, "map border not closed");
}
