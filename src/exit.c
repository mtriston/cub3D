/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 22:13:25 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/25 22:55:29 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			ft_close(t_cub *cub)
{
	ft_exit("cub3D was closed.", cub);
	return (0);
}

static void	ft_mlx_close(t_cub *cub)
{
	if (cub->frame.mlx == NULL)
		return ;
	if (cub->frame.win)
		mlx_destroy_window(cub->frame.mlx, cub->frame.win);
	if (cub->tex.east.img)
		mlx_destroy_image(cub->frame.mlx, cub->tex.east.img);
	if (cub->tex.west.img)
		mlx_destroy_image(cub->frame.mlx, cub->tex.west.img);
	if (cub->tex.north.img)
		mlx_destroy_image(cub->frame.mlx, cub->tex.north.img);
	if (cub->tex.south.img)
		mlx_destroy_image(cub->frame.mlx, cub->tex.south.img);
	if (cub->tex.item.img)
		mlx_destroy_image(cub->frame.mlx, cub->tex.item.img);
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
		ft_putendl_fd(message, 1);
	ft_mlx_close(cub);
	free_gc(NULL);
	errno = errno == 11 ? 0 : errno;
	exit(errno);
}
