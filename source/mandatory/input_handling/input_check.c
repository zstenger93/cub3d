/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:59:28 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/05 11:18:47 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

		// printf("working\n");
int	input_check(int argc, char *argv, t_mlx_data *data)
{
	int i;

	i = ft_strlen(argv);
	if (argc != 2)
	{
		ft_printf("Wrong number of arguments.\n");
		ft_printf("Please launch it as ./cub3d path/to/map.\n");
		return (false);
	}
	else if (argv && i > 3 && argv[i - 1] == 'b' && argv[i - 2] == 'u'
		&& argv[i - 3] == 'c' && argv[i - 4] == '.')  // checking .cub format
	{
		if (validate_content(argv, data) == false) //check the file content
			return (false);
	}
	else
	{
		printf("Map is file is in a wrong format. It should have .ber format.\n");
		return (false);
	}
	return (true);
}

// check the textures and colors
// check errors on the map
int	validate_content(char *map_file, t_mlx_data *data)
{
	int fd;
	char *line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (printf("Map cannot be opened.\n"), false);
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->reading_pos++;
		if (contains_valid_objects(line, data) == true)
		{
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line == NULL)
		return (false);
	get_map_length(fd, map_file, data);
	if (map_validathor(map_file, data, fd) == false || map_checks(data) == false)
	{
		printf("invalid map\n");
		return(false);
	}
	return (close(fd), true);
}
	// print_map_objects(data);
	// exit(0);

int	map_checks(t_mlx_data *data)
{
	// if (wall_check(data) == false)
	// 	return (false);
	data->map_copy = malloc(sizeof(char *) * (data->map_length + 1));
	data->map_copy = copy_2d_char_array(data->raw_map);
	dfs(data->map_copy, 3, 3, data->map_length, data);
	ft_print_2d_char_array(data->map_copy);
	return (true);
}

int	wall_check(t_mlx_data *data)
{
	int	i;
	int	k;

	while (data->raw_map[i] != NULL)
	{
		k = 0;
		while (data->raw_map[i][k] == ' ' || data->raw_map[i][k] == '\t' || data->raw_map[i][k] == '\0')
			k++;
		if (data->raw_map[i][k] != '1')
		{
			printf("%c\n", data->raw_map[i][k]);
			return (false);
		}
		else
			i++;
	}
	return (true);
}

char	put_chars(char c)
{
	char	colored_0[] = "\e[1;37m0\e[0m";
	char	colored_1[] = "\e[1;31m1\e[0m";
	char	colored_e[] = "\e[1;33mE\e[0m";
	char	colored_s[] = "\e[1;32mS\e[0m";
	char	colored_w[] = "\e[1;35mW\e[0m";
	char	colored_n[] = "\e[1;34mN\e[0m";
	char	colored_x[] = "\e[1;34mX\e[0m";

	if (c == '0')
		write(1, &colored_0, 13);
	if (c == '1')
		write(1, &colored_1, 13);
	if (c == 'N')
		write(1, &colored_n, 13);
	if (c == 'S')
		write(1, &colored_s, 13);
	if (c == 'W')
		write(1, &colored_w, 13);
	if (c == 'E')
		write(1, &colored_e, 13);
	if (c == '\n')
		write(1, "\n", 2);
	if (c == ' ')
		write(1, " ", 1);
	if (c == 'X')
		write(1, &colored_x, 13);
	return (0);
}
