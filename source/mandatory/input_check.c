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
	{
		pritnf("Map cannot be opened.\n");
		return (false);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (contains_valid_objects(line, data) == true) // check the textures and colors
			break ;
		line = get_next_line(fd);
	}
	if (line == NULL)
		return (false);
	close(fd);
	if (map_validator(map_file, data) == false) // check errors on the map
		return(false);
	return (true);
}

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
	if (data->no != NULL && data->so != NULL && data->we != NULL
		&& data->ea != NULL && data->floor_color != NULL
		&& data->ceiling_color != NULL)
		return (true);
	else
		return (false);
}

int	is_duplicate(char *line, t_mlx_data *data)
{
	if ((ft_strncmp(line, "NO .", 4) == 0 && data->no != NULL)
		|| (ft_strncmp(line, "SO ", 4) == 0 && data->so != NULL)
		|| (ft_strncmp(line, "WE .", 4) == 0 && data->we != NULL)
		|| (ft_strncmp(line, "EA .", 4) == 0) && data->ea != NULL
		|| (ft_strncmp(line, "F ", 2) == 0) && data->floor_color != NULL
		|| (ft_strncmp(line, "C ", 2) == 0) && data->ceiling_color != NULL)
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
		file = ft_strtrim(line, "NO ");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'N');
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		file = ft_strtrim(line, "SO ");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'S');
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		file = ft_strtrim(line, "WE ");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'W');
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		file = ft_strtrim(line, "EA ");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'E');
	}
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
	if (line[0] == "F")
	{
		trimmed_line = ft_strtrim(line, "F "); // trim off the start
		rgb = ft_split(trimmed_line, ","); // get array of numbers
		if (valid_rgb(rgb) == true) // check the rgb range
			save_color_to_data(rgb, data, 'F'); // save it to struct
		else
			return (false);
	}
	if (line[0] == "C")
	{
		trimmed_line = ft_strtrim(line, "C ");
		rgb = ft_split(trimmed_line, ",");
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

	i = 0;
	while (line[i] != '\0')
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
		data->floor_color[0] == rgb[0];
		data->floor_color[1] == rgb[1];
		data->floor_color[2] == rgb[2];
		data->floor_color[3] == NULL;
	}
	else if (option == 'C')
	{
		data->ceiling_color[0] == rgb[0];
		data->ceiling_color[1] == rgb[1];
		data->ceiling_color[2] == rgb[2];
		data->ceiling_color[3] == NULL;
	}
}

int	map_validathor(char *map_file, t_mlx_data *data) // map always starts from 9th line ??
{
	int	i;
	int fd;
	char	*line;

	i = 0;
	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL && i < 9)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

