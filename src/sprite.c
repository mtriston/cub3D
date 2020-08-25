/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 20:15:16 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/23 21:08:22 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	calc_sprite_parameters(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map.items)
	{
		cub->item[i].angle = atan2(cub->item[i].y - cub->cam.y, \
										cub->item[i].x - cub->cam.x);
		while (cub->item[i].angle - cub->cam.angle > M_PI)
			cub->item[i].angle -= 2.0 * M_PI;
		while (cub->item[i].angle - cub->cam.angle < -M_PI)
			cub->item[i].angle += 2.0 * M_PI;
		cub->item[i].angle -= cub->cam.angle;
		cub->item[i].dist = sqrt(pow(cub->item[i].x - cub->cam.x, 2) + \
										pow(cub->item[i].y - cub->cam.y, 2));
		cub->item[i].size = (cub->map.tile / cub->item[i].dist) * \
										(cub->frame.w / 2) / tan(FOV / 2);
		cub->item[i].x_ff = cub->frame.w / (FOV * (180 / M_PI)) * \
			((180 / M_PI * cub->item[i].angle) + 30) - cub->item[i].size / 2;
		cub->item[i].y_ff = cub->frame.h / 2 - cub->item[i].size / 2;
		cub->item[i].step = cub->tex.item.height / cub->item[i].size;
		cub->item[i].tex_pos = 0;
		i++;
	}
}

static void	sort_sprite(t_cub *cub)
{
	int		i;
	int		j;
	t_item	temp;

	i = 0;
	while (i < cub->map.items)
	{
		j = 0;
		while (j < cub->map.items - 1)
		{
			if (cub->item[j].dist < cub->item[j + 1].dist)
			{
				temp = cub->item[j];
				cub->item[j] = cub->item[j + 1];
				cub->item[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	draw_sprite(t_cub *cub, t_item n)
{
	int				i;
	int				j;
	int				tex_x;
	int				tex_y;

	i = -1;
	while (++i < n.size)
	{
		if (n.x_ff + i > cub->frame.w || n.x_ff + i < 0 || \
							cub->ray[i + (int)n.x_ff].dist < n.dist)
			continue;
		tex_x = i / n.size * cub->tex.item.width;
		n.tex_pos = 0;
		j = -1;
		while (++j < n.size)
		{
			tex_y = (unsigned int)n.tex_pos & (cub->tex.item.height - 1);
			n.clr = (unsigned int *)(cub->tex.item.addr + \
				(tex_y * cub->tex.item.len + tex_x * (cub->tex.item.bpp / 8)));
			n.tex_pos += n.step;
			if (n.y_ff + j > cub->frame.h || n.y_ff + i < 0 || *n.clr == 0x0)
				continue;
			my_mlx_pixel_put(&cub->img, n.x_ff + i, n.y_ff + j, *n.clr);
		}
	}
}

void		render_sprite(t_cub *cub)
{
	int	i;

	i = 0;
	calc_sprite_parameters(cub);
	sort_sprite(cub);
	while (i < cub->map.items)
	{
		draw_sprite(cub, cub->item[i]);
		i++;
	}
}
