/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 22:13:25 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/22 22:14:22 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int			ft_close(t_cub *cub)
{
	ft_exit("cub3D was closed.", cub);
	return (0);
}

static void	ft_mlx_close(t_cub *cub)
{
	if (cub->frame.win)
		mlx_destroy_window(cub->frame.mlx, cub->frame.win);
	if (cub->texture.east.img)
		mlx_destroy_image(cub->frame.mlx, cub->texture.east.img);
	if (cub->texture.west.img)
		mlx_destroy_image(cub->frame.mlx, cub->texture.west.img);
	if (cub->texture.north.img)
		mlx_destroy_image(cub->frame.mlx, cub->texture.north.img);
	if (cub->texture.south.img)
		mlx_destroy_image(cub->frame.mlx, cub->texture.south.img);
	if (cub->texture.sprite.img)
		mlx_destroy_image(cub->frame.mlx, cub->texture.sprite.img);
	if (cub->img.img)
		mlx_destroy_image(cub->frame.mlx, cub->img.img);
	if (cub->frame.mlx)
		free(cub->frame.mlx);
}

void		ft_exit(char *message, t_cub *cub)
{
	if (errno != 0 && errno != 11)
		perror(message);
	else
	{
		ft_putendl_fd(message, 1);
		errno = 0;
	}
	ft_mlx_close(cub);
	free_gc(NULL);
	exit(errno);
}
