/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:34:59 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/30 11:50:20 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_mlx(t_app *app)
{
	if (!app || !app->img)
		return ;
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

void	free_app(t_app *app)
{
	if (app)
	{
		free_mlx(app);
		ft_free(app->map->no);
		ft_free(app->map->so);
		ft_free(app->map->we);
		ft_free(app->map->ea);
		ft_free(app->map->f);
		ft_free(app->map->c);
		ft_free(app->full_file_string);
		if (app->map)
			ft_free_tab(app->map->map);
		ft_free(app->map);
	}
}
