/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:34:59 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/29 14:45:09 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_data *data)
{
	ft_free(data->map->no);
	ft_free(data->map->so);
	ft_free(data->map->we);
	ft_free(data->map->ea);
	ft_free(data->map->f);
	ft_free(data->map->c);
	ft_free(data->full_file_string);
	if (data->map)
		ft_free_tab(data->map->map);
	ft_free(data->map);
}
