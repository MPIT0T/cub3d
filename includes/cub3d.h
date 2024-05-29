/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:03:07 by cesar             #+#    #+#             */
/*   Updated: 2024/05/29 09:07:02 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../mlx_linux/mlx.h>
# include <../libft/incs/libft.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define MAP_WIDTH		24
# define MAP_HEIGHT		24
# define SCREEN_WIDTH	1920
# define SCREEN_HEIGHT	1080

# define EXIT_SUCCESS	0
# define ALLOC_FAILURE	1

# define UP		65362
# define DOWN	65364
# define LEFT	65361
# define RIGHT	65363
# define ESC	65307

# define BLUE			0x3a8399
# define YELLOW			0xebab34
# define YELLOW_SIDE	0xa67924
# define BROWN			0x7a5631

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
	double	cameraX; //x-coordinate in camera space
	double	rayDirX;
	double	rayDirY;
	int		mapX; //which box of the map we're in
	int		mapY;
	double	sideDistX; //length of ray from current position to next x or y-side
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX; //what direction to step in x or y-direction (either +1 or -1)
	int		stepY;
	int		hit; //was there a wall hit?
	int		side; //was a NS or a EW wall hit?
	int		h;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	double	oldDirX;
	double	oldPlaneX;
	double	moveSpeed;
	double	rotSpeed;
	bool	motion_up;
	bool	motion_down;
	bool	motion_left;
	bool	motion_right;
	bool	rotate_left;
	bool	rotate_right;
	int		**px;
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
int	yline(t_app *app, int x, int yStart, int yEnd, int color);
int	xline(t_app *app, int y, int xStart, int xEnd, int **px_tab);
int	line(t_img *img, int startX, int startY, int nextX, int nextY, int color);
int	change_motion_keypress(int key, t_app *app);
int	change_motion_keyrelease(int key, t_app *app);
int	motion(t_app *app);
int	new_image(t_app *app);
int	game_loop(t_app *app);

int	raycasting_loop(t_pos *pos, t_img *img, t_app *app);

#endif