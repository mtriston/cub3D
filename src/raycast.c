#include "../cub3D.h"

double			normalize_angle(double angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

static double	distance_between_points(double x1, double x2, double y1, double y2)
{
	double result;

	result = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	return (result);
}

static double	find_vertical_interception(t_vars *vars, t_ray ray)
{
	t_ray_utils vert;
	vert.x_intercept = floorf(vars->player.x / vars->map.tile_size) * vars->map.tile_size;
	vert.x_intercept += ray->is_ray_facing_right ? vars->map.tile_size : 0;
	vert.y_intercept = vars->player.y + (vert.x_intercept - vars->player.x) * tan(ray->ray_angle);
	if (vert.y_intercept < 0 || vert.y_intercept > vars->screen.height)
		return (INT_MAX);
	vert.x_step = vars->map.tile_size;
	vert.x_step *= ray->is_ray_facing_left ? -1 : 1;
	vert.y_step = vars->map.tile_size * tan(ray->ray_angle);
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

static double	find_horizontal_interception(t_vars *vars, t_ray ray)
{
	t_ray_utils horz;
	horz.y_intercept = floorf(vars->player.y / vars->map.tile_size) * vars->map.tile_size;
	horz.y_intercept += ray->is_ray_facing_down ? vars->map.tile_size : 0;
	horz.x_intercept = vars->player.x + (horz.y_intercept - vars->player.y) / tan(ray->ray_angle);
	if (horz.y_intercept < 0 || horz.y_intercept > vars->screen.width)
		return (INT_MAX);
	horz.y_step = vars->map.tile_size;
	horz.y_step *= ray->is_ray_facing_up ? -1 : 1;
	horz.x_step = vars->map.tile_size / tan(ray->ray_angle);
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
	double	ray_angle;
	double	vert_distance;
	double	horz_distance;

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
		if (vert_distance > horz_distance)
		{	
			vars->ray[i].distance = sqrt(horz_distance);
			vars->ray[i].is_vertical_hit = FALSE;
		}
		else
		{
			vars->ray[i].distance = sqrt(vert_distance);
			vars->ray[i].is_vertical_hit = TRUE;
		}
		ray_angle += FOV_ANGLE / vars->screen.width;
		i++;
	}
}
