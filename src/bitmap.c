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
#include "../bitmap.h"

t_bmp_file_header   file_header(t_vars *vars)
{
	t_bmp_file_header bfh;

	bfh.type = 0x4D42;
	bfh.size = sizeof(t_bmp_file_header) + sizeof(t_bmp_info_header) + \
				vars->screen.width * vars->screen.height * 4;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.off_bits = sizeof(t_bmp_file_header) + sizeof(t_bmp_info_header);
	return (bfh);
}

t_bmp_info_header   info_header(t_vars *vars)
{
	t_bmp_info_header bih;
	bih.size = 40;
	bih.width = vars->screen.width;
	bih.height = vars->screen.height * (-1);
	bih.planes = 1;
	bih.bit_count = vars->img.bits_per_pixel;
	bih.compression = 0;
	bih.size_image = 0;
	bih.x_pels_per_meter = 0;
	bih.y_pels_per_meter = 0;
	bih.clr_used = 0;
	bih.clr_important = 0;
	return (bih);
}
void bitmap(t_vars *vars) {

	int fd;
	t_bmp_file_header bfh;
	t_bmp_info_header bih;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	bfh = file_header(vars);
	bih = info_header(vars);
	if (!write(fd, &bfh, sizeof(bfh)))
		ft_exit("file header error", vars);
	if (!write(fd, &bih, sizeof(bih)))
		ft_exit("info header error", vars);
	if (!write(fd, vars->img.addr, vars->screen.width * vars->screen.height * 4))
		ft_exit("bitmap data error", vars);
	close(fd);
}