/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:29:15 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/28 10:25:49 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(t_data *data, int error)
{
	int		err;

	err = *data->err;
	if (error != -1)
		err = error;
	if (err == EXIT_MALLOC)
		ft_printf_fd(2, "%s: malloc error\n", ERRMSG);
	if (err == EXIT_OPEN)
		ft_printf_fd(2, "%s: error opening file\n", ERRMSG);
	if (err == EXIT_READ)
		ft_printf_fd(2, "%s: error reading file\n", ERRMSG);
	free_data(data);
	exit(err);
}

void	exit_parsing_error(t_data *data, const char *msg)
{
	if (!msg)
		perror(ERRMSG);
	else
		ft_printf_fd(2, "%s: %s\n", ERRMSG, msg);
	free_data(data);
	exit(EXIT_PARSING);
}
