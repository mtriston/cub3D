#include "../cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_rect(int x, int y, int width, int height, int color, t_img *img)
{
	int i;
	int j;

	i = x;
	while (i <= x + width)
	{
		j = y;
		while (j <= y + height)
		{
				my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

int		is_wall(double x, double y, t_vars *vars)
{
	int map_x;
	int map_y;
	int i;
	int j;

	if (x < 0 || x > vars->screen.width || y < 0 || y > vars->screen.height)
		return (2);
	i = 0;
	j = 0;
	map_x = (int)((x / vars->map.tile_size));
	map_y = (int)((y / vars->map.tile_size));
	while (vars->map.map[i] != NULL)
	{
		if (i == map_y)
			break;
		i++;
	}
	if (vars->map.map[i] == NULL)
		return (2);
	while (vars->map.map[i][j] != '\0')
	{
		if (j == map_x)
			break;
		j++;
	}
	if (vars->map.map[i][j] == '\0')
		return (2);
	if (i != map_y || j != map_x || vars->map.map[i][j] == ' ' || vars->map.map[i][j] == '2')
		return (2);
	
	return (vars->map.map[map_y][map_x] == '1');
}

void	player_location(t_vars *vars)
{
	double next_x;
	double next_y;
	double move_step;
	double sideways;

	sideways = vars->player.sideways ? M_PI / 2 * vars->player.walk_direction : 0;
	move_step = vars->player.walk_direction * vars->player.walk_speed;
	move_step = vars->player.sideways && move_step < 0 ? -move_step : move_step;
	vars->player.rotation_angle += vars->player.turn_direction * vars->player.turn_speed;
	next_x = vars->player.x + cos(vars->player.rotation_angle - sideways) * move_step * 2;
	next_y = vars->player.y + sin(vars->player.rotation_angle - sideways) * move_step * 2;
	if (!is_wall(next_x, next_y, vars))
	{
		vars->player.x = vars->player.x + cos(vars->player.rotation_angle - sideways) * move_step;
		vars->player.y = vars->player.y + sin(vars->player.rotation_angle - sideways) * move_step;
	}
	vars->player.turn_direction = 0;
	vars->player.walk_direction = 0;
	vars->player.sideways = 0;
}

int		render_next_frame(t_vars *vars)
{
	mlx_do_sync(vars->screen.mlx);
	ft_rect(0, 0, vars->screen.width, vars->screen.height / 2, \
											vars->map.ceil_color, &vars->img);
	ft_rect(0, vars->screen.height / 2, vars->screen.width, \
				vars->screen.height / 2, vars->map.floor_color, &vars->img);
	player_location(vars);
	cast_rays(vars);
	render_walls(vars);
	sprite(vars);
	draw_minimap(vars);
	ft_rect((int)(vars->player.x * MINIMAP_SCALE),	(int)(vars->player.y * MINIMAP_SCALE), (int)(vars->map.tile_size / 2 * MINIMAP_SCALE), (int)(vars->map.tile_size / 2 * MINIMAP_SCALE), 0x00FF0000, &vars->img);
	mlx_put_image_to_window(vars->screen.mlx, vars->screen.win, vars->img.img, 0, 0);
	return (1);
}


int		key_pressed(int keycode, t_vars *vars)
{
	if (keycode == LEFT_ARROW)
		vars->player.turn_direction = -1;
	else if (keycode == RIGHT_ARROW)
		vars->player.turn_direction = 1;
	else if (keycode == W_KEY)
		vars->player.walk_direction = 1;
	else if (keycode == S_KEY)
		vars->player.walk_direction = -1;
	else if (keycode == D_KEY)
	{
		vars->player.walk_direction = -1;
		vars->player.sideways = TRUE;
	}
	else if (keycode == A_KEY)
	{
		vars->player.walk_direction = 1;
		vars->player.sideways = TRUE;
	}
	render_next_frame(vars);
	return (1);
}

int		key_released(int keycode, t_vars *vars)
{

	if (keycode == LEFT_ARROW)
		vars->player.turn_direction = 0;
	else if (keycode == RIGHT_ARROW)
		vars->player.turn_direction = 0;
	else if (keycode == W_KEY)
		vars->player.walk_direction = 0;
	else if (keycode == S_KEY)
		vars->player.walk_direction = 0;
	else if (keycode == D_KEY)
	{
		vars->player.walk_direction = 0;
		vars->player.sideways = FALSE;
	}
	else if (keycode == A_KEY)
	{
		vars->player.walk_direction = 0;
		vars->player.sideways = FALSE;
	}
	render_next_frame(vars);
	return (1);
}

int		main(int argc, char **argv)
{
	t_vars	vars;
	if (argc == 1)
		ft_error("Missing *.cub file");
	setup(&vars, argv[1]);
	render_next_frame(&vars);
	mlx_hook(vars.screen.win, 2, 1L<<0, key_pressed, &vars);
	mlx_hook(vars.screen.win, 3, 1L<<1, key_released, &vars);
	mlx_loop(vars.screen.mlx);
	return (0);
}
