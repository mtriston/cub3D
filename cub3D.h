#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"
#include <stdio.h> //TODO: delete
#include <limits.h>
#define FALSE 0
#define TRUE 1

#define MINIMAP_SCALE 0.3f

#define FOV_ANGLE 60 * (M_PI / 180) 

#define LEFT_ARROW 65361
#define UP_ARROW 65362
#define RIGHT_ARROW 65363
#define DOWN_ARROW 65364

typedef struct	s_player
{
	double		x;
	double		y;
	int			turn_direction;
	int			walk_direction;
	double		rotation_angle;
	double		walk_speed;
	double		turn_speed;
}				t_player;

typedef struct	s_ray
{
	double		ray_angle;
	double		distance;
	double		hit_x;
	double		hit_y;
	int			is_up;
	int			is_down;
	int			is_left;
	int			is_right;
	int			is_vertical_hit;
}				t_ray[1920];

typedef struct  s_ray_utils
{
	double		x_intercept;
	double		y_intercept;
	double		x_step;
	double		y_step;
	double		next_x;
	double		next_y;
	double		hit_x;
	double		hit_y;
	double		distance;
}				t_ray_utils;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_map
{
	char		**map;
	double		tile_size;
	int			floor_color;
	int			ceil_color;
}				t_map;

typedef struct	s_texture
{
	t_img		north;
	t_img		south;
	t_img		west;
	t_img		east;
	t_img		sprite;
}				t_texture;

typedef struct	s_screen
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;

}				t_screen;

typedef struct	s_vars
{
	t_player	player;
	t_ray		ray;
	t_img		img;
	t_map		map;
	t_texture	texture;
	t_screen	screen;
}				t_vars;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		is_wall(double x, double y, t_vars *vars);
void	parser(char *path, t_vars *vars);
void	parse_map(t_vars *vars, t_list **list);
void	setup(t_vars *vars, char *path);
void	draw_minimap(t_vars *vars);
void	ft_rect(int x, int y, int width, int height, int color, t_img *img);
void	cast_rays(t_vars *vars);
void	render_walls(t_vars *vars);
void	import_texture(char *path, t_img *texture, void *mlx);
void	render_walls(t_vars *vars);
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

#endif
