#include "../cub3D.h"

static void	search_player(char *str, int x, t_player *player)
{
	int y;

	y = 0;
	if (player->rotation_angle != -1 || player->x != 0 || player->y != 0)
		return ;//TODO: two players, error
	while (str[y] != '\0')
	{
		if (str[y] == 'N' || str[y] == 'S' || str[y] == 'W' || str[y] == 'E')
		{
			player->x = y;
			player->y = x;
			if (str[y] == 'N')
				player->rotation_angle = M_PI/ 2;
			else if (str[y] == 'S')
				player->rotation_angle = 3 * M_PI/ 2;
			else if (str[y] == 'W')
				player->rotation_angle = M_PI;
			else if (str[y] == 'E')
				player->rotation_angle = 0;
			return ;
		}
		y++;
	}
}

static void	validate_line(char *line)
{
	char	*allow_char;

	allow_char = "012NSWE";
	if (ft_atoi(line) == 0)
		return ;//TODO error blank line;
	if (ft_atoi(line) % 10 != 1)
		return ;//TODO error open right wall
	while (*line != '\0')
	{
		if (!ft_strchr(allow_char, *line))
			return ;//TODO: error forbidden char
		line++;
	}
}

void		parse_map(t_vars *vars, t_list **list)
{
	t_list	*ptr;
	int		i;
	int		max_len;

	ptr = *list;
	i = 0;
	max_len = 0;
	while (ptr && ft_atoi(ptr->content) == 0)
		ptr = ptr->next;
	vars->map.map = (char **)malloc(sizeof(char *) * (ft_lstsize(ptr) + 1));
	if (vars->map.map == NULL)
		return ;//TODO: exit
	while (ptr)
	{
		validate_line(ptr->content);
		search_player(ptr->content, i, &vars->player);
		vars->map.map[i++] = ptr->content;
		max_len = max_len < (int)ft_strlen(ptr->content) \
		? (int)ft_strlen(ptr->content) : max_len;
		ptr = ptr->next;
	}
	vars->map.map[i] = NULL;
	vars->map.tile_size = vars->screen.width < vars->screen.height \
	? vars->screen.width / max_len : vars->screen.height / max_len;
	vars->player.x *= vars->map.tile_size;
	vars->player.y *= vars->map.tile_size;
}
