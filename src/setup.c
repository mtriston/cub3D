#include "../cub3D.h"

static void	prepare_structs(t_vars *vars)
{
	vars->player.x = 0;
	vars->player.y = 0;
	vars->player.turn_direction = 0;
	vars->player.walk_direction = 0;
	vars->player.rotation_angle = -1;
	vars->player.walk_speed = 5;
	vars->player.turn_speed = 5 * (M_PI / 180);
	vars->screen.width = 0;
	vars->screen.height = 0;
	vars->map.map = NULL;
	vars->map.floor_color = 0;
	vars->map.ceil_color = 0;
	vars->map.sprites = 0;
}

static void	init_img(t_img *img, t_screen *screen)
{
	screen->win = \
			mlx_new_window(screen->mlx, screen->width, screen->height, "cub3D");
	if (screen->win == NULL)
	{
		perror("mlx_new_window failed");
		exit(EXIT_FAILURE);
	}
	img->img = mlx_new_image(screen->mlx, screen->width, screen->height);
	if (img->img == NULL)
	{
		perror("mlx_new_image failed");
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
									&img->line_length, &img->endian);
	if (img->addr == NULL)
	{
		perror("mlx_get_data_addr failed");
		exit(EXIT_FAILURE);
	}
}

void		setup(t_vars *vars, char *path)
{
	vars->screen.mlx = mlx_init();
	if (vars->screen.mlx == NULL)
		ft_error("MLH initialization failed");
	prepare_structs(vars);
	parser(path, vars);
	init_img(&vars->img, &vars->screen);
}
