#include "../cub3D.h"

void	import_texture(char *path, t_img *texture, t_vars *vars)
{
	texture->img = mlx_xpm_file_to_image(vars->screen.mlx, path, &texture->width, &texture->height);
	if (texture->img == NULL)
		ft_exit("Invalid texture file", vars);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (texture->addr == NULL)
		ft_exit("Invalid texture file", vars);
}