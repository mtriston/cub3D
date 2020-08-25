/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:45:28 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/25 23:45:28 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	import_texture(char *path, t_img *texture, t_cub *cub)
{
	texture->img = mlx_xpm_file_to_image(cub->frame.mlx, \
						path, &texture->width, &texture->height);
	if (texture->img == NULL)
		ft_exit("Invalid tex file", cub);
	texture->addr = mlx_get_data_addr(texture->img, \
					&texture->bpp, &texture->len, &texture->endian);
	if (texture->addr == NULL)
		ft_exit("Invalid tex file", cub);
}
