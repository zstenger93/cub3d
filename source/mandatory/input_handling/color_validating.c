/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:59:24 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/05 15:16:00 by zstenger         ###   ########.fr       */
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

	if (commacounter(line) == false || rgb_contains_letters(line) == true)
		return (false);
	if (line[0] == 'F')
	{
		trimmed_line = ft_strtrim(line, "F \n");
		rgb = ft_split(trimmed_line, ',');
		free(trimmed_line);
		if (valid_rgb(rgb) == true)
			save_color_to_data(rgb, data, 'F');
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
	{
		printf("Error! The amount of comma in the RGB list is wrong.\n");
		return (false);
	}
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
