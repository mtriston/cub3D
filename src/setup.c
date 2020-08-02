#include "../cub3D.h"

static void	prepare_structs(t_vars *vars)
{
	vars->player.x = 0;
	vars->player.y = 0;
	vars->player.turn_direction = 0;
	vars->player.walk_direction = 0;
	vars->player.rotation_angle = -1;
	vars->player.walk_speed = 5;
	vars->player.turn_speed = 10 * (M_PI / 180);
	vars->screen.width = 0;
	vars->screen.height = 0;
	vars->map.map = NULL;
	vars->map.floor_color = 0;
	vars->map.ceil_color = 0;
	vars->texture.north = NULL;
	vars->texture.south = NULL;
	vars->texture.west = NULL;
	vars->texture.east = NULL;
	vars->sprite.path = NULL;
}

static void	init_img(t_img *img, t_screen *screen)
{
	screen->win = \
			mlx_new_window(screen->mlx, screen->width, screen->height, "cub3D");
	img->img = mlx_new_image(screen->mlx, screen->width, screen->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
									&img->line_length, &img->endian);
}
void		setup(t_vars *vars, char *path)
{
	vars->screen.mlx = mlx_init();
	prepare_structs(vars);
	parser(path, vars);
	init_img(&vars->img, &vars->screen);
}
