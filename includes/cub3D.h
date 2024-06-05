/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:08 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/05 02:57:15 by cesar            ###   ########.fr       */
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

# define ROOF_TEX "./textures/roof.xpm"
# define FLOOR_TEX "./textures/floor.xpm"
# define DOOR_TEX "./textures/door.xpm"
# define GHOST_TEX "./textures/ghost.xpm"

# define N 0
# define S 1
# define E 2
# define W 3

# define GHOSTS_NUMBER 2

# define BLUE			0x3a8399
# define RED			0xFF0000
# define YELLOW			0xffff00
# define YELLOW_SIDE	0xa67924
# define BROWN			0x7a5631
# define BLACK			0x000000
# define WHITE			0xffffff
# define GREY			0x242b38

# define MAP_CHARS " 012NSWE"

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

typedef struct	s_sptr
{
	double	x;
	double	y;
	double	invDet;
	double	trans_X;
	double	trans_Y;
	int		spriteScreenX;
	int		height;
	int		width;
	int		y_start;
	int		x_start;
	int		y_end;
	int		x_end;
	int		tex_x;
	int		tex_y;
	uint32_t	*tex_content;
}	t_sprt;

typedef struct	s_triplet
{
	size_t	a;
	size_t	b;
	size_t	c;
}	t_triplet;

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

typedef struct	s_ghost
{
	double	x;
	double	y;
	char	dir;
	int		dir_x;
	int		dir_y;
	double	move_speed;
	char	*dirset;
	char	*x_dirs_pref;
	char	*y_dirs_pref;
	double	player_dist;
	int		is_theone;
	int		rank;
}	t_ghost;

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
	ssize_t			MAP_WIDTH;
	ssize_t			MAP_HEIGHT;
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
	double			rotSpeedSave;
	bool			motion_up;
	bool			motion_down;
	bool			motion_left;
	bool			motion_right;
	bool			rotate_left;
	bool			rotate_right;
	uint32_t		**px;
	char			wallDir;
	t_tex			*tex;
	uint32_t		**textures;
	int				*z_prox;

} t_pos;

typedef struct s_app
{
	int		*err;
	t_pos	*pos;
	t_img	*img;
	char	*full_file_string;
	t_ghost	*ghosts;
	t_list	*ghosts_lst;
}	t_app;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

/*   MAIN   */

/*   MINIMAP   */
//minimap.c
void	put_minimap(t_app *app);
//minimap_utils.c
void	set_frame_dimensions(t_app *app, t_minimap *mm);
void	get_minimap_pos(t_app *app, t_minimap *mm);
void	put_minimap_frame(t_app *app, t_minimap *mm);
void	put_minimap_pixel(t_app *app, t_minimap *mm);
void	put_minimap_on_screen(t_app *app, t_minimap *mm);
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
int	check_multiple_id_instances(char *str, char *id);
//map_parsing.c
void	parse_map(t_app *app, char *full_file_string);
//map_verif.c
int	is_map_line(char *str);
int	verify_map_border(char **map);
int	verify_map_chars(char **map);
int	check_double_nl(const char *str);
//parsing_utils.c
void	skip_blanks(char *str, size_t *i);
char	*ft_strndup(t_app *app, char *str, size_t size);

/*   EXIT   */
//exit.c
void	exit_error(t_app *app, int error);
void	exit_parsing_error(t_app *app, const char *msg);
//free.c
void	free_app(t_app *app);
void	free_parsing_exit(t_app *app);

int		construct_app(t_app *app);
int		initiate_mlx(t_app *app);
int		change_motion_keypress(int key, t_app *app);
int		change_motion_keyrelease(int key, t_app *app);
int		mouse_motion(int x, int y, t_app *app);
int		motion(t_app *app);
int		new_image(t_app *app);
int		game_loop(t_app *app);
int		initiate_textures(t_app *app);
int		raycasting_loop(t_pos *pos, t_img *img, t_app *app);
int		get_wall_texture(t_app *app, t_pos *pos, t_walltex *walltex);
int		get_horizontal_texture(t_pos *pos, t_horiztex *horiztex);
void	which_dir(t_pos *pos, char *set, int asdlfk);
void	px_put(t_img *img, int x, int y, int color);
void	draw_screen(t_pos *pos, t_img *img);
void	clear_px_buffer(uint32_t **px);

/* GHOSTS */
int		get_opposite_of_player(t_pos *pos);
int		spawning_point(t_pos *pos, t_ghost *ghost, int quarter);
int		pop_some_ghosts(t_app *app);
void 	print_map(t_pos *pos);
int		ghosts_are_coming(t_app *app);
int		sort_and_cast_sprites(t_pos *pos, t_list **ghosts_lst);

#endif