/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 18:48:03 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/25 23:50:04 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_wall(double x, double y, t_cub *cub)
{
	int m_x;
	int m_y;

	if (x < 0 || x > cub->frame.w || y < 0 || y > cub->frame.h)
		return (OUT_OF_MAP);
	m_x = (int)((x / cub->map.tile));
	m_y = (int)((y / cub->map.tile));
	if (m_x < 0 || m_x >= cub->map.x || m_y < 0 || m_y >= cub->map.y)
		return (OUT_OF_MAP);
	if (cub->map.map[m_y][m_x] == '2')
		return (SPRITE);
	return (cub->map.map[m_y][m_x] == '1');
}

void	player_location(t_cub *cub)
{
	double next_x;
	double next_y;
	double move_step;
	double sideways;

	sideways = cub->cam.sideways ? M_PI / 2 * cub->cam.walk_dir : 0;
	move_step = cub->cam.walk_dir * cub->cam.walk_speed;
	move_step = cub->cam.sideways && move_step < 0 ? -move_step : move_step;
	cub->cam.angle += cub->cam.turn_dir * cub->cam.turn_speed;
	next_x = cub->cam.x + cos(cub->cam.angle - sideways) * move_step * 2;
	next_y = cub->cam.y + sin(cub->cam.angle - sideways) * move_step * 2;
	if (!is_wall(next_x, next_y, cub))
	{
		cub->cam.x = cub->cam.x + cos(cub->cam.angle - sideways) * move_step;
		cub->cam.y = cub->cam.y + sin(cub->cam.angle - sideways) * move_step;
	}
	cub->cam.turn_dir = 0;
	cub->cam.walk_dir = 0;
	cub->cam.sideways = 0;
}

int		key_pressed(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		ft_close(cub);
	if (keycode == LEFT_ARROW)
		cub->cam.turn_dir = -1;
	else if (keycode == RIGHT_ARROW)
		cub->cam.turn_dir = 1;
	else if (keycode == W_KEY)
		cub->cam.walk_dir = 1;
	else if (keycode == S_KEY)
		cub->cam.walk_dir = -1;
	else if (keycode == D_KEY)
	{
		cub->cam.walk_dir = -1;
		cub->cam.sideways = TRUE;
	}
	else if (keycode == A_KEY)
	{
		cub->cam.walk_dir = 1;
		cub->cam.sideways = TRUE;
	}
	render_next_frame(cub);
	mlx_put_image_to_window(cub->frame.mlx, cub->frame.win, cub->img.img, 0, 0);
	return (1);
}

int		key_released(int keycode, t_cub *cub)
{
	if (keycode == LEFT_ARROW)
		cub->cam.turn_dir = 0;
	else if (keycode == RIGHT_ARROW)
		cub->cam.turn_dir = 0;
	else if (keycode == W_KEY)
		cub->cam.walk_dir = 0;
	else if (keycode == S_KEY)
		cub->cam.walk_dir = 0;
	else if (keycode == D_KEY)
	{
		cub->cam.walk_dir = 0;
		cub->cam.sideways = FALSE;
	}
	else if (keycode == A_KEY)
	{
		cub->cam.walk_dir = 0;
		cub->cam.sideways = FALSE;
	}
	render_next_frame(cub);
	mlx_put_image_to_window(cub->frame.mlx, cub->frame.win, cub->img.img, 0, 0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_cub	cub;
	int		bmp;

	bmp = validate_args(argc, argv, &cub);
	setup(&cub, argv[1], bmp);
	mlx_hook(cub.frame.win, 17, 1Lu << 17u, ft_close, &cub);
	mlx_hook(cub.frame.win, 2, 1Lu << 0u, key_pressed, &cub);
	mlx_hook(cub.frame.win, 3, 1Lu << 1u, key_released, &cub);
	mlx_loop(cub.frame.mlx);
	return (0);
}
