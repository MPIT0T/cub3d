/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:08 by mpitot            #+#    #+#             */
/*   Updated: 2024/06/13 12:22:28 by mpitot           ###   ########.fr       */
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
# define FLOOR_TEX "./textures/v2_floor.xpm"
# define GHOST_TEX "./textures/ghost.xpm"
# define DOOR_TEX "./textures/v2_door.xpm"
# define OPEN_TEX "./textures/v2_open_door.xpm"
# define CLOSE_TEX "./textures/v2_close_door.xpm"
# define PAUSE_TEX "./textures/pause_menu.xpm"

# define GHOSTS_NUMBER 5
# define GHOSTS_SIZE 0.3

# define BLUE			0x0000FF
# define RED			0xFF0000
# define YELLOW			0xffdd00
# define YELLOW_SIDE	0xa67924
# define BROWN			0x7a5631
# define BLACK			0x000000
# define WHITE			0xffffff
# define GREY			0xe5e5e5

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

typedef enum e_door_dir
{
	none,
	north,
	south,
	west,
	east
}	t_door_dir;

typedef enum s_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_dir;

/* ************************************************************************** */
/*                                STRUCTS                                     */
/* ************************************************************************** */

typedef struct s_sptr
{
	double		x;
	double		y;
	double		trans_factor;
	double		trans_x;
	double		trans_y;
	int			sprite_x;
	int			height;
	int			width;
	int			y_start;
	int			x_start;
	int			y_end;
	int			x_end;
	int			tex_x;
	int			tex_y;
	uint32_t	*tex_content;
	int			y_start_flag;
}	t_sprt;

typedef struct s_triplet
{
	size_t	a;
	size_t	b;
	size_t	c;
}	t_triplet;

typedef struct s_connection
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

typedef struct s_minimap
{
	int		pix_x;
	int		pix_y;
	double	start_x;
	double	int_x;
	double	start_y;
	double	int_y;
	int		map_size_x;
	int		map_size_y;
}	t_minimap;

typedef struct s_d
{
	int	y[4];
	int	x[4];
}	t_d;

typedef struct s_ghost
{
	double	x;
	double	y;
	t_dir	dir;
	int		dir_x;
	int		dir_y;
	double	move_speed;
	int		*dirset;
	double	player_dist;
}	t_ghost;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}	t_img;

typedef struct s_walltex
{
	uint32_t	*tex_content;
	int			tex_x;
	int			tex_y;
	double		wall_x;
	double		step;
	double		tex_pos;
	int			tex_num;
	int			x;
}	t_walltex;

typedef struct s_horiztex
{
	uint32_t	*floor_tex_content;
	uint32_t	*roof_tex_content;
	uint32_t	floor_tex_px;
	uint32_t	roof_tex_px;
	float		raydir_x_start;
	float		raydir_y_start;
	float		raydir_x_end;
	float		raydir_y_end;
	int			p;
	float		pos_z;
	float		row_dist;
	float		floor_step_x;
	float		floor_step_y;
	float		floor_x;
	float		floor_y;
	int			roof_x;
	int			roof_y;
	int			t_x;
	int			t_y;
	int			y;
}	t_horiztex;

typedef struct s_tex
{
	char		*file;
	int			width;
	int			height;
	void		*img;
	char		*data;
	int			bits_per_pixel;
	int			endian;
	int			line_length;
	uint32_t	*tex_value;
}	t_tex;

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
	ssize_t			map_width;
	ssize_t			map_height;
	double			p_x;
	double			p_y;
	double			p_dir_x;
	double			p_dir_y;
	double			surf_x;
	double			surf_y;
	double			cam_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			raydist_x;
	double			raydist_y;
	double			raydelta_x;
	double			raydelta_y;
	double			wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				h;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				color;
	double			prev_p_dir_x;
	double			prev_surf_x;
	double			move_speed;
	double			rot_speed_arrows;
	double			rot_speed_mouse;
	bool			motion_up;
	bool			motion_down;
	bool			motion_left;
	bool			motion_right;
	bool			rotate_left_arrows;
	bool			rotate_right_arrows;
	bool			rotate_left_mouse;
	bool			rotate_right_mouse;
	int				**px;
	char			wall_dir;
	t_tex			*tex;
	int				*z_prox;
	t_door_dir		pointing_door;
	size_t			column;
	bool			found_door;
	bool			floor_tex;
	bool			roof_tex;
}	t_pos;

typedef struct s_app
{
	bool	pause;
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
//info_extract.c
unsigned int	get_color(t_app *app, char *str, char *id);
//minimap.c
void			put_minimap(t_app *app);
//minimap_utils.c
void			get_minimap_pos(t_app *app, t_minimap *mm);
void			put_minimap_frame(t_app *app, t_minimap *mm);
void			put_minimap_on_screen(t_app *app, t_minimap *mm);
/*   PARSING   */
//parsing.c
void			ft_check_args(int ac, char **av);
int				parsing(t_app *app, const char *path_to_map);
//read_map_file.c
char			*read_map_file(t_app *app, const char *path_to_map);
char			*get_texture(t_app *app, char *str, char *id);
//info_verif.c
void			verify_infos(t_app *app);
int				verify_color(t_color *color);
int				check_multiple_id_instances(char *str, char *id);
//map_parsing.c
void			parse_map(t_app *app, char *full_file_string);
//map_verif.c
int				is_map_line(char *str);
int				verify_map_border(char **map);
int				verify_map_chars(char **map);
int				check_double_nl(const char *str);
//parsing_utils.c
void			skip_blanks(char *str, size_t *i);
char			*ft_strndup(t_app *app, char *str, size_t size);
//set_start_vars.c
int				initiate_positions(t_app *app);

/*   EXIT   */
//exit.c
void			exit_error(t_app *app, int error);
void			exit_parsing_error(t_app *app, const char *msg);
//free.c
void			free_app(t_app *app);
void			free_parsing_exit(t_app *app);

/* RAYCASTING */
int				raycasting_loop(t_pos *pos, t_img *img, t_app *app);
void			which_dir(t_pos *pos, char *set, int asdlfk);

/* INPUT READING AND MOVEMENT*/
int				init_hook(t_app *app);
int				change_motion_keypress(int key, t_app *app);
int				change_motion_keyrelease(int key, t_app *app);
int				mouse_motion(int x, int y, t_app *app);
int				motion(t_app *app);
int				rotate(t_app *app);

/* INITIALIZATION */
int				game_loop(t_app *app);
int				construct_app(t_app *app);
int				initiate_mlx(t_app *app);

/* SCREEN */
void			draw_screen(t_pos *pos, t_img *img);
int				new_image(t_app *app);
void			px_put(t_img *img, int x, int y, int color);
void			clear_px_buffer(int **px);

/* TEXTURES */
int				initiate_textures(t_app *app);
int				get_wall_texture(t_app *app, t_pos *pos, t_walltex *walltex);
int				get_horizontal_texture(t_pos *pos, t_horiztex *horiztex);

/* GHOSTS */
typedef int		(*t_spawn_func)(t_pos *, t_ghost *);

int				get_opposite_of_player(t_pos *pos);
int				spawning_point(t_pos *pos, t_ghost *ghost);
int				pop_some_ghosts(t_app *app);
void			print_map(t_pos *pos);
int				ghosts_are_coming(t_app *app);
int				sort_and_cast_sprites(t_pos *pos, t_list **ghosts_lst);
void			sort_list(t_list **head);
void			lstfree(t_list **lst);
void			door_dir(t_pos *pos);
void			open_door(t_app *app);
int				put_door_button(t_app *app);

#endif