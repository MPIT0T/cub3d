/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:27:45 by cesar             #+#    #+#             */
/*   Updated: 2024/05/27 10:32:14 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	print_err(int err)
{
	if (err == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (err == ALLOC_FAILURE)
		return (printf("[%d] memory allocation failure\n", err), ALLOC_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_err(t_app *app)
{
	print_err(app->err);
	if (app->pos)
		free(app->pos);
	if (app->img)
	{
		if (app->img->mlx && app->img->mlx_win && app->img->img)
		{
			mlx_destroy_image(app->img->mlx, app->img->img);
			mlx_destroy_window(app->img->mlx, app->img->mlx_win);
			mlx_destroy_display(app->img->mlx);
		}
		if (app->img->mlx)
			free(app->img->mlx);
		free(app->img);
	}
	if (app->err == 3)
		exit(EXIT_SUCCESS);
	return (app->err);
}