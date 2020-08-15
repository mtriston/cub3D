#include "../cub3D.h"

static void	write_resolution(char *str, t_screen *screen)
{
	if (screen->width != 0 || screen->height != 0)
		return ;
	//TODO: exit
	str = ft_strchr(str, 'R');
	str++;
	screen->width = ft_atoi(str);
	while (*str && ft_isspace(*str))
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	screen->height = ft_atoi(str);
}

static void	write_color(char *str, t_map *map, char type)
{
	int		c1;
	int		c2;
	int		c3;
	
	str = ft_strchr(str, type);
	str++;
	while (*str && ft_isspace(*str))
		str++;
	c1 = ft_atoi(++str);
	str = ft_strchr(str, ',');
//TODO: exit
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
		import_texture(str, &vars->texture.north, vars->screen.mlx);
	if (type == 'S')
		import_texture(str, &vars->texture.south, vars->screen.mlx);
	if (type == 'W')
		import_texture(str, &vars->texture.west, vars->screen.mlx);
	if (type == 'E')
		import_texture(str, &vars->texture.east, vars->screen.mlx);
	if (type == 's')
		import_texture(str, &vars->sprite.img, vars->screen.mlx);
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
			write_resolution(ptr->content, &vars->screen);
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
	
	fd = open(path, O_RDONLY);
	head = NULL;
	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	close(fd);
	parse_parameters(&head, vars);
	parse_map(vars, &head);
}
