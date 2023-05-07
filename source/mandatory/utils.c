/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:17:08 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/07 14:08:40 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	write2(int n)
{
	char *str = ft_itoa(n);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

char *double_to_string(double num) {
    char *str;
    int len;

    // Determine the length of the string representation
    // using snprintf() with a NULL format string
    len = snprintf(NULL, 0, "%f", num);

    // Allocate memory for the string
    str = malloc(len + 1);

    // Convert the double to a string using snprintf()
    snprintf(str, len + 1, "%f", num);

    return str;
}

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

char	*ft_strdup2(char *str, int start, int end)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (end - start + 1));
	if (result == NULL)
		return (NULL);
	i = -1;
	while (start + ++i != end)
		result[i] = str[i + start];
	result[i] = '\0';
	return (result);
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

int	is_duplicate(char *line, t_mlx_data *data)
{
	if ((ft_strncmp(line, "NO .", 4) == 0 && ft_strcmp(data->no, "X") == false)
		|| (ft_strncmp(line, "SO ", 4) == 0
			&& ft_strcmp(data->so, "X") == false)
		|| (ft_strncmp(line, "WE .", 4) == 0
			&& ft_strcmp(data->we, "X") == false)
		|| (ft_strncmp(line, "EA .", 4) == 0
			&& ft_strcmp(data->ea, "X") == false)
		|| (ft_strncmp(line, "F ", 2) == 0) && data->floor_color[0] != -1
		|| (ft_strncmp(line, "C ", 2) == 0) && data->ceiling_color[0] != -1)
		return (ft_printf(DUPLICATE), true);
	return (false);
}
