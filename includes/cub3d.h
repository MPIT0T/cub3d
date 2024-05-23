/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:08 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/23 15:40:46 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/incs/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include <math.h>
# include <fcntl.h>

/* ************************************************************************** */
/*                              DEFINES                                       */
/* ************************************************************************** */

# define DEF_NO ""
# define DEF_SO ""
# define DEF_WE ""
# define DEF_EA ""
# define DEF_C ""	//voir si une struct est mieux qu'un char *
# define DEF_N ""

/* ************************************************************************** */
/*                              STRUCTS                                       */
/* ************************************************************************** */

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_element
{
	char	type;
}	t_elem;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	*c;
	t_color	*f;
	t_elem	**map;
}	t_map;

typedef struct s_data
{
	t_map	*map;
}	t_data;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

/*   MAIN   */

/*   PARSING   */
//parsing.c
int	parsing_map(t_data *data, const char *path_to_map);

/*   EXIT   */
//exit.c
void	exit_error(t_data *data);
//free.c
void	free_data(t_data *data);


#endif