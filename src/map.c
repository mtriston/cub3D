#include "../cub3D.h"

static void	*free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
		free(array[i]);
	free(array);
	return (NULL);
}

static int	count_lines(char *path)
{
	int		i;
	int		fd;
	int		return_value;
	char	*line;

	if (path == NULL)
		return (-1);
	// TODO: exit + error
	i = 0;
	fd = open(path, O_RDONLY);
	line = NULL;
	while ((return_value = get_next_line(fd, &line)))
	{
		i++;
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	if (return_value == -1)
		return (-1);
		//TODO: exit + error
	return (i);
}

/*static int	check_digits(char *line)
{
	while (*line != '\0')
	{
		if (!ft_isdigit(*line))
			return (-1);
		line++;
	}
	return (1);
}
*/
char		**parse_map(char *path)
{
	char 	**map;
	int		fd;
	int		i;
	int		return_value;
	char	*line;

	if (path == NULL)
		//TODO: exit + error
		return (NULL);
	if (!(map = (char **)malloc(sizeof(char *) * (count_lines(path) + 1))))
		// TODO: exit + error
		return (NULL);
	fd = open(path, O_RDONLY);
	line = NULL;
	i = 0;
	while ((return_value = get_next_line(fd, &line)))
	{
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	if (return_value == -1)
		//TODO: free array + exit + error
		return (free_array(map));
	return (map);
}
