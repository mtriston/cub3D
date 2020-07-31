#ifndef CUB3D_H
# define CUB3D_H

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define TILE_SIZE 32 

#define MOVE_SPEED 4 

#define FOV_ANGLE 60 * (M_PI / 180) 
#define ROTATION_SPEED 2 * (M_PI / 180)

#define WALL_STRIP_WIDTH 1
#define NUM_RAYS WINDOW_WIDTH / WALL_STRIP_WIDTH

#define LEFT_ARROW 65361
#define UP_ARROW 65362
#define RIGHT_ARROW 65363
#define DOWN_ARROW 65364

#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	double		x;
	double		y;
	double		turn_direction;
	int			walk_direction;
	double		rotation_angle;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			**map;
}				t_vars;

int	**parse_map(char *path);
void	draw_minimap(t_vars *vars);
void	ft_rect(int x, int y, int width, int height, int color, t_vars *vars);
int	create_trgb(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

#endif
