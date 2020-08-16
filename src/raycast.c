#include "../cub3D.h"

double			normalize_angle(double angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

static double	calc_distance(double x1, double x2, double y1, double y2)
{
	double result;

	result = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (result);
}

static t_ray_utils	find_vertical_interception(t_vars *vars, t_ray ray)
{
	t_ray_utils vert;

	vert.distance = INT_MAX;
	vert.x_intercept = floor(vars->player.x / vars->map.tile_size) * vars->map.tile_size;
	vert.x_intercept += ray->is_right ? vars->map.tile_size : 0;
	vert.y_intercept = vars->player.y + (vert.x_intercept - vars->player.x) * tan(ray->ray_angle);
	if (vert.y_intercept < 0 || vert.y_intercept > vars->screen.height)
		return (vert);
	vert.x_step = vars->map.tile_size;
	vert.x_step *= ray->is_left ? -1 : 1;
	vert.y_step = vars->map.tile_size * tan(ray->ray_angle);
	vert.y_step *= (ray->is_up && vert.y_step > 0) ? -1 : 1;
	vert.y_step *= (ray->is_down && vert.y_step < 0) ? -1 : 1;
	vert.next_x = vert.x_intercept;
	vert.next_y = vert.y_intercept;
	while (vert.next_x >= 0 && vert.next_x <= vars->screen.width \
		&& vert.next_y >= 0 && vert.next_y <= vars->screen.height)
	{
		if (is_wall(vert.next_x - (ray->is_left ? 1 : 0), vert.next_y, vars) == TRUE)
		{
			vert.distance = calc_distance(vars->player.x, vert.next_x, vars->player.y, vert.next_y);
			return (vert);
		}
		else
		{
			vert.next_x += vert.x_step;
			vert.next_y += vert.y_step;
		}
	}
	return (vert);
}

static t_ray_utils	find_horizontal_interception(t_vars *vars, t_ray ray)
{
	t_ray_utils horz;

	horz.distance = INT_MAX;
	horz.y_intercept = floor(vars->player.y / vars->map.tile_size) * vars->map.tile_size;
	horz.y_intercept += ray->is_down ? vars->map.tile_size : 0;
	horz.x_intercept = vars->player.x + (horz.y_intercept - vars->player.y) / tan(ray->ray_angle);
	if (horz.y_intercept < 0 || horz.y_intercept > vars->screen.width)
		return (horz);
	horz.y_step = vars->map.tile_size;
	horz.y_step *= ray->is_up ? -1 : 1;
	horz.x_step = vars->map.tile_size / tan(ray->ray_angle);
	horz.x_step *= (ray->is_left && horz.x_step > 0) ? -1 : 1;
	horz.x_step *= (ray->is_right && horz.x_step < 0) ? -1 : 1;
	horz.next_y = horz.y_intercept;
	horz.next_x = horz.x_intercept;
	while (horz.next_x >= 0 && horz.next_x <= vars->screen.width \
		&& horz.next_y >= 0 && horz.next_y <= vars->screen.height)
	{
		if (is_wall(horz.next_x, horz.next_y - (ray->is_up ? 1 : 0), vars) == TRUE)
		{ 	
			horz.distance = calc_distance(vars->player.x, horz.next_x, vars->player.y, horz.next_y);
			return (horz);
		}
		else
		{
			horz.next_x += horz.x_step;
			horz.next_y += horz.y_step;
		}
	}
	return (horz);
}

void			cast_rays(t_vars *vars)
{
	int		i;
	double	ray_angle;
	t_ray_utils horz;
	t_ray_utils vert;

	i = 0;
	ray_angle = vars->player.rotation_angle - FOV_ANGLE / 2;
	while (i < vars->screen.width)
	{
		ray_angle = normalize_angle(ray_angle);
		vars->ray[i].ray_angle = ray_angle;
		vars->ray[i].is_down = ray_angle > 0 && ray_angle < M_PI;
		vars->ray[i].is_up = !vars->ray[i].is_down;
		vars->ray[i].is_right = ray_angle < (M_PI / 2) || ray_angle > (M_PI * 1.5); 
		vars->ray[i].is_left = !vars->ray[i].is_right;
		vert = find_vertical_interception(vars, &vars->ray[i]);
		horz = find_horizontal_interception(vars, &vars->ray[i]);
		vars->ray[i].distance = vert.distance > horz.distance ? horz.distance : vert.distance;
		vars->ray[i].hit_x = vert.distance > horz.distance ? horz.next_x : vert.next_x;
		vars->ray[i].hit_y = vert.distance > horz.distance ? horz.next_y : vert.next_y;
		vars->ray[i].is_vertical_hit = vert.distance > horz.distance ? FALSE : TRUE;
		
		ray_angle += FOV_ANGLE / vars->screen.width;
		i++;
	}
}
