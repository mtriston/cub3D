#include "../cub3D.h"
#include <stdio.h>

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
			if (j == y || j == height || i == x || i == width)
				my_mlx_pixel_put(img, i, j, 0x33333333);
			else
				my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	setup(t_vars *vars)
{
	vars->player.x = WINDOW_WIDTH / 2;
	vars->player.y = WINDOW_HEIGHT / 2;
	vars->player.turn_direction = 0;
	vars->player.walk_direction = 0;
	vars->player.rotation_angle = M_PI / 2;
	vars->player.walk_speed = 5;
	vars->player.turn_speed = 10 * (M_PI / 180);
}

int		map_has_wall_at(float x, float y, t_map *map)
{
	int map_x;
	int map_y;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (TRUE);
	map_x = (int)(floor(x / TILE_SIZE));
	map_y = (int)(floor(y / TILE_SIZE));
	return (map->map[map_y][map_x]) != '0';
}

void	player_location(t_vars *vars)
{
	float next_x;
	float next_y;
	float move_step;
	move_step = vars->player.walk_direction * vars->player.walk_speed;
	vars->player.rotation_angle += vars->player.turn_direction * vars->player.turn_speed;
	next_x = vars->player.x + cosf(vars->player.rotation_angle) * move_step;
	next_y = vars->player.y + sinf(vars->player.rotation_angle) * move_step;
	if (!map_has_wall_at(next_x, next_y, &vars->map))
	{
		vars->player.x = next_x;
		vars->player.y = next_y;
	}
	vars->player.turn_direction = 0;
	vars->player.walk_direction = 0;
}

int		render_next_frame(t_vars *vars)
{ 
	draw_minimap(vars);
	player_location(vars);
	my_mlx_pixel_put(&vars->img, (int)vars->player.x, (int)vars->player.y, 0x00FF);
	mlx_put_image_to_window(vars->screen.mlx, vars->screen.win, vars->img.img, 0, 0);
	return (1);
}


int		key_pressed(int keycode, t_vars *vars)
{

	if (keycode == LEFT_ARROW)
		vars->player.turn_direction = -1;
	else if (keycode == UP_ARROW)
		vars->player.walk_direction = 1; 
	else if (keycode == RIGHT_ARROW)
		vars->player.turn_direction = 1;
	else if (keycode == DOWN_ARROW)
		vars->player.walk_direction = -1; 
	return (1);
}

int		key_released(int keycode, t_vars *vars)
{

	if (keycode == LEFT_ARROW)
		vars->player.turn_direction = 0;
	else if (keycode == UP_ARROW)
		vars->player.walk_direction = 0; 
	else if (keycode == RIGHT_ARROW)
		vars->player.turn_direction = 0;
	else if (keycode == DOWN_ARROW)
		vars->player.walk_direction = 0; 
	return (1);
}

int		main(void)
{
	t_vars	vars;

	vars.screen.mlx = mlx_init();
	vars.screen.win = mlx_new_window(vars.screen.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	setup(&vars);
	vars.img.img = mlx_new_image(vars.screen.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	mlx_put_image_to_window(vars.screen.mlx, vars.screen.win, vars.img.img, 0, 0);
	mlx_loop_hook(vars.screen.mlx, render_next_frame, &vars);
	vars.map.map = parse_map("./map.cub");
	mlx_hook(vars.screen.win, 2, 1L<<0, key_pressed, &vars);
	mlx_hook(vars.screen.win, 3, 1L<<1, key_released, &vars);
	mlx_loop(vars.screen.mlx);
	return (0);
}
