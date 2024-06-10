/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:09 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/03 17:29:46 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	skip_blanks(char *str, size_t *i)
{
	while (str[*i] && ft_isblank(str[*i]))
		(*i)++;
}

char	*ft_strndup(t_app *app, char *str, size_t size)
{
	char	*result;

	result = malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		exit_error(app, EXIT_MALLOC);
	ft_strlcpy(result, str, size + 1);
	return (result);
}
