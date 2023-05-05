/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:00:50 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/05 10:42:23 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// check invalid char on the lines
int	map_validathor(char *map_file, t_mlx_data *data, int fd)
{
	int		i;
	int		k;
	char	*line;

	k = 0;
	line = get_next_line(fd);
	while(k++ != data->reading_pos)
	{
		free(line);
		line = get_next_line(fd);
	}
	data->raw_map = malloc(sizeof(char *) * (data->map_length + 1));
	i = 0;
	free(line);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line_has_invalid_chars(line) == true)
			return (false);
		data->raw_map[i] = copy_map_line(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->raw_map[i] = NULL;

	return (close(fd), true);
}

// skip lines with only space on them
void	get_map_length(int fd, char *map_file, t_mlx_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && line_cotains_only_spaces(line) == true)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		data->map_length++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		printf("Map cannot be opened.\n");
		exit(0);
	}
}

int	line_cotains_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'
			|| line[i] == '\r' || line[i] == '\f')
			i++;
		else
			return (false);
	}
	return (true);
}

int	line_has_invalid_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1'
			|| line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E')
			i++;
		else if (line[i] == '\0')
			return (false);
		else
		{
			printf("Error! Map has at least one invalid char: %c.", line[i]);
			return (true);
		}
	}
	return (false);
}
