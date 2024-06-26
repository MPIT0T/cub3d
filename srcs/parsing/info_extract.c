/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:34:33 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/14 14:19:15 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	__check_color_part(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isblank(str[i]))
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (ft_isblank(str[i]))
		i++;
	if (i == 0)
		return (-1);
	return (i);
}

static int	__check_color(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	i += __check_color_part(&str[i]);
	if (str[i] != ',')
		return (1);
	i++;
	i += __check_color_part(&str[i]);
	if (str[i] != ',')
		return (1);
	i++;
	i += __check_color_part(&str[i]);
	if (i != len)
		return (1);
	return (0);
}

static t_color	*__parse_color(t_app *app, char *str)
{
	size_t	i;
	t_color	*color;

	if (ft_strncmp(str, "tex", 3) == 0)
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
	if (!color && ft_strncmp("F ", id, 2) == 0)
		return (app->pos->floor_tex = true, 0);
	if (!color && ft_strncmp("C ", id, 2) == 0)
		return (app->pos->roof_tex = true, 0);
	if (verify_color(color))
		return (ft_free(color), exit_parsing_error(app, "invalid color"), 1);
	result = 0;
	result |= color->r << 16;
	result |= color->g << 8;
	result |= color->b;
	return (ft_free(color), result);
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
