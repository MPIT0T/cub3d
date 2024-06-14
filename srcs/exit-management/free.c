/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:34:59 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/14 15:39:54 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	freetab(void **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
}

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
	else if (app->img->mlx && app->img->mlx_win)
	{
		mlx_destroy_window(app->img->mlx, app->img->mlx_win);
		mlx_destroy_display(app->img->mlx);
	}
	else if (app->img->mlx)
		mlx_destroy_display(app->img->mlx);
	if (app->img->mlx)
		free(app->img->mlx);
	free(app->img);
}

void	free_tex(t_app *app)
{
	size_t	i;

	i = -1;
	if (app->pos->tex)
	{
		while (++i < 11 && app->pos->tex[i].img)
			mlx_destroy_image(app->img->mlx, app->pos->tex[i].img);
	}
	ft_free(app->pos->tex);
	i = -1;
	if (app->pos->px)
	{
		while (++i < SCREEN_HEIGHT)
			ft_free(app->pos->px[i]);
	}
	ft_free(app->pos->px);
	ft_free(app->pos);
}

void	free_app(t_app *app)
{
	if (app)
	{
		ft_free(app->full_file_string);
		if (app->pos)
		{
			ft_free(app->pos->no);
			ft_free(app->pos->so);
			ft_free(app->pos->we);
			ft_free(app->pos->ea);
			ft_free(app->pos->z_prox);
			ft_free_tab(app->pos->map);
		}
		lstfree(&app->ghosts_lst);
		free(app->ghosts);
		free_tex(app);
		free_mlx(app);
	}
}

void	free_parsing_exit(t_app *app)
{
	if (app)
	{
		ft_free(app->full_file_string);
		if (app->pos)
		{
			ft_free_tab(app->pos->map);
			ft_free(app->pos->z_prox);
			ft_free(app->pos->no);
			ft_free(app->pos->so);
			ft_free(app->pos->we);
			ft_free(app->pos->ea);
		}
		ft_free(app->img);
		ft_free(app->pos);
	}
}
