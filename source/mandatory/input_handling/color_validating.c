/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:59:24 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/06 10:45:32 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// trim off the start
// get array of numbers
// check the rgb range
// save it to struct
// check between numbers. DONE
int	validate_color(char *line, t_mlx_data *data)
{
	char	*trimmed_line;
	char	**rgb;

	if (commacounter(line) == false || rgb_contains_letters(line) == true
		|| has_duplicate_rgb(line) == true)
		return (false);
	if (line[0] == 'F')
	{
		rgb = split_rgb(line, "F \n");
		if (valid_rgb(rgb) == true)
			save_color_to_data(rgb, data, 'F');
		else
			return (false);
	}
	if (line[0] == 'C')
	{
		rgb = split_rgb(line, "C \n");
		if (valid_rgb(rgb) == true)
			save_color_to_data(rgb, data, 'C');
		else
			return (false);
	}
	return (true);
}

char	**split_rgb(char *line, char *trim_with)
{
	char	*trimmed_line;
	char	**rgb;

	trimmed_line = ft_strtrim(line, trim_with);
	rgb = ft_split(trimmed_line, ',');
	free(trimmed_line);
	return (rgb);
}

int	has_duplicate_rgb(char *line)
{
	int	f;
	int	c;

	f = 0;
	c = 0;
	if (line[0] == 'F')
		f++;
	else if (line[0] == 'C')
		c++;
	else if (f != 1 || c != 1)
		return (printf("Error! Duplicate rgb attributes.\n"), true);
	return (false);
}

// checking the amount of commas in the rgb list
int	commacounter(char *line)
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
		return (printf("%s", COMMA), false);
	return (true);
}

	//check for chars in string. DONE IN PREVIOUS
int	valid_rgb(char **rgb)
{
	if ((ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[0]) < 0)
		&& (ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[1]) < 0)
		&& (ft_atoi(rgb[2]) > 255 || ft_atoi(rgb[2]) < 0))
		return (printf("%s%s", RGB_IS, OUT_OF_RANGE), false);
	else
		return (true);
}

// check if there are letters in the rgb list
int	rgb_contains_letters(char *line)
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
