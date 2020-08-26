/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 20:57:47 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/26 19:27:39 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	validate_line(char *line, t_cub *cub)
{
	while (ft_isblank(*line) && *line)
		line++;
	if (*line != '1' && *line != '\0')
		ft_exit("Unknown instruction in config file", cub);
}

int		validate_args(int argc, char **argv, t_cub *cub)
{
	int bmp;
	int len;

	bmp = FALSE;
	cub->frame.mlx = NULL;
	if (argc == 1)
		ft_exit("The first argument must be the configuration file.", cub);
	if (argc >= 2)
	{
		len = ft_strlen(argv[1]) - 4;
		if (len <= 0 || ft_memcmp(argv[1] + len, ".cub\0", 5) != 0)
			ft_exit("The 1st arg must be the config file '*.cub'.", cub);
	}
	if (argc == 3)
		if (ft_memcmp(argv[2], "--save\0", 7) == 0)
			bmp = TRUE;
		else
			ft_exit("The second argument can only be '--save'", cub);
	if (argc > 3)
		ft_exit("There should be no more than two arguments.", cub);
	return (bmp);
}

void	validate_parameters(t_cub *cub)
{
	if (cub->frame.w == -1 || cub->frame.h == -1)
		ft_exit("No screen resolution data", cub);
	if (cub->tex.south.img == NULL)
		ft_exit("No south texture data", cub);
	if (cub->tex.north.img == NULL)
		ft_exit("No north texture data", cub);
	if (cub->tex.west.img == NULL)
		ft_exit("No west texture data", cub);
	if (cub->tex.east.img == NULL)
		ft_exit("No east texture data", cub);
	if (cub->tex.item.img == NULL)
		ft_exit("No item's texture data", cub);
	if (cub->map.c_clr == -1)
		ft_exit("No ceil's color data", cub);
	if (cub->map.f_clr == -1)
		ft_exit("No floor's color data", cub);
}

void	validate_map(t_cub *cub, char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (j == 0 || j == cub->map.x - 1)
					ft_exit("Invalid map", cub);
				if (i == 0 || i == cub->map.y - 1)
					ft_exit("Invalid map", cub);
				if (j + 1 < cub->map.x && map[i][j + 1] == ' ')
					ft_exit("Invalid map", cub);
				if (map[i][j - 1] == ' ' || map[i - 1][j] == ' ')
					ft_exit("Invalid map", cub);
				if (i + 1 < cub->map.y && map[i + 1][j] == ' ')
					ft_exit("Invalid map", cub);
			}
		}
	}
}
