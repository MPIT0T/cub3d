/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:27:45 by cesar             #+#    #+#             */
/*   Updated: 2024/05/30 11:27:08 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	print_err(int err)
{
	if (err == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (err == ALLOC_FAILURE)
		return (printf("[%d] memory allocation failure\n", err), ALLOC_FAILURE);
	return (EXIT_SUCCESS);
}
