/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 16:13:48 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/16 20:57:30 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void     calc_sprite_parameters(t_vars *vars)
{
	int i;

    i = 0;
    while (i < vars->map.sprites)
    {
        vars->sprite[i].angle = atan2(vars->sprite[i].y - vars->player.y, \
                                        vars->sprite[i].x - vars->player.x);
        while (vars->sprite[i].angle - vars->player.rotation_angle > M_PI)
		vars->sprite[i].angle -= 2.0 * M_PI;
	    while (vars->sprite[i].angle - vars->player.rotation_angle < -M_PI)
		vars->sprite[i].angle += 2.0 * M_PI;
        vars->sprite[i].angle -= vars->player.rotation_angle;
        vars->sprite[i].dist = sqrt(pow(vars->sprite[i].x - vars->player.x, 2)\
                                + pow(vars->sprite[i].y - vars->player.y, 2));
        vars->sprite[i].size = (vars->map.tile_size / vars->sprite[i].dist) *\
                                (vars->screen.width / 2) / tan(FOV_ANGLE / 2);
        if (vars->sprite[i].angle < FOV_ANGLE / 2 && \
                                        vars->sprite[i].angle > -FOV_ANGLE / 2)
            vars->sprite[i].hidden = TRUE;
        i++;
    }
}

static void sort_sprite(t_vars *vars)
{
    int i;
    int j;
    t_sprite temp;
    
    i = 0;
    while (i < vars->map.sprites)
    {
        j = 0;
        while (j < vars->map.sprites - 1)
        {
            if (vars->sprite[j].dist < vars->sprite[j + i].dist)
            {
                temp = vars->sprite[j];
                vars->sprite[j] = vars->sprite[j + 1];
                vars->sprite[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    
}

static void render_sprite(t_vars *vars)
{
	int		k;
	double	x_offset;
	double	y_offset;

	k = 0;
	while (k < vars->map.sprites)
	{
		x_offset = vars->screen.width / (FOV_ANGLE * (180 / M_PI)) * ((180 / M_PI * vars->sprite[k].angle) + 30) - vars->sprite[k].size / 2;
		y_offset = vars->screen.height / 2 - vars->sprite[k].size / 2;
		double step = 1.0 * vars->texture.sprite.height / vars->sprite[k].size;
		for (int i = 0; i < vars->sprite[k].size; i++)
		{	
			if (x_offset + i > vars->screen.width || x_offset + i < 0)
				continue;
			if (vars->ray[i + (int)x_offset].distance < vars->sprite[k].dist)
				continue;
			int tex_x = i / vars->sprite[k].size * vars->texture.sprite.width;
			double tex_pos = 0;
			for (int j = 0; j < vars->sprite[k].size; j++)
			{	
				if (y_offset + j > vars->screen.height || y_offset + i < 0)
				continue;
				int tex_y = (unsigned int)tex_pos & (vars->texture.sprite.height - 1);
				char *color = vars->texture.sprite.addr + (tex_y * vars->texture.sprite.line_length + tex_x * (vars->texture.sprite.bits_per_pixel / 8));
				tex_pos += step;
				if (*(unsigned int *)color == 0x00000000)
					continue;
				my_mlx_pixel_put(&vars->img, x_offset + i, y_offset + j, *(unsigned int *)color);
			}
		}
        k++;
	}
}

void        sprite(t_vars *vars)
{
    calc_sprite_parameters(vars);
    sort_sprite(vars);
    render_sprite(vars);
}