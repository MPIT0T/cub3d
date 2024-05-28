/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:07:17 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/28 12:56:48 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_data_structs(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (1);
	data->err = malloc(sizeof(int));
	if (!data->err)
		return (free(data->map), 1);
	data->map->no = NULL;
	data->map->so = NULL;
	data->map->we = NULL;
	data->map->ea = NULL;
	data->map->f = NULL;
	data->map->c = NULL;
	data->full_file_string = NULL;
	return (0);
}

void	ft_check_args(int ac, char **av)
{
	size_t	len;

	len = ft_strlen(av[1]);
	if (ac == 2)
	{
		if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u'
			|| av[1][len - 3] != 'c' || av[1][len - 4] != '.')
			ft_printf_fd(2, "%s: bad map extension\n", ERRMSG);
		else
			return ;
		exit(EXIT_ARGS);
	}
	if (ac < 2)
		ft_printf_fd(2, "%s: map not provided\n", ERRMSG);
	if (ac > 2)
		ft_printf_fd(2, "%s: too many arguments\n", ERRMSG);
	exit(EXIT_ARGS);
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_check_args(ac, av);
	if (init_data_structs(&data))
		return (EXIT_MALLOC);
	parsing(&data, av[1]);
	free_data(&data);
	return (EXIT_SUCCESS);
}
