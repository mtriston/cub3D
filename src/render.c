#include "../cub3D.h"

static void render_sprite(t_vars *vars)
{
	double sprite_dir;
	double sprite_dist;
	double sprite_size;
	double angle_between;
	double x_offset;
	double y_offset;

	sprite_dir = atan2(vars->sprite.y - vars->player.y, vars->sprite.x - vars->player.x);
	sprite_dist = sqrt(pow(vars->sprite.x - vars->player.x, 2) +
					   pow(vars->sprite.y - vars->player.y, 2));

	sprite_size = (vars->map.tile_size / sprite_dist) * (vars->screen.width / 2) / tan(FOV_ANGLE / 2);
	while (sprite_dir - vars->player.rotation_angle > M_PI)
		sprite_dir -= 2.0 * M_PI;
	while (sprite_dir - vars->player.rotation_angle < -M_PI)
		sprite_dir += 2.0 * M_PI;

	angle_between = sprite_dir - vars->player.rotation_angle;
	if (angle_between < FOV_ANGLE / 2 && angle_between > -FOV_ANGLE / 2)
	{
		x_offset = vars->screen.width / (FOV_ANGLE * (180 / M_PI)) * ((180 / M_PI * angle_between) + 30) - sprite_size / 2;
		y_offset = vars->screen.height / 2 - sprite_size / 2;
		double step = 1.0 * vars->sprite.img.height / sprite_size;
		for (int i = 0; i < sprite_size; i++)
		{	
			if (vars->ray[i + (int)x_offset].distance < sprite_dist)
				continue;
			int tex_x = i / sprite_size * vars->sprite.img.width;
			double tex_pos = 0;
			if (x_offset + i > vars->screen.width || x_offset + i < 0)
				continue;
			for (int j = 0; j < sprite_size; j++)
			{	
				if (y_offset + j > vars->screen.height || y_offset + i < 0)
				continue;
				int tex_y = (int)tex_pos & (vars->sprite.img.height - 1);
				char *color = vars->sprite.img.addr + (tex_y * vars->sprite.img.line_length + tex_x * (vars->sprite.img.bits_per_pixel / 8));
				tex_pos += step;
				if (*(unsigned int *)color == 0x00000000)
					continue;
				my_mlx_pixel_put(&vars->img, x_offset + i, y_offset + j, *(unsigned int *)color);
			}
		}
	}
}

static t_img detect_side(t_vars *vars, t_ray ray)
{
	if (ray->is_vertical_hit)
	{
		if (ray->is_right)
			return (vars->texture.east);
		else
			return (vars->texture.west);
	}
	else
	{
		if (ray->is_up)
			return (vars->texture.south);
		else
			return (vars->texture.north);
	}
}

void render_walls(t_vars *vars)
{
	int i;
	double ray_distance;
	double plane;
	double wall_height;
	double wall_top;
	double step;
	double tex_pos;
	int texX;
	t_img texture;

	i = 0;
	plane = (vars->screen.width / 2) / tan(FOV_ANGLE / 2);
	while (i < vars->screen.width)
	{
		texture = detect_side(vars, &vars->ray[i]);
		if (vars->ray[i].distance == 0)
			vars->ray[i].distance = 1;
		ray_distance = vars->ray[i].distance * cos(vars->ray[i].ray_angle - vars->player.rotation_angle);
		wall_height = (vars->map.tile_size / ray_distance) * plane;
		wall_top = vars->screen.height / 2 - wall_height / 2;

		if (vars->ray[i].is_vertical_hit)
			texX = (int)vars->ray[i].hit_y % (int)vars->map.tile_size / vars->map.tile_size * texture.width;
		else
			texX = (int)vars->ray[i].hit_x % (int)vars->map.tile_size / vars->map.tile_size * texture.width;

		step = 1.0 * texture.height / wall_height;
		tex_pos = (wall_top - vars->screen.height / 2 + wall_height / 2) * step;
		for (int y = wall_top; y < wall_top + wall_height; y++)
		{
			int texY = (int)tex_pos & (texture.height - 1);
			char *color = texture.addr + (texY * texture.line_length + texX * (texture.bits_per_pixel / 8));
			tex_pos += step;
			if (y >= 0 && y <= vars->screen.height && i >= 0 && i <= vars->screen.width)
				my_mlx_pixel_put(&vars->img, i, y, *(unsigned int *)color);
		}
		i++;
	}
	render_sprite(vars);
}