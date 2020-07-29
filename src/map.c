#include "../cub3D.h"

static void	*free_array(int **array)
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

static int	count_digits(char *line)
{
	int i;

	i = 0;
	while (*line != '\0')
	{
		if (ft_isdigit(*line))
			i++;
		line++;
	}
	return (i);
}

static int	*parse_line(char *line)
{
	int	i;
	int *array;

	i = 0;
	array = (int *)malloc(sizeof(int) * (count_digits(line) + 1));
	if (array == NULL)
		return (NULL);
	//TODO: exit + error
	while (*line != '\0')
	{
		if (ft_isdigit(*line))
		{
			array[i] = *line - '0';
			i++;
		}
		line++;
	}
	array[i] = -1;
	
	return (array);
}

int			**parse_map(char *path)
{
	int 	**map;
	int		fd;
	int		i;
	int		return_value;
	char	*line;

	if (path == NULL)
		//TODO: exit + error
		return (NULL);
	if (!(map = (int **)malloc(sizeof(int *) * (count_lines(path) + 1))))
		// TODO: exit + error
		return (NULL);
	fd = open(path, O_RDONLY);
	line = NULL;
	i = 0;
	while ((return_value = get_next_line(fd, &line)))
	{
		if (!(map[i] = parse_line(line)))
			return (free_array(map));
		i++;
	}
	map[i] = NULL;
	if (return_value == -1)
		//TODO: free array + exit + error
		return (free_array(map));
	return (map);
}
