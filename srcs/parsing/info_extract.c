/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:34:33 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/30 13:25:28 by mpitot           ###   ########.fr       */
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
	if ((str[i] != ',' && state == 'g') || state !='g')
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

	color = malloc(sizeof(t_color));
	if (!color)
		exit_error(app, EXIT_MALLOC);
	if (__check_color(str))
	{
		ft_free(color);
		exit_parsing_error(app, "invalid color format");
	}
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
	i+= ft_strlen(id);
	while (str[i] && str[i] == ' ')
		i++;
	color = __parse_color(app, &str[i]);
	if (verify_color(color))
		exit_parsing_error(app, "invalid color format");
	result = 0;
	result |= color->r << 16;
	result |= color->g << 8;
	result |= color->b;
	return (result);
}

char	*get_texture(t_app *app, char *str, char *id)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*result;

	i = 0;
	while (str[i] && ft_strncmp(&str[i], id, ft_strlen(id)))
		i++;
	if (str[i] == '\0')
		return (NULL);
	i += ft_strlen(id);
	while (str[i] && str[i] == ' ')
		i++;
	size = 0;
	while (str[i + size] && !ft_isblank(str[i + size]) && str[i + size] != '\n')
		size++;
	j = 0;
	while (str[i + size + j] && ft_isblank(str[i + size + j]))
		j++;
	if (str[i + size + j] && str[i + size + j] != '\n')
		return (NULL);
	result = malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		exit_error(app, EXIT_MALLOC);
	ft_strlcpy(result, &str[i], size + 1);
	return (result);
}