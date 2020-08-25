/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 21:43:03 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/25 23:42:39 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char *dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_rect(int x, int y, t_cub *cub)
{
	int i;
	int j;
	int width;
	int height;
	int color;

	i = x;
	width = cub->frame.w;
	height = cub->frame.h / 2;
	color = y == 0 ? cub->map.c_clr : cub->map.f_clr;
	while (i <= x + width)
	{
		j = y;
		while (j <= y + height)
		{
			my_mlx_pixel_put(&cub->img, i, j, color);
			j++;
		}
		i++;
	}
}
