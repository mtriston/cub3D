/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 19:07:30 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/23 19:49:04 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static t_img			detect_side(t_cub *cub, t_ray ray)
{
	if (ray.is_vert_hit)
	{
		if (ray.is_right)
			return (cub->texture.east);
		else
			return (cub->texture.west);
	}
	else
	{
		if (ray.is_up)
			return (cub->texture.south);
		else
			return (cub->texture.north);
	}
}

static t_render_utils	calc_one_stripe(t_cub *cub, int i, t_img tex)
{
	t_render_utils col;

	col.plane = (cub->frame.w / 2.0) / tan(FOV / 2);
	cub->ray[i].dist = cub->ray[i].dist == 0 ? 1 : cub->ray[i].dist;
	col.dist = cub->ray[i].dist * cos(cub->ray[i].angle - cub->cam.angle);
	col.height = (cub->map.tile / col.dist) * col.plane;
	col.top = cub->frame.h / 2.0 - col.height / 2;
	if (cub->ray[i].is_vert_hit)
		col.t_x = remainder(cub->ray[i].hit_y, cub->map.tile) / \
												cub->map.tile * tex.width;
	else
		col.t_x = remainder(cub->ray[i].hit_x, cub->map.tile) / \
												cub->map.tile * tex.width;
	col.t_x = col.t_x & (unsigned int)(tex.height - 1);
	col.step = tex.height / col.height;
	col.tex_pos = (col.top - cub->frame.h / 2.0 + col.height / 2.0) * col.step;
	col.y = (int)col.top;
	return (col);
}

void					render_walls(t_cub *cub)
{
	t_img			tex;
	t_render_utils	c;
	int				i;

	i = 0;
	while (i < cub->frame.w)
	{
		tex = detect_side(cub, cub->ray[i]);
		c = calc_one_stripe(cub, i, tex);
		while (c.y < c.top + c.height)
		{
			c.t_y = (unsigned int)c.tex_pos & ((unsigned int)tex.height - 1);
			c.color = tex.addr + (c.t_y * tex.line_len + c.t_x * (tex.bpp / 8));
			c.tex_pos += c.step;
			if (c.y >= 0 && c.y <= cub->frame.h && i >= 0 && i <= cub->frame.w)
				my_mlx_pixel_put(&cub->img, i, c.y, *(unsigned int *)c.color);
			c.y++;
		}
		i++;
	}
}
