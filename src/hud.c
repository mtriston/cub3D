/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 22:10:58 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/22 22:11:03 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static	void	draw_player(t_cub *cub)
{
	ft_rect((int)(cub->cam.x * MINIMAP_SCALE), \
	(int)(cub->cam.y * MINIMAP_SCALE), \
	(int)(cub->map.tile / 2 * MINIMAP_SCALE), \
	(int)(cub->map.tile / 2 * MINIMAP_SCALE), \
	0x00FF0000, &cub->img);
}

void			draw_minimap(t_cub *cub)
{
	int i;
	int j;
	int tile_x;
	int tile_y;

	i = 0;
	tile_y = 0;
	while (cub->map.map[i] != NULL)
	{
		tile_x = 0;
		j = 0;
		while (cub->map.map[i][j] != '\0')
		{
			if (cub->map.map[i][j] != ' ')
				ft_rect(tile_x * MINIMAP_SCALE, tile_y * MINIMAP_SCALE, \
				cub->map.tile * MINIMAP_SCALE, cub->map.tile * MINIMAP_SCALE,\
				cub->map.map[i][j] == '1' ? 0 : 0xFFFFFFFF, &cub->img);
			tile_x += cub->map.tile;
			j++;
		}
		i++;
		tile_y += cub->map.tile;
	}
	draw_player(cub);
}
