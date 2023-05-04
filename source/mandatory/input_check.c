#include "../../include/cub3d.h"

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
		// printf("working\n");
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
		if (contains_valid_objects(line, data) == true) // check the textures and colors
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
	if (map_validathor(map_file, data, fd) == false) // check errors on the map
		return(false);
	ft_print_2d_char_array(data->raw_map);
	exit(0);
	return (close(fd), true);
}
	// print_map_objects(data);
	// exit(0);

//check duplicates. DONE
int	contains_valid_objects(char *line, t_mlx_data *data)
{
	if (is_duplicate(line, data) == true)
		return (false);
	if (ft_strncmp(line, "NO .", 4) == 0 || ft_strncmp(line, "SO .", 4) == 0
		|| ft_strncmp(line, "WE .", 4) == 0 || ft_strncmp(line, "EA .", 4) == 0)
		if (validate_texture(line, data) == false)
			return (false);
	if ((ft_strncmp(line, "F ", 2) == 0 && ft_isdigit(line[3]) == true)
		|| (ft_strncmp(line, "C ", 2) == 0 && ft_isdigit(line[3]) == true))
		if (validate_color(line, data) == false)
			return (false);
	if (ft_strcmp(data->no, "X") == false && ft_strcmp(data->so, "X") == false
		&& ft_strcmp(data->we, "X") == false && ft_strcmp(data->ea, "X") == false
		&& data->floor_color[0] != -1 && data->ceiling_color[0] != -1)
		return (true);
	else
		return (false);
}

int	is_duplicate(char *line, t_mlx_data *data)
{
	if ((ft_strncmp(line, "NO .", 4) == 0 && ft_strcmp(data->no, "X") == false)
		|| (ft_strncmp(line, "SO ", 4) == 0 && ft_strcmp(data->so, "X") == false)
		|| (ft_strncmp(line, "WE .", 4) == 0 && ft_strcmp(data->we, "X") == false)
		|| (ft_strncmp(line, "EA .", 4) == 0 && ft_strcmp(data->ea, "X") == false)
		|| (ft_strncmp(line, "F ", 2) == 0) && data->floor_color[0] != -1
		|| (ft_strncmp(line, "C ", 2) == 0) && data->ceiling_color[0] != -1)
	{
		printf("Error! Duplicates found in the map file for one of the attribute.\n");
		return (true);
	}
	return (false);
}

int	validate_texture(char *line, t_mlx_data *data)
{
	char	*file;

	if (ft_strncmp(line, "NO", 2) == 0)
	{
		file = ft_strtrim(line, "NO \n");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'N');
		else
			return (false);
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		file = ft_strtrim(line, "SO \n");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'S');
		else
			return (false);
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		file = ft_strtrim(line, "WE \n");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'W');
		else
			return (false);
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		file = ft_strtrim(line, "EA \n");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'E');
		else
			return (false);
	}
	return (true);
}

int	it_can_be_opened(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error! The %s texture file cannot be opened.\n", file);
		return (false);
	}
	close(fd);
	return (true);
}

void	save_texture_to_data(char *file, t_mlx_data *data, char option) // save the path to the textures
{
	if (option == 'N')
		data->no = ft_strdup(file);
	if (option == 'S')
		data->so = ft_strdup(file);
	if (option == 'W')
		data->we = ft_strdup(file);
	if (option == 'E')
		data->ea = ft_strdup(file);
}

int	validate_color(char *line, t_mlx_data *data)
{
	char	*trimmed_line;
	char	**rgb;

	// check between numbers. DONE
	if (commacounter(line) == false || rgb_contains_letters(line) == true)
		return (false);
	if (line[0] == 'F')
	{
		trimmed_line = ft_strtrim(line, "F \n"); // trim off the start
		rgb = ft_split(trimmed_line, ','); // get array of numbers
		free(trimmed_line);
		if (valid_rgb(rgb) == true) // check the rgb range
			save_color_to_data(rgb, data, 'F'); // save it to struct
		else
			return (false);
	}
	if (line[0] == 'C')
	{
		trimmed_line = ft_strtrim(line, "C \n");
		rgb = ft_split(trimmed_line, ',');
		free(trimmed_line);
		if (valid_rgb(rgb) == true)
			save_color_to_data(rgb, data, 'C');
		else
			return (false);
	}
	return (true);
}

int	commacounter(char *line) // checking the amount of commas in the rgb list
{
	int	i;
	int	commacount;

	i = 0;
	commacount = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			commacount++;
		i++;
	}
	if (commacount != 2)
	{
		printf("Error! The amount of comma in the RGB list is wrong.\n");
		return (false);
	}
	return (true);
}

int	valid_rgb(char **rgb)
{
	//check for chars in string. DONE IN PREVIOUS
	if ((ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[0]) < 0)
		&& (ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[1]) < 0)
		&& (ft_atoi(rgb[2]) > 255 || ft_atoi(rgb[2]) < 0))
	{
		printf("The RGB color is out of range, all numbers must be between 0 and 255.\n");
		return (false);
	}
	else
		return (true);
}

int	rgb_contains_letters(char *line) // check if there are letters in the rgb list
{
	int	i;

	i = 2;
	while (i < 13)
	{
		if (line[i] == ',' || ft_isdigit(line[i]) == true)
			i++;
		else
			return (true);
	}
	return (false);
}

void	save_color_to_data(char **rgb, t_mlx_data *data, char option) // save the rgb colors as int
{
	if (option == 'F')
	{
		data->floor_color[0] = ft_atoi(rgb[0]);
		data->floor_color[1] = ft_atoi(rgb[1]);
		data->floor_color[2] = ft_atoi(rgb[2]);
	}
	else if (option == 'C')
	{
		data->ceiling_color[0] = ft_atoi(rgb[0]);
		data->ceiling_color[1] = ft_atoi(rgb[1]);
		data->ceiling_color[2] = ft_atoi(rgb[2]);
	}
}

int	map_validathor(char *map_file, t_mlx_data *data, int fd) // map always starts from 9th line ??
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
	write(1, line, ft_strlen(line));
	while (line != NULL)
	{
		if (line_has_invalid_chars(line) == true) // check invalid char on the lines
			return (false);
		data->raw_map[i] = copy_map_line(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	data->raw_map[i] = NULL;
	close(fd);
	// if () // map checks
	return (true);
}

void	get_map_length(int fd, char *map_file, t_mlx_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && line_cotains_only_spaces(line) == true) // skip lines with only space on them
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

void	free_char_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*copy_map_line(char *content)
{
	int		i;
	int		content_len;
	char	*line;

	i = -1;
	content_len = ft_strlen(content) + 1;
	line = malloc(sizeof(char) * content_len);
	while (content[++i] != '\0')
		line[i] = content[i];
	line[i] = '\0';
	return (line);
}

void	ft_print_2d_char_array(char **array_2d)
{
	int	i;
	int	k;

	if (array_2d == NULL)
		return ;
	i = 0;
	while (array_2d[i] != NULL)
	{
		k = 0;
		while (array_2d[i][k] != '\0')
		{
			put_chars(array_2d[i][k]);
			k++;
		}
		i++;
	}
		// printf("%s", array_2d[i++]);
}

char	put_chars(char c)
{
	char	colored_0[] = "\e[1;37m0\e[0m";
	char	colored_1[] = "\e[1;31m1\e[0m";
	char	colored_e[] = "\e[1;33mE\e[0m";
	char	colored_s[] = "\e[1;32mS\e[0m";
	char	colored_w[] = "\e[1;35mW\e[0m";
	char	colored_n[] = "\e[1;34mN\e[0m";
	

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
	return (0);
}