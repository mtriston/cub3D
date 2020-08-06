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
	float		x;
	float		y;
	int			turn_direction;
	int			walk_direction;
	float		rotation_angle;
	float		walk_speed;
	float		turn_speed;
}				t_player;

typedef struct	s_ray
{
	float		ray_angle;
	float		distance;
	int			is_ray_facing_up;
	int			is_ray_facing_down;
	int			is_ray_facing_left;
	int			is_ray_facing_right;
}				t_ray[1920];

typedef struct  s_ray_utils
{
	float		x_intercept;
	float		y_intercept;
	float		x_step;
	float		y_step;
	float		next_x;
	float		next_y;
	float		check_x;
	float		check_y;
	float		hit_wall_x;
	float		hit_wall_y;
	float		distance;
}				t_ray_utils;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_map
{
	char		**map;
	float		tile_size;
	int			floor_color;
	int			ceil_color;
}				t_map;

typedef struct	s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_texture;

typedef struct	s_sprite
{
	char		*path;
}				t_sprite;

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
	t_sprite	sprite;
	t_screen	screen;
}				t_vars;

int		map_has_wall_at(float x, float y, t_vars *vars);
void	parser(char *path, t_vars *vars);
void	parse_map(t_vars *vars, t_list **list);
void	setup(t_vars *vars, char *path);
void	draw_minimap(t_vars *vars);
void	ft_rect(int x, int y, int width, int height, int color, t_img *img);
void	cast_rays(t_vars *vars);
void	render_walls(t_vars *vars);
int	create_trgb(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

#endif
