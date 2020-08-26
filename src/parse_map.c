/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 22:54:41 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/25 23:06:44 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	setup_player(char side, int x, int y, t_cub *cub)
{
	if (cub->cam.angle != -1 || cub->cam.x != 0 || \
												cub->cam.y != 0)
		ft_exit("More than one player on the map", cub);
	cub->cam.x = x;
	cub->cam.y = y;
	if (side == 'N')
		cub->cam.angle = M_PI / 2;
	else if (side == 'S')
		cub->cam.angle = 3 * M_PI / 2;
	else if (side == 'W')
		cub->cam.angle = M_PI;
	else if (side == 'E')
		cub->cam.angle = 0;
}

static void	setup_sprites(t_cub *cub)
{
	int i;
	int x;
	int y;

	y = 0;
	i = 0;
	cub->item = malloc_gc(sizeof(t_item) * (cub->map.items));
	if (cub->item == NULL)
		ft_exit("Memory allocation for items failed", cub);
	while (cub->map.map[y])
	{
		x = 0;
		while (cub->map.map[y][x])
		{
			if (cub->map.map[y][x] == '2')
			{
				cub->item[i].x = (x + 0.5) * cub->map.tile;
				cub->item[i].y = (y + 0.5) * cub->map.tile;
				i++;
			}
			x++;
		}
		y++;
	}
}

static void	parse_line(char *str, int y, t_cub *cub)
{
	int x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == 'N' || str[x] == 'S' || str[x] == 'W' || str[x] == 'E')
			setup_player(str[x], x, y, cub);
		else if (str[x] == '2')
			cub->map.items++;
		else if (str[x] != '0' && str[x] != '1' && str[x] != ' ')
			ft_exit("Invalid map: Forbidden symbols", cub);
		x++;
	}
}

static void	align_map(t_cub *cub, int max)
{
	int		i;
	char	*temp;

	i = 0;
	while (cub->map.map[i] != NULL)
	{
		temp = cub->map.map[i];
		cub->map.map[i] = malloc_gc(sizeof(char) * max + 1);
		ft_memset(cub->map.map[i], ' ', max);
		cub->map.map[i][max] = '\0';
		ft_memcpy(cub->map.map[i], temp, ft_strlen(temp));
		free_gc(temp);
		i++;
	}
	cub->map.x = max;
	cub->map.y = i;
}

void		parse_map(t_cub *cub, t_list *ptr)
{
	size_t	i;
	size_t	max;

	i = 0;
	max = 0;
	while (ptr && ft_atoi(ptr->content) == 0)
		ptr = ptr->next;
	if (!(cub->map.map = malloc_gc(sizeof(char *) * (ft_lstsize(ptr) + 1))))
		ft_exit("Memory allocated for map failed", cub);
	while (ptr)
	{
		parse_line(ptr->content, i, cub);
		cub->map.map[i++] = ptr->content;
		max = max < ft_strlen(ptr->content) ? ft_strlen(ptr->content) : max;
		ptr = ptr->next;
	}
	cub->map.map[i] = NULL;
	align_map(cub, max);
	validate_map(cub, cub->map.map);
	max = max < i ? i : max;
	cub->map.tile = cub->frame.h > cub->frame.w ? \
									cub->frame.h / max : cub->frame.w / max;
	cub->cam.x *= cub->map.tile;
	cub->cam.y *= cub->map.tile;
	setup_sprites(cub);
}
