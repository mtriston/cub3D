/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 21:34:28 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/22 21:37:54 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double		normalize_angle(double angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

static double		calc_distance(double x1, double x2, double y1, double y2)
{
	double result;

	result = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (result);
}

static t_ray_utils	find_vertical_interception(t_cub *cub, t_ray *ray)
{
	t_ray_utils v;

	v.dist = INT_MAX;
	v.x = floor(cub->cam.x / cub->map.tile) * cub->map.tile;
	v.x += ray->is_right ? cub->map.tile : 0;
	v.y = cub->cam.y + (v.x - cub->cam.x) * tan(ray->angle);
	if (v.y < 0 || v.y > cub->frame.h)
		return (v);
	v.x_step = cub->map.tile;
	v.x_step *= ray->is_left ? -1 : 1;
	v.y_step = cub->map.tile * tan(ray->angle);
	v.y_step *= (ray->is_up && v.y_step > 0) ? -1 : 1;
	v.y_step *= (ray->is_down && v.y_step < 0) ? -1 : 1;
	while (v.x >= 0 && v.x <= cub->frame.w && v.y >= 0 && v.y <= cub->frame.h)
	{
		if (is_wall(v.x - (ray->is_left ? 1 : 0), v.y, cub) == TRUE)
		{
			v.dist = calc_distance(cub->cam.x, v.x, cub->cam.y, v.y);
			return (v);
		}
		v.x += v.x_step;
		v.y += v.y_step;
	}
	return (v);
}

static t_ray_utils	find_horizontal_interception(t_cub *cub, t_ray *ray)
{
	t_ray_utils h;

	h.dist = INT_MAX;
	h.y = floor(cub->cam.y / cub->map.tile) * cub->map.tile;
	h.y += ray->is_down ? cub->map.tile : 0;
	h.x = cub->cam.x + (h.y - cub->cam.y) / tan(ray->angle);
	if (h.y < 0 || h.y > cub->frame.w)
		return (h);
	h.y_step = cub->map.tile;
	h.y_step *= ray->is_up ? -1 : 1;
	h.x_step = cub->map.tile / tan(ray->angle);
	h.x_step *= (ray->is_left && h.x_step > 0) ? -1 : 1;
	h.x_step *= (ray->is_right && h.x_step < 0) ? -1 : 1;
	while (h.x >= 0 && h.x <= cub->frame.w && h.y >= 0 && h.y <= cub->frame.h)
	{
		if (is_wall(h.x, h.y - (ray->is_up ? 1 : 0), cub) == TRUE)
		{
			h.dist = calc_distance(cub->cam.x, h.x, cub->cam.y, h.y);
			return (h);
		}
		h.x += h.x_step;
		h.y += h.y_step;
	}
	return (h);
}

void				cast_rays(t_cub *cub)
{
	int			i;
	double		angle;
	t_ray_utils	h;
	t_ray_utils	v;

	i = 0;
	angle = cub->cam.angle - FOV / 2;
	while (i < cub->frame.w)
	{
		angle = normalize_angle(angle);
		cub->ray[i].angle = angle;
		cub->ray[i].is_down = angle > 0 && angle < M_PI;
		cub->ray[i].is_up = !cub->ray[i].is_down;
		cub->ray[i].is_right = angle < (M_PI / 2) || angle > (M_PI * 1.5);
		cub->ray[i].is_left = !cub->ray[i].is_right;
		v = find_vertical_interception(cub, &cub->ray[i]);
		h = find_horizontal_interception(cub, &cub->ray[i]);
		cub->ray[i].dist = v.dist > h.dist ? h.dist : v.dist;
		cub->ray[i].hit_x = v.dist > h.dist ? h.x : v.x;
		cub->ray[i].hit_y = v.dist > h.dist ? h.y : v.y;
		cub->ray[i].is_vert_hit = v.dist > h.dist ? FALSE : TRUE;
		angle += FOV / cub->frame.w;
		i++;
	}
}
