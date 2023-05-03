#include "../../include/cub3d.h"

int	get_height_of_map(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return(count);
		count++;
		free(line);
		line = NULL;
	}
	return (count);
}

int	get_width_of_map(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	count = ft_strlen(line);
	free(line);
	return (count);
}

char	**get_matrix(t_minimap *minimap, int fd)
{
	char	**matrix;
	int		i;

	matrix = malloc(sizeof(char *) * (minimap->height + 1));
	matrix[minimap->height] = NULL;
	i = 0;
	while (i < minimap->height)
	{
		matrix[i] = get_next_line(fd);
		i++;
	}
	return (matrix);
}


uint32_t get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
