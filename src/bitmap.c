/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 22:08:27 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/20 22:21:29 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    file_header(int fd, t_vars *vars)
{
	unsigned char   bfh[14];
	int             size;

	ft_bzero(bfh, 14);
	bfh[0] = 'B';
	bfh[1] = 'M';
	size = 14 + 40 + (vars->screen.width * vars->screen.height * 4);
	bfh[2] = size % 256;
	bfh[3] = size / 256 % 256;
	bfh[4] = size / 256 / 256 % 256;
	bfh[5] = size / 256 / 256 / 256;
	bfh[10] = 14 + 40;
	if (!write(fd, bfh, 14))
		ft_exit("file header error", vars);
}

void    info_header(int fd, t_vars *vars)
{
	unsigned char   bih[40];
	int32_t         size;

	ft_bzero(bih, 40);
	bih[0] = 40;
	size = vars->screen.width;
	bih[4] = size % 256;
	bih[5] = size / 256 % 256;
	bih[6] = size / 256 / 256 % 256;
	bih[7] = size / 256 / 256 / 256;
	size = vars->screen.height;
	bih[8] = size % 256;
	bih[9] = size / 256 % 256;
	bih[10] = size / 256 / 256 % 256;
	bih[11] = size / 256 / 256 / 256;
	bih[12] = 1;
	bih[14] = vars->img.bits_per_pixel;
	if (!write(fd, bih, 40))
		ft_exit("header info error", vars);
}
void bitmap(t_vars *vars) {

	int fd;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	file_header(fd, vars);
	info_header(fd, vars);
	if (!write(fd, vars->img.addr, vars->screen.width * vars->screen.height * 4))
		ft_exit("bitmap data error", vars);
	close(fd);
}