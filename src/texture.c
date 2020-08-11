#include "../cub3D.h"

void	import_texture(char *path, t_img *texture, void *mlx)
{
	//TODO: добавить обработку ошибок
	texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height);
	if (texture->img == NULL)
		exit(-1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
}