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

int		map_has_wall_at(float x, float y, t_vars *vars)
{
	int map_x;
	int map_y;

	if (x < 0 || x > vars->screen.width || y < 0 || y > vars->screen.height)
		return (TRUE);
	map_x = (int)((x / vars->map.tile_size));
	map_y = (int)((y / vars->map.tile_size));
	return (vars->map.map[map_y][map_x]) == '1';
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
	if (!map_has_wall_at(next_x, next_y, vars))
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
	ft_rect((int)(vars->player.x * MINIMAP_SCALE), \
	(int)(vars->player.y * MINIMAP_SCALE), (int)(vars->map.tile_size / 2 * MINIMAP_SCALE), (int)(vars->map.tile_size / 2 * MINIMAP_SCALE), 0x00FF0000, &vars->img);
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

int		main(int argc, char **argv)
{
	t_vars	vars;
	if (argc != 2)
		return (-1);
//TODO: invalid num of arguments
	setup(&vars, argv[1]);
	mlx_loop_hook(vars.screen.mlx, render_next_frame, &vars);
	mlx_hook(vars.screen.win, 2, 1L<<0, key_pressed, &vars);
	mlx_hook(vars.screen.win, 3, 1L<<1, key_released, &vars);
	mlx_loop(vars.screen.mlx);
	return (0);
}
