/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:27:45 by cesar             #+#    #+#             */
/*   Updated: 2024/05/24 10:07:13 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	print_err(int err)
{
	if (err == 0)
		return (0);
	else if (err == 1)
		return (printf("[%d] memory allocation failure\n", err), 1);
	return (0);
}

int	handle_err(t_app *app, int err)
{
	print_err(err);
	if (app->pos)
		free(app->pos);
	if (app->img)
	{
		if (app->img->mlx)
			
		free(app->img);
	}
	return (err);
}