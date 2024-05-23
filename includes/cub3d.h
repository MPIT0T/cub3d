/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:08 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/23 17:57:36 by mpitot           ###   ########.fr       */
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

# define DEFAULT_NORTH ""
# define DEFAULT_SOUTH ""
# define DEFAULT_WEST ""
# define DEFAULT_EAST ""
# define DEFAULT_FLOOR ""
# define DEFAULT_CEILING ""

# define ID_NORTH "NO"
# define ID_SOUTH "SO"
# define ID_WEST "WE"
# define ID_EAST "EA"
# define ID_FLOOR "N"
# define ID_CEILING "C"

/* ************************************************************************** */
/*                                 ENUM                                       */
/* ************************************************************************** */






/* ************************************************************************** */
/*                                STRUCTS                                     */
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
int		parsing_map(t_data *data, const char *path_to_map);
//read_map_file.c
char	*read_map_file(t_data *data, const char *path_to_map);

/*   EXIT   */
//exit.c
void	exit_error(t_data *data, int put_error);
//free.c
void	free_data(t_data *data);


#endif