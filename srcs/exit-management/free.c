/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:34:59 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/03 13:26:58 by cefuente         ###   ########.fr       */
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
	if (app->img->mlx)
		free(app->img->mlx);
	free(app->img);
}

void	free_tex(t_app *app)
{
	size_t	i;

	i = -1;
	while (++i < 10)
		mlx_destroy_image(app->img->mlx, app->pos->tex[i].img);
	i = -1;
	while (++i < SCREEN_HEIGHT)
		ft_free(app->pos->px[i]);
	ft_free(app->pos->px);
	ft_free(app->pos->tex);
	ft_free(app->pos);
}

void	free_ghosts(t_list **lst, t_ghost *ghosts, int map_width)
{
	(void) map_width;
	// while (++i < GHOSTS_NUMBER)
	// {
	// 	free(ghosts[i].y_dirs_pref);
	// 	if (ghosts[i].memory)
	// 		freetab((void **)ghosts[i].memory, map_width);
	// }
	free(ghosts);
	lstfree(lst);
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
		free_ghosts(&app->ghosts_lst, app->ghosts, app->pos->MAP_WIDTH);
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
