/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 22:30:40 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/26 19:24:28 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	write_resolution(char *str, t_cub *cub)
{
	int m_w;
	int m_h;

	mlx_get_screen_size(cub->frame.mlx, &m_w, &m_h);
	if (cub->frame.w != -1 || cub->frame.h != -1)
		ft_exit("More then one resolution's configuration", cub);
	str = ft_strchr(str, 'R');
	str++;
	cub->frame.w = ft_atoi(str);
	while (*str && ft_isspace(*str))
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	cub->frame.h = ft_atoi(str);
	if (cub->frame.w <= 0 || cub->frame.h <= 0)
		ft_exit("Invalid resolution", cub);
	cub->frame.w = cub->frame.w > m_w ? m_w : cub->frame.w;
	cub->frame.h = \
						cub->frame.h > m_h ? m_h : cub->frame.h;
}

static void	write_color(char *str, t_cub *cub, char type)
{
	char	**clr;
	int		rgb[3];
	int		i;

	i = -1;
	while (*str && ft_isspace(*str))
		str++;
	str++;
	while (str[++i])
		if (!ft_isdigit(str[i]) && str[i] != ',' && !ft_isspace(str[i]))
			ft_exit("Invalid color in the config file", cub);
	if (!(clr = ft_split(str, ',')))
		ft_exit("Memory allocation error", cub);
	i = -1;
	while (clr && clr[++i] != NULL)
	{
		if ((rgb[i] = ft_atoi(clr[i])) > 255 || clr[i] < 0 || i > 2)
			ft_exit("Invalid color in the config file", cub);
		free_gc(clr[i]);
	}
	free_gc(clr);
	if (type == 'C')
		cub->map.c_clr = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	else if (type == 'F')
		cub->map.f_clr = create_trgb(0, rgb[0], rgb[1], rgb[2]);
}

static void	write_path_to_file(char *str, t_cub *cub, char type)
{
	while (*str && ft_isspace(*str))
		str++;
	str = str + 2;
	while (*str && ft_isspace(*str))
		str++;
	if (type == 'N')
		import_texture(str, &cub->tex.north, cub);
	if (type == 'S')
		import_texture(str, &cub->tex.south, cub);
	if (type == 'W')
		import_texture(str, &cub->tex.west, cub);
	if (type == 'E')
		import_texture(str, &cub->tex.east, cub);
	if (type == 's')
		import_texture(str, &cub->tex.item, cub);
}

static void	parse_parameters(t_list *list, t_cub *cub)
{
	int		len;

	while (list)
	{
		len = ft_strlen(list->content);
		if (ft_strnstr(list->content, "R ", len))
			write_resolution(list->content, cub);
		else if (ft_strnstr(list->content, "NO ", len))
			write_path_to_file(list->content, cub, 'N');
		else if (ft_strnstr(list->content, "SO ", len))
			write_path_to_file(list->content, cub, 'S');
		else if (ft_strnstr(list->content, "WE ", len))
			write_path_to_file(list->content, cub, 'W');
		else if (ft_strnstr(list->content, "EA ", len))
			write_path_to_file(list->content, cub, 'E');
		else if (ft_strnstr(list->content, "S ", len))
			write_path_to_file(list->content, cub, 's');
		else if (ft_strnstr(list->content, "F ", len))
			write_color(list->content, cub, 'F');
		else if (ft_strnstr(list->content, "C ", len))
			write_color(list->content, cub, 'C');
		else
			validate_line(list->content, cub);
		list = list->next;
	}
}

void		parser(char *path, t_cub *cub)
{
	int		fd;
	char	*line;
	t_list	*head;
	t_list	*ptr;
	int		ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_exit("Invalid *.cub file", cub);
	head = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(ptr = ft_lstnew(line)))
			ft_exit("Memory allocation failed", cub);
		ft_lstadd_back(&head, ptr);
	}
	if (ret == -1)
		ft_exit("get_next_line error", cub);
	if (!(ptr = ft_lstnew(line)))
		ft_exit("Memory allocation failed", cub);
	ft_lstadd_back(&head, ptr);
	close(fd);
	parse_parameters(head, cub);
	validate_parameters(cub);
	parse_map(cub, head);
}
