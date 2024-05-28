/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:08 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/28 16:34:06 by mpitot           ###   ########.fr       */
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

# define ERRMSG "\e[0;91mError\e[0m"

# define VOID -1
# define ROOM 0
# define WALL 1
# define FACING_NORTH 2
# define FACING_SOUTH 3
# define FACING_WEST 4
# define FACING_EAST 5

# define ID_NORTH "NO "
# define ID_SOUTH "SO "
# define ID_WEST "WE "
# define ID_EAST "EA "
# define ID_FLOOR "F "
# define ID_CEILING "C "

# define EXIT_SUCCESS 0
# define EXIT_MALLOC 1
# define EXIT_ARGS 2
# define EXIT_READ 3
# define EXIT_OPEN 4
# define EXIT_PARSING 5


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

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	*c;
	t_color	*f;
	int		**map;
	size_t	weight;
	size_t	height;
}	t_map;

typedef struct s_data
{
	int		*err;
	t_map	*map;
	char	*full_file_string;
}	t_data;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

/*   MAIN   */

/*   PARSING   */
//parsing.c
int		parsing(t_data *data, const char *path_to_map);
//read_map_file.c
char	*read_map_file(t_data *data, const char *path_to_map);
//info_extract.c
t_color *get_color(t_data *data, char *str, char *id);
char	*get_texture(t_data *data, char *str, char *id);
//info_verif.c
void	verify_infos(t_data *data);

/*   EXIT   */
//exit.c
void	exit_error(t_data *data, int error);
void	exit_parsing_error(t_data *data, const char *msg);
//free.c
void	free_data(t_data *data);

#endif