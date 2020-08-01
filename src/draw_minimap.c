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
			else
				color = 0xFFFFFFFF;
			ft_rect(tileX, tileY, TILE_SIZE, TILE_SIZE, color, &vars->img);
			tileX += TILE_SIZE;
			j++;
		}
		i++;
		tileX = 0;
		tileY += TILE_SIZE;
	}
}
