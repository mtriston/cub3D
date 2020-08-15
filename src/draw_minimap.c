#include "../cub3D.h"

void	draw_minimap(t_vars *vars)
{
	int i;
	int j;
	int color;
	int tileX;
	int tileY;

	i = 0;
	tileX = 0;
	tileY = 0;
	while (vars->map.map[i] != NULL)
	{
		j = 0;
		while (vars->map.map[i][j] != '\0')
		{
			if (vars->map.map[i][j] == '1')
				color = 0x00000000;
			else if (vars->map.map[i][j] == '2')
				color = 0x0000FF00;
			else
				color = 0xFFFFFFFF;
			if (vars->map.map[i][j] != ' ')
				ft_rect(\
				tileX * MINIMAP_SCALE, \
				tileY * MINIMAP_SCALE, \
				vars->map.tile_size * MINIMAP_SCALE, \
				vars->map.tile_size * MINIMAP_SCALE,\
				color, \
				&vars->img);
			tileX += vars->map.tile_size;
			j++;
		}
		i++;
		tileX = 0;
		tileY += vars->map.tile_size;
	}
}
