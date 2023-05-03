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
		// printf("yes\n");
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

//check duplicates
int	contains_valid_objects(char *line, t_mlx_data *data)
{
	if (ft_strncmp(line, "NO .", 4) == 0 || ft_strncmp(line, "SO ", 4) == 0
		|| ft_strncmp(line, "WE .", 4) == 0 || ft_strncmp(line, "EA ", 4) == 0)
	{
		if (validate_texture(line) == true)
			save_texture_to_data(line, data);
		else
			return (false);
	}
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		if (validate_color(line, data) == false)
			return (false);
	}
	if (data->no != NULL && data->so != NULL && data->we != NULL
		&& data->ea != NULL && data->floor_color != NULL
		&& data->ceiling_color != NULL)
		return (true);

}

int	validate_texture(char *line)
{
	
}

void	save_texture_to_data(char *line, t_mlx_data *data) // save the path to the textures
{

}

int	validate_color(char *line, t_mlx_data *data)
{
	char	*trimmed_line;
	char	**rgb;

	// check between numbers
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

int	valid_rgb(char **rgb)
{
	//check for chars in string
	if ((ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[0]) < 0)
		&& (ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[1]) < 0)
		&& (ft_atoi(rgb[2]) > 255 || ft_atoi(rgb[2]) < 0))
		return (false);
	else
		return (true);
}

void	save_color_to_data(char **rgb, t_mlx_data *data, char option) // save the rgb colors as int
{
	
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

