/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:08 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/30 13:28:28 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/incs/libft.h"
# include "../mlx_linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdint.h>

/* ************************************************************************** */
/*                              DEFINES                                       */
/* ************************************************************************** */

# define SCREEN_WIDTH	1920
# define SCREEN_HEIGHT	1080
# define TEX_WIDTH		64
# define TEX_HEIGHT		64

# define N 0
# define S 1
# define E 2
# define W 3

# define BLUE			0x3a8399
# define YELLOW			0xebab34
# define YELLOW_SIDE	0xa67924
# define BROWN			0x7a5631
# define BLACK			0x000000

# define ERRMSG "\e[0;91mError\e[0m"

# define MAP_CHARS " 01NSWE"

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
# define EXIT_MLX 6


/* ************************************************************************** */
/*                                 ENUM                                       */
/* ************************************************************************** */






/* ************************************************************************** */
/*                                STRUCTS                                     */
/* ************************************************************************** */

# include <../mlx_linux/mlx.h>
# include <../libft/incs/libft.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdint.h>

# define MAP_WIDTH		24
# define MAP_HEIGHT		24
# define SCREEN_WIDTH	1920
# define SCREEN_HEIGHT	1080
# define TEX_WIDTH		64
# define TEX_HEIGHT		64

# define N 0
# define S 1
# define E 2
# define W 3

# define EXIT_SUCCESS	0
# define ALLOC_FAILURE	1

# define BLUE			0x3a8399
# define YELLOW			0xebab34
# define YELLOW_SIDE	0xa67924
# define BROWN			0x7a5631
# define BLACK			0x000000

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
} t_img;

typedef	struct	s_tex
{
	char	*file;
	int		width;
	int		height;
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		endian;
	int		line_length;
	uint32_t	*tex_value;
} t_tex;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_pos
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	unsigned int	c;
	unsigned int	f;
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double			time;
	double			oldTime;
	double			cameraX; //x-coordinate in camera space
	double			rayDirX;
	double			rayDirY;
	int				mapX; //which box of the map we're in
	int				mapY;
	double			sideDistX; //length of ray from current position to next x or y-side
	double			sideDistY;
	double			deltaDistX;
	double			deltaDistY;
	double			perpWallDist;
	int				stepX; //what direction to step in x or y-direction (either +1 or -1)
	int				stepY;
	int				hit; //was there a wall hit?
	int				side; //was a NS or a EW wall hit?
	int				h;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	int				color;
	double			oldDirX;
	double			oldPlaneX;
	double			moveSpeed;
	double			rotSpeed;
	bool			motion_up;
	bool			motion_down;
	bool			motion_left;
	bool			motion_right;
	bool			rotate_left;
	bool			rotate_right;
	int				**px;
	char			wallDir;
	t_tex			*tex;
	uint32_t		**textures;

} t_pos;

typedef struct s_app
{
	int		*err;
	t_pos	*pos;
	t_img	*img;
	char	*full_file_string;
}	t_app;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

/*   MAIN   */

/*   PARSING   */
//parsing.c
int		parsing(t_app *app, const char *path_to_map);
//read_map_file.c
char	*read_map_file(t_app *app, const char *path_to_map);
//info_extract.c
unsigned int	get_color(t_app *app, char *str, char *id);
char	*get_texture(t_app *app, char *str, char *id);
//info_verif.c
void	verify_infos(t_app *app);
int		verify_color(t_color *color);
//map_parsing.c
void	parse_map(t_app *app, char *full_file_string);
//map_verif.c
int	is_map_line(char *str);
int	verify_map_border(char **map);
int	verify_map_chars(char **map);
int	check_double_nl(const char *str);

/*   EXIT   */
//exit.c
void	exit_error(t_app *app, int error);
void	exit_parsing_error(t_app *app, const char *msg);
//free.c
void	free_app(t_app *app);

int	construct_app(t_app *app);
int	initiate_mlx(t_app *app);
int	yline(t_app *app, int x, int yStart, int yEnd, int color);
int	xline(t_app *app, int y, int xStart, int xEnd, int color);
int	line(t_img *img, int startX, int startY, int nextX, int nextY, int color);
int	change_motion_keypress(int key, t_app *app);
int	change_motion_keyrelease(int key, t_app *app);
int	motion(t_app *app);
int	new_image(t_app *app);
int	game_loop(t_app *app);
int	initiate_textures(t_app *app);
int	raycasting_loop(t_pos *pos, t_img *img, t_app *app);
void	px_put(t_img *img, int x, int y, int color);

#endif