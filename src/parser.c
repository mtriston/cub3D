#include "../cub3D.h"

static void	write_resolution(char *str, t_vars *vars)
{
	int m_w;
	int m_h;

	mlx_get_screen_size(vars->screen.mlx, &m_w, &m_h);
	if (vars->screen.width != 0 || vars->screen.height != 0)
		ft_exit("More then one resolution's configuration", vars);
	str = ft_strchr(str, 'R');
	str++;
	vars->screen.width = ft_atoi(str);
	while (*str && ft_isspace(*str))
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	vars->screen.height = ft_atoi(str);
	if (vars->screen.width <= 0 || vars->screen.height <= 0)
		ft_exit("Invalid resolution", vars);
	vars->screen.width = vars->screen.width > m_w ? m_w : vars->screen.width;
	vars->screen.height = \
						vars->screen.height > m_h ? m_h : vars->screen.height;
}

static void	write_color(char *str, t_map *map, char type)
{
	int		c1;
	int		c2;
	int		c3;
	//TODO: add check error
	str = ft_strchr(str, type);
	str++;
	while (*str && ft_isspace(*str))
		str++;
	c1 = ft_atoi(++str);
	str = ft_strchr(str, ',');
	c2 = ft_atoi(++str);
	str = ft_strchr(str, ',');
	c3 = ft_atoi(++str);
	if (type == 'C')
		map->ceil_color = create_trgb(0, c1, c2, c3); 
	else if (type == 'F')
		map->floor_color = create_trgb(0, c1, c2, c3); 
}

static void	write_path_to_file(char *str, t_vars *vars, char type)
{
	char *temp;

	str += 2;
	while (*str && ft_isspace(*str))
		str++;
	temp = ft_strchr(str, ' ');
	if (temp)
		*temp = '\0';
	if (type == 'N')
		import_texture(str, &vars->texture.north, vars);
	if (type == 'S')
		import_texture(str, &vars->texture.south, vars);
	if (type == 'W')
		import_texture(str, &vars->texture.west, vars);
	if (type == 'E')
		import_texture(str, &vars->texture.east, vars);
	if (type == 's')
		import_texture(str, &vars->texture.sprite, vars);
}

static void	parse_parameters(t_list **list, t_vars *vars)
{
	t_list *ptr;
	int		len;

	ptr = *list;
	while (ptr)
	{
		len = ft_strlen(ptr->content);
		if (ft_strnstr(ptr->content, "R ", len))
			write_resolution(ptr->content, vars);
		else if (ft_strnstr(ptr->content, "NO ", len))
			write_path_to_file(ptr->content, vars, 'N');
		else if (ft_strnstr(ptr->content, "SO ", len))
			write_path_to_file(ptr->content, vars, 'S');
		else if (ft_strnstr(ptr->content, "WE ", len))
			write_path_to_file(ptr->content, vars, 'W');
		else if (ft_strnstr(ptr->content, "EA ", len))
			write_path_to_file(ptr->content, vars, 'E');
		else if (ft_strnstr(ptr->content, "S ", len))
			write_path_to_file(ptr->content, vars, 's');
		else if (ft_strnstr(ptr->content, "F ", len))
			write_color(ptr->content, &vars->map, 'F');
		else if (ft_strnstr(ptr->content, "C ", len))
			write_color(ptr->content, &vars->map, 'C');
		ptr = ptr->next;
	}
}

void		parser(char *path, t_vars *vars)
{
	int		fd;
	char	*line;
	t_list	*head;
	t_list	*ptr;
	int		ret;
	if (!path)
		return ;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_exit("Invalid *.cub file", vars);
	head = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(ptr = ft_lstnew(line)))
			ft_exit("Memory allocation failed", vars);
		ft_lstadd_back(&head, ptr);
	}
	if (ret == -1)
	    ft_exit("get_next_line error", vars);
	if (!(ptr = ft_lstnew(line)))
		ft_exit("Memory allocation failed", vars);
	ft_lstadd_back(&head, ptr);
	close(fd);
	parse_parameters(&head, vars);
	parse_map(vars, head);
}
