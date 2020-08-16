#include "../cub3D.h"

static void	setup_player(char side, int x, int y, t_vars *vars)
{

	if (vars->player.rotation_angle != -1 || vars->player.x != 0 || \
												vars->player.y != 0)
		exit(MORE_THEN_ONE_PLAYER);
	vars->player.x = x;
	vars->player.y = y;
	if (side == 'N')
		vars->player.rotation_angle = M_PI/ 2;
	else if (side == 'S')
		vars->player.rotation_angle = 3 * M_PI/ 2;
	else if (side == 'W')
		vars->player.rotation_angle = M_PI;
	else if (side == 'E')
		vars->player.rotation_angle = 0;
}

static void setup_sprites(t_vars *vars)
{
	int i;
	int x;
	int y;

	y = 0;
	i = 0;
	vars->sprite = malloc_gc(sizeof(t_sprite) * (vars->map.sprites + 1));
	if (vars->sprite == NULL)
		ft_error("Memory allocation for sprites failed");
	while (vars->map.map[y])
	{
		x = 0;
		while (vars->map.map[y][x])
		{
			if (vars->map.map[y][x] == '2')
			{
				vars->sprite[i].x = (x + 0.5) * vars->map.tile_size;
				vars->sprite[i].y = (y + 0.5) * vars->map.tile_size;
				i++;
			}
			x++;
		}
		y++;
	}
}

static void	parse_line(char *str, int y, t_vars *vars)
{
	int x;

	x = 0;
	while (str[x] != '\0')
	{
		if (ft_atoi(str) == 0)
			ft_error("Invalid map");
		if (str[x] == 'N' || str[x] == 'S' || str[x] == 'W' || str[x] == 'E')
			setup_player(str[x], x, y, vars);
		else if (str[x] == '2')
			vars->map.sprites++;
		else if (str[x] != '0' && str[x] != '1' && str[x] != ' ')
			ft_error("Invalid map: Forbidden symbols");
		x++;
	}
}

void		parse_map(t_vars *vars, t_list *ptr)
{
	size_t	i;
	size_t	max;

	i = 0;
	max = 0;
	while (ptr && ft_atoi(ptr->content) == 0)
		ptr = ptr->next;
	if (ft_lstsize(ptr) < 3)
		ft_error("Invalid size of map");
	vars->map.map = (char **)malloc_gc(sizeof(char *) * (ft_lstsize(ptr) + 1));
	if (vars->map.map == NULL)
		ft_error("Memory allocated for map failed");
	while (ptr)
	{
		parse_line(ptr->content, i, vars);
		vars->map.map[i++] = ptr->content;
		max = max < ft_strlen(ptr->content) ? ft_strlen(ptr->content) : max;
		ptr = ptr->next;
	}
	vars->map.map[i] = NULL;
	max = max < i ? i : max;
	vars->map.tile_size = vars->screen.height > vars->screen.width ? \
	vars->screen.height / max : vars->screen.width / max;
	vars->player.x *= vars->map.tile_size;
	vars->player.y *= vars->map.tile_size;
	setup_sprites(vars);
}
