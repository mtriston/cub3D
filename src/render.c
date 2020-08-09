#include "../cub3D.h"

void			render_walls(t_vars *vars)
{
	int i;
	double ray_distance;
	double plane;
	double wall_height;
	double wall_top;

	i = 0;
	plane = (vars->screen.width / 2) / tan(FOV_ANGLE / 2);
	while (i < vars->screen.width - 1)
	{
		if (vars->ray[i].distance == 0)
			vars->ray[i].distance = 1;
		ray_distance = vars->ray[i].distance * cos(vars->ray[i].ray_angle - vars->player.rotation_angle);
		wall_height = (vars->map.tile_size / ray_distance) * plane;
		wall_top = vars->screen.height / 2 - wall_height / 2;
		wall_top = wall_top < 0 ? 0 : wall_top;
		wall_height = wall_height + wall_top > (vars->screen.height) ? vars->screen.height : wall_height;
		if (vars->ray[i].is_vertical_hit)
			ft_rect(i, wall_top, 1, wall_height, 0x00AA0408, &vars->img);
		else
			ft_rect(i, wall_top, 1, wall_height, 0x0000AA59, &vars->img);
		i++;
	}
}