#include "../cub3D.h"

static void draw_player(t_vars *vars)
{
	if (vars->x + 2 < WINDOW_WIDTH && (int)vars->x - 2 > 0 && \
		vars->y + 2 < WINDOW_HEIGHT && (int)vars->y - 2 > 0)
	{
		ft_rect((int)vars->x + 2, (int)vars->y + 2, 5, 5, 0x00FF0000, vars);
	}
}

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
	while (vars->map[i] != NULL)
	{
		j = 0;
		while (vars->map[i][j] != -1)
		{
			if (vars->map[i][j] == 1)
				color = 0x00000000;
			else
				color = 0xFFFFFFFF;
			ft_rect(tileX, tileY, TILE_SIZE, TILE_SIZE, color, vars);
			tileX += TILE_SIZE;
			j++;
		}
		i++;
		tileX = 0;
		tileY += TILE_SIZE;
	}
	draw_player(vars);
}
