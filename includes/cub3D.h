/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:08 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/03 11:48:09 by cefuente         ###   ########.fr       */
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
// # define MAP_WIDTH		24
// # define MAP_HEIGHT		24

# define N 0
# define S 1
# define E 2
# define W 3

# define BLUE			0x3a8399
# define RED			0xFF0000
# define YELLOW			0xffff00
# define YELLOW_SIDE	0xa67924
# define BROWN			0x7a5631
# define BLACK			0x000000
# define WHITE			0xffffff
# define GREY			0x242b38

# define MAP_CHARS " 01NSWE"

# define ID_NORTH "NO "
# define ID_SOUTH "SO "
# define ID_WEST "WE "
# define ID_EAST "EA "
# define ID_FLOOR "F "
# define ID_CEILING "C "

# define ERRMSG "\e[0;91mError\e[0m"
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

typedef	struct	s_connection
{
	bool	n;
	bool	s;
	bool	w;
	bool	e;
	bool	nw;
	bool	ne;
	bool	sw;
	bool	se;
}	t_con;

typedef struct	s_minimap
{
	int		pixX;
	int		pixY;
	double	startX;
	double	intX;
	double	startY;
	double	intY;
	int		mapSizeX;
	int		mapSizeY;
}	t_minimap;

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

typedef struct	s_walltex
{
	uint32_t	*tex_content;
	int 	texX;
	int		texY;
	double	wallX;
	double	step;
	double	texPos;
	int		texNum;
	int		x;
} t_walltex;

typedef struct	s_horiztex
{
	uint32_t	*floor_tex_content;
	uint32_t	*roof_tex_content;
	uint32_t floor_tex_px;
	uint32_t roof_tex_px;
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		p;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
	int		floorTexture;
	int		ceilingTexture;
	int		y;

} t_horiztex;

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
	size_t			MAP_WIDTH;
	size_t			MAP_HEIGHT;
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
void	put_minimap(t_app *app);
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
int	change_motion_keypress(int key, t_app *app);
int	change_motion_keyrelease(int key, t_app *app);
int	motion(t_app *app);
int	new_image(t_app *app);
int	game_loop(t_app *app);
int	initiate_textures(t_app *app);
int	raycasting_loop(t_pos *pos, t_img *img, t_app *app);
int	 draw_wall_texture(t_app *app, t_pos *pos, t_walltex *walltex);
int	draw_horizontal_texture(t_app *app, t_pos *pos, t_horiztex *horiztex);
void	px_put(t_img *img, int x, int y, int color);

#endif