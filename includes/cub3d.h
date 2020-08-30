/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:36:14 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/30 16:20:08 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>

# define FALSE 0
# define TRUE 1
# define SPRITE 2
# define OUT_OF_MAP 3

# define MINIMAP_SCALE 0.3f
# define FOV 60 * (M_PI / 180)

# define ESC			65307
# define LEFT_ARROW		65361
# define RIGHT_ARROW	65363
# define W_KEY			119
# define D_KEY			100
# define S_KEY			115
# define A_KEY			97

typedef struct		s_cam
{
	double			x;
	double			y;
	int				turn_dir;
	int				walk_dir;
	int				sideways;
	double			angle;
	double			walk_speed;
	double			turn_speed;
}					t_cam;

typedef struct		s_ray
{
	double			angle;
	double			dist;
	double			hit_x;
	double			hit_y;
	int				is_up;
	int				is_down;
	int				is_left;
	int				is_right;
	int				is_vert_hit;
}					t_ray;

typedef struct		s_ray_utils
{
	double			x;
	double			y;
	double			x_step;
	double			y_step;
	double			hit_x;
	double			hit_y;
	double			dist;
}					t_ray_utils;

typedef struct		s_render_utils
{
	double			dist;
	double			plane;
	double			height;
	double			top;
	double			step;
	double			tex_pos;
	unsigned int	t_x;
	unsigned int	t_y;
	int				y;
	char			*color;
}					t_render_utils;

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				len;
	int				endian;
}					t_img;

typedef struct		s_map
{
	char			**map;
	double			tile;
	int				f_clr;
	int				c_clr;
	int				items;
	int				x;
	int				y;
}					t_map;

typedef struct		s_item
{
	double			x;
	double			y;
	double			angle;
	double			dist;
	double			size;
	double			x_ff;
	double			y_ff;
	double			step;
	double			tex_pos;
	unsigned int	*clr;
}					t_item;

typedef struct		s_tex
{
	t_img			north;
	t_img			south;
	t_img			west;
	t_img			east;
	t_img			item;
}					t_tex;

typedef struct		s_frame
{
	void			*mlx;
	void			*win;
	int				w;
	int				h;

}					t_frame;

typedef struct		s_cub
{
	t_cam			cam;
	t_ray			*ray;
	t_img			img;
	t_map			map;
	t_tex			tex;
	t_item			*item;
	t_frame			frame;
}					t_cub;

int					ft_close(t_cub *cub);
void				ft_exit(char *message, t_cub *cub);
int					validate_args(int argc, char **argv, t_cub *cub);
void				validate_line(char *line, t_cub *cub);
void				validate_parameters(t_cub *cub);
void				validate_map(t_cub *cub, char **map);
void				validate_color(char *line, char type, t_cub *cub);
void				my_mlx_pixel_put(t_img *img, int x, int y,\
												unsigned int color);
void				bitmap(t_cub *cub);
int					render_next_frame(t_cub *cub);
void				player_location(t_cub *cub);
int					is_wall(double x, double y, t_cub *cub);
void				parser(char *path, t_cub *cub);
void				parse_map(t_cub *cub, t_list *list);
void				setup(t_cub *cub, char *path, int bmp);
void				ft_rect(int x, int y, t_cub *cub);
void				cast_rays(t_cub *cub);
void				import_texture(char *path, t_img *texture, t_cub *cub);
int					create_trgb(int t, int r, int g, int b);
void				render_sprite(t_cub *cub);

#endif
