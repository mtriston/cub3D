#include "../cub3D.h"

float			normalize_angle(float angle)
{
	while (angle > (2 * M_PI))
		angle = angle - (2 * M_PI);
	while (angle < (-2 * M_PI))
		angle = angle + (2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void			render_walls(t_vars *vars)
{
	int i;
	float ray_distance;
	float plane;
	int wall_height;
	int wall_top;

	i = 0;
	plane = vars->screen.width / 2 / tanf(FOV_ANGLE / 2);
	while (i < vars->screen.width)
	{
		if (vars->ray[i].distance == 0)
			vars->ray[i].distance = 1;
		ray_distance = vars->ray[i].distance * cosf(vars->ray[i].ray_angle - vars->player.rotation_angle);
		wall_height = (vars->map.tile_size / ray_distance) * plane;
		wall_top = vars->screen.height / 2 - wall_height / 2;
		wall_top = wall_top < 0 ? 0 : wall_top;
		wall_height = wall_height + wall_top >= (vars->screen.height) ? vars->screen.height : wall_height;
		if (vars->ray[i].is_vertical_hit)
			ft_rect(i, wall_top, 1, wall_height, 0x00AA0408, &vars->img);
		else
			ft_rect(i, wall_top, 1, wall_height, 0x0000AA59, &vars->img);
		i++;
	}
}

static float	distance_between_points(float x1, float x2, float y1, float y2)
{
	float result;

	result = sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (result);
}

static int		find_vertical_interception(t_vars *vars, t_ray ray)
{
	t_ray_utils vert;
	vert.x_intercept = floorf(vars->player.x / vars->map.tile_size) * vars->map.tile_size;
	vert.x_intercept += ray->is_ray_facing_right ? vars->map.tile_size : 0;
	vert.y_intercept = vars->player.y + (vert.x_intercept - vars->player.x) * tanf(ray->ray_angle);
	vert.y_intercept = vert.y_intercept < 0 ? vars->screen.height : vert.y_intercept;  
	vert.y_intercept = vert.y_intercept > vars->screen.height ? vars->screen.height : vert.y_intercept;  
	vert.x_step = vars->map.tile_size;
	vert.x_step *= ray->is_ray_facing_left ? -1 : 1;
	vert.y_step = vars->map.tile_size * tanf(ray->ray_angle);
	vert.y_step *= (ray->is_ray_facing_up && vert.y_step > 0) ? -1 : 1;
	vert.y_step *= (ray->is_ray_facing_down && vert.y_step < 0) ? -1 : 1;
	vert.next_x = vert.x_intercept;
	vert.next_y = vert.y_intercept;
	while (vert.next_x >= 0 && vert.next_x <= vars->screen.width \
		&& vert.next_y >= 0 && vert.next_y <= vars->screen.height)
	{
		vert.check_x = vert.next_x - (ray->is_ray_facing_left ? 1 : 0);
		vert.check_y = vert.next_y;
		if (map_has_wall_at(vert.check_x, vert.check_y, vars) == 2)
			return (INT_MAX);
		if (map_has_wall_at(vert.check_x, vert.check_y, vars))
		{
			vert.hit_wall_x = vert.next_x;
			vert.hit_wall_y = vert.next_y;
			break;
		}
		else
		{
			vert.next_x += vert.x_step;
			vert.next_y += vert.y_step;
		}
	}
	return (distance_between_points(vars->player.x, vert.hit_wall_x, \
			vars->player.y, vert.hit_wall_y));
}

static int		find_horizontal_interception(t_vars *vars, t_ray ray)
{
	t_ray_utils horz;
	horz.y_intercept = floorf(vars->player.y / vars->map.tile_size) * vars->map.tile_size;
	horz.y_intercept += ray->is_ray_facing_down ? vars->map.tile_size : 0;
	horz.x_intercept = vars->player.x + (horz.y_intercept - vars->player.y) / tanf(ray->ray_angle);
	horz.x_intercept = horz.x_intercept < 0 ? vars->screen.height : horz.x_intercept;  
	horz.x_intercept = horz.x_intercept > vars->screen.width ? vars->screen.width : horz.x_intercept;  
	horz.y_step = vars->map.tile_size;
	horz.y_step *= ray->is_ray_facing_up ? -1 : 1;
	horz.x_step = vars->map.tile_size / tanf(ray->ray_angle);
	horz.x_step *= (ray->is_ray_facing_left && horz.x_step > 0) ? -1 : 1;
	horz.x_step *= (ray->is_ray_facing_right && horz.x_step < 0) ? -1 : 1;
	horz.next_y = horz.y_intercept;
	horz.next_x = horz.x_intercept;
	while (horz.next_x >= 0 && horz.next_x <= vars->screen.width \
		&& horz.next_y >= 0 && horz.next_y <= vars->screen.height)
	{
		horz.check_x = horz.next_x;
		horz.check_y = horz.next_y - (ray->is_ray_facing_up ? 1 : 0);
		if (map_has_wall_at(horz.check_x, horz.check_y, vars) == 2)
			return (INT_MAX);
		if (map_has_wall_at(horz.check_x, horz.check_y, vars))
		{ 
			horz.hit_wall_x = horz.next_x;
			horz.hit_wall_y = horz.next_y;
			break;
		}
		else
		{
			horz.next_x += horz.x_step;
			horz.next_y += horz.y_step;
		}
	}
	return (distance_between_points(vars->player.x, horz.hit_wall_x, \
			vars->player.y, horz.hit_wall_y));
}

void			cast_rays(t_vars *vars)
{
	int		i;
	float	ray_angle;
	float	vert_distance;
	float	horz_distance;

	i = 0;
	ray_angle = vars->player.rotation_angle - FOV_ANGLE / 2;
	while (i < vars->screen.width)
	{
		ray_angle = normalize_angle(ray_angle);
		vars->ray[i].ray_angle = ray_angle;
		vars->ray[i].is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
		vars->ray[i].is_ray_facing_up = !vars->ray[i].is_ray_facing_down;
		vars->ray[i].is_ray_facing_right = ray_angle < (M_PI / 2) || ray_angle > (M_PI * 1.5); 
		vars->ray[i].is_ray_facing_left = !vars->ray[i].is_ray_facing_right;
		vert_distance = find_vertical_interception(vars, &vars->ray[i]);
		horz_distance = find_horizontal_interception(vars, &vars->ray[i]);
		vars->ray[i].distance = horz_distance < vert_distance ? horz_distance : vert_distance;
		vars->ray[i].is_vertical_hit = (horz_distance >= vert_distance); 
		ray_angle += FOV_ANGLE / vars->screen.width;
		i++;
	}
}
