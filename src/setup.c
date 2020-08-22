/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 22:18:48 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/22 22:19:23 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	prepare_structs(t_cub *cub)
{
	cub->frame.win = NULL;
	cub->frame.mlx = NULL;
	cub->texture.east.img = NULL;
	cub->texture.west.img = NULL;
	cub->texture.north.img = NULL;
	cub->texture.south.img = NULL;
	cub->texture.sprite.img = NULL;
	cub->img.img = NULL;
	cub->cam.x = 0;
	cub->cam.y = 0;
	cub->cam.turn_dir = 0;
	cub->cam.walk_dir = 0;
	cub->cam.sideways = FALSE;
	cub->cam.angle = -1;
	cub->cam.walk_speed = 5;
	cub->cam.turn_speed = 5 * (M_PI / 180);
	cub->frame.w = 0;
	cub->frame.h = 0;
	cub->map.map = NULL;
	cub->map.f_clr = 0;
	cub->map.c_clr = 0;
	cub->map.items = 0;
}

static void	init_img(t_img *img, t_frame *screen, t_cub *cub)
{
	img->img = mlx_new_image(screen->mlx, screen->w, screen->h);
	if (img->img == NULL)
		ft_exit("mlx_new_image failed", cub);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, \
									&img->line_len, &img->endian);
	if (img->addr == NULL)
		ft_exit("mlx_get_data_addr failed", cub);
}

void		setup(t_cub *cub, char *path, int bmp)
{
	prepare_structs(cub);
	cub->frame.mlx = mlx_init();
	if (cub->frame.mlx == NULL)
		ft_exit("MLH initialization failed", cub);
	parser(path, cub);
	if (!(cub->ray = malloc_gc(sizeof(t_ray) * cub->frame.w)))
		ft_exit("Memory allocation for array of rays failed.", cub);
	init_img(&cub->img, &cub->frame, cub);
	render_next_frame(cub);
	if (bmp == TRUE)
		bitmap(cub);
	cub->frame.win = \
			mlx_new_window(cub->frame.mlx, cub->frame.w, cub->frame.h, "cub3D");
	if (cub->frame.win == NULL)
		ft_exit("mlx_new_window failed", cub);
	mlx_put_image_to_window(cub->frame.mlx, cub->frame.win, cub->img.img, 0, 0);
}
