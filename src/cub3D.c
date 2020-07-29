#include "../cub3D.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_rect(int x, int y, int width, int height, int color, t_vars *vars)
{
	int i;
	int j;

	i = x;
	while (i <= x + width)
	{
		j = y;
		while (j <= y + height)
		{
			if (j == y || j == height || i == x || i == width)
				my_mlx_pixel_put(vars, i, j, 0x33333333);
			else
				my_mlx_pixel_put(vars, i, j, color);
			j++;
		}
		i++;
	}
}

void	init_player(t_vars *vars)
{
	vars->x = WINDOW_WIDTH / 2;
	vars->y = WINDOW_HEIGHT / 2;
	vars->turn_direction = 0.0;
	vars->walk_direction = 0.0;
	vars->rotation_angle = M_PI / 2;
}

void	clear(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
	j = 0;
		while (j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(vars, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}

int		is_wall(int x, int y, t_vars *vars)
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (1);
	return (vars->map[y / TILE_SIZE][x / TILE_SIZE]);
}

void	player_location(t_vars *vars)
{
	float next_x;
	float next_y;
	float move_step;
	move_step = vars->walk_direction * MOVE_SPEED;
	vars->rotation_angle += vars->turn_direction * ROTATION_SPEED;
	next_x = vars->x + cos(vars->rotation_angle) * move_step;
	next_y = vars->y + sin(vars->rotation_angle) * move_step;
	if (!is_wall((int)next_x, (int)next_y, vars))
	{
		vars->x = next_x;
		vars->y = next_y;
	}
	printf("x = %f, y = %f, rotation_angle = %f, turn_dir = %f, walk_dir = %f\n",\
	vars->x, vars->y, vars->rotation_angle, vars->turn_direction, vars->walk_direction);
	vars->turn_direction = 0;
	vars->walk_direction = 0;
}

int		render_next_frame(t_vars *vars)
{ 
	//draw_minimap(vars);
	player_location(vars);
	my_mlx_pixel_put(vars, (int)vars->x, (int)vars->y, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (1);
}


int		key_pressed(int keycode, t_vars *vars)
{

	if (keycode == LEFT_ARROW)
		vars->turn_direction = -1;
	else if (keycode == UP_ARROW)
		vars->walk_direction = 1; 
	else if (keycode == RIGHT_ARROW)
		vars->turn_direction = 1;
	else if (keycode == DOWN_ARROW)
		vars->walk_direction = -1; 
	return (1);
}

int		key_released(int keycode, t_vars *vars)
{

	if (keycode == LEFT_ARROW)
		vars->turn_direction = 0;
	else if (keycode == UP_ARROW)
		vars->walk_direction = 0; 
	else if (keycode == RIGHT_ARROW)
		vars->turn_direction = 0;
	else if (keycode == DOWN_ARROW)
		vars->walk_direction = 0; 
	return (1);
}

int		main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	init_player(&vars);
	vars.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	vars.map = parse_map("./map.cub");
	mlx_hook(vars.win, 2, 1L<<0, key_pressed, &vars);
	mlx_hook(vars.win, 3, 1L<<1, key_released, &vars);
	mlx_key_hook(vars.win, key_pressed, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
