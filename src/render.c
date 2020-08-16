#include "../cub3D.h"

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
			texX = remainder(vars->ray[i].hit_y, vars->map.tile_size) / vars->map.tile_size * texture.width;
		else
			texX = remainder(vars->ray[i].hit_x, vars->map.tile_size) / vars->map.tile_size * texture.width;
		texX = texX & (texture.height - 1);
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
}