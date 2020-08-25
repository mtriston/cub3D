/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 22:08:27 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/22 22:17:47 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/bitmap.h"

t_bmp_file_header	file_header(t_cub *cub)
{
	t_bmp_file_header bfh;

	bfh.type = 0x4D42;
	bfh.size = sizeof(t_bmp_file_header) + sizeof(t_bmp_info_header) + \
				cub->frame.w * cub->frame.h * 4;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.off_bits = sizeof(t_bmp_file_header) + sizeof(t_bmp_info_header);
	return (bfh);
}

t_bmp_info_header	info_header(t_cub *cub)
{
	t_bmp_info_header bih;

	bih.size = 40;
	bih.width = cub->frame.w;
	bih.height = (cub->frame.h - 1) * (-1);
	bih.planes = 1;
	bih.bit_count = cub->img.bpp;
	bih.compression = 0;
	bih.size_image = 0;
	bih.x_pels_per_meter = 0;
	bih.y_pels_per_meter = 0;
	bih.clr_used = 0;
	bih.clr_important = 0;
	return (bih);
}

void				bitmap(t_cub *cub)
{
	int					fd;
	t_bmp_file_header	bfh;
	t_bmp_info_header	bih;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	bfh = file_header(cub);
	bih = info_header(cub);
	if (!write(fd, &bfh, sizeof(bfh)))
		ft_exit("file header error", cub);
	if (!write(fd, &bih, sizeof(bih)))
		ft_exit("info header error", cub);
	if (!write(fd, cub->img.addr, \
								cub->frame.w * cub->frame.h * 4))
		ft_exit("bitmap data error", cub);
	close(fd);
	ft_exit("Screenshot has been saved", cub);
}
