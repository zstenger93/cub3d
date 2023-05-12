/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:00:50 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/12 15:58:05 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// do check player duplicates / no player
// check invalid char on the lines
int	map_validathor(char *map_file, t_mlx_data *data, int fd)
{
	int			i;
	static int	k = 0;
	char		*line;

	line = get_next_line(fd);
	while (k++ != data->reading_pos)
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
		data->raw_map[i++] = copy_map_line(line);
		free(line);
		line = get_next_line(fd);
	}
	if (map_checks(data, i) == false)
		return (false);
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
			|| line[i] == 'E' || line[i] == 'D')
		{
			if (map_has_multiple_players_or_none(line[i], 'N') == true)
				return (true);
			i++;
		}
		else if (line[i] == '\0')
			return (false);
		else
			return (printf("%s%c.", INVALID_CHAR, line[i]), true);
	}
	return (false);
}

int	map_has_multiple_players_or_none(char c, char option)
{
	static int	n = 0;
	static int	s = 0;
	static int	w = 0;
	static int	e = 0;

	if (c == 'N')
		n++;
	else if (c == 'S')
		s++;
	else if (c == 'W')
		w++;
	else if (c == 'E')
		e++;
	if (n > 1 || s > 1 || w > 1 || e > 1)
		return (ft_printf("Error! Player duplicates on the map."), true);
	if (option == 'Y')
	{
		if ((n + s + w + e) == 0)
			return (printf("Error! No player found on the map.\n"), true);
		else if ((n + s + w + e) > 1)
			return (printf("Error! Too many players.\n"), true);
	}
	return (false);
}
