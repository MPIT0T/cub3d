/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:03:07 by cesar             #+#    #+#             */
/*   Updated: 2024/05/24 11:33:24 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../mlx_linux/mlx.h>
# include <../libft/incs/libft.h>
# include <math.h>
# include <stdio.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

# define EXIT_SUCCESS 0
# define ALLOC_FAILURE 1

typedef struct s_pos
{
	int map[MAP_WIDTH][MAP_HEIGHT];
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
} t_pos;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
} t_img;

typedef struct s_app
{
	t_pos	*pos;
	t_img	*img;
	int		err;
} t_app;

int	handle_err(t_app *app);
int	construct_app(t_app *app);
int	initiate_mlx(t_app *app);



#endif