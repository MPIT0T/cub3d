/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:34:33 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/12 13:59:23 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	__check_color(char *str)
{
	size_t	i;
	int		state;

	i = 0;
	state = 0;
	while (str[++i] && ft_isdigit(str[i]))
		state = 'r';
	if ((str[i] != ',' && state == 'r') || state != 'r')
		return (1);
	while (str[++i] && ft_isdigit(str[i]))
		state = 'g';
	if ((str[i] != ',' && state == 'g') || state != 'g')
		return (1);
	while (str[++i] && ft_isdigit(str[i]))
		state = 'b';
	while (str[i] && ft_isblank(str[i]))
		i++;
	if ((str[i] && str[i] != '\n') || state != 'b')
		return (1);
	return (0);
}

static t_color	*__parse_color(t_app *app, char *str)
{
	size_t	i;
	t_color	*color;

	if (ft_strcmp(str, "tex"))
		return (NULL);
	if (__check_color(str))
		exit_parsing_error(app, "invalid color format");
	color = malloc(sizeof(t_color));
	if (!color)
		exit_parsing_error(app, "malloc error");
	i = 0;
	color->r = ft_atoi(&str[i]);
	i += ft_intlen(color->r) + 1;
	color->g = ft_atoi(&str[i]);
	i += ft_intlen(color->g) + 1;
	color->b = ft_atoi(&str[i]);
	return (color);
}

unsigned int	get_color(t_app *app, char *str, char *id)
{
	size_t			i;
	t_color			*color;
	unsigned int	result;

	i = 0;
	while (str[i] && ft_strncmp(&str[i], id, ft_strlen(id)))
		i++;
	if (str[i] == '\0')
		exit_parsing_error(app, "missing color");
	i += ft_strlen(id);
	while (str[i] && str[i] == ' ')
		i++;
	color = __parse_color(app, &str[i]);
	if (!color && ft_strcmp("F", id))
		(app->pos->floor_tex = true);
	if (!color && ft_strcmp("C", id))
		(app->pos->roof_tex = true);
	if (verify_color(color))
		exit_parsing_error(app, "invalid color format");
	result = 0;
	result |= color->r << 16;
	result |= color->g << 8;
	result |= color->b;
	ft_free(color);
	return (result);
}

char	*get_texture(t_app *app, char *str, char *id)
{
	t_triplet	var;

	var.a = 0;
	while (str[var.a] && ft_strncmp(&str[var.a], id, ft_strlen(id)))
	{
		if ((var.a == 0 || str[var.a - 1] == '\n') && is_map_line(&str[var.a]))
			return (NULL);
		var.a++;
	}
	if (str[var.a] == '\0')
		return (NULL);
	var.a += ft_strlen(id);
	skip_blanks(str, &var.a);
	var.c = 0;
	while (str[var.a + var.c] && !ft_isblank(str[var.a + var.c])
		&& str[var.a + var.c] != '\n')
		var.c++;
	var.b = 0;
	while (str[var.a + var.c + var.b] && ft_isblank(str[var.a + var.c + var.b]))
		var.b++;
	if (str[var.a + var.c + var.b] && str[var.a + var.c + var.b] != '\n')
		return (NULL);
	return (ft_strndup(app, &str[var.a], var.c));
}
