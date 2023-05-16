/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:02:29 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/16 10:29:14 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

char	*get_line(int fd, char *line)
{
	char	*return_line;

	free(line);
	return_line = get_next_line(fd);
	return (return_line);
}

char	**copy_2d_char_array(char **array)
{
	int		i;
	char	**result;

	i = 0;
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (result == NULL)
		return (p_err(MALLOC_FAIL), NULL);
	i = -1;
	while (array[++i] != NULL)
		result[i] = copy_map_line(array[i]);
	result[i] = NULL;
	return (result);
}

// void	ft_print_2d_char_array(char **array_2d)
// {
// 	int	i;
// 	int	k;

// 	if (array_2d == NULL)
// 		return ;
// 	i = 0;
// 	while (array_2d[i] != NULL)
// 	{
// 		k = 0;
// 		while (array_2d[i][k] != '\0')
// 		{
// 			put_chars(array_2d[i][k]);
// 			k++;
// 		}
// 		write(1, "\n", 2);
// 		i++;
// 	}
// }

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
	if (line == NULL)
		return (p_err(MALLOC_FAIL), NULL);
	while (content[++i] != '\0')
		line[i] = content[i];
	line[i] = '\0';
	return (line);
}

int	it_can_be_opened(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		p_err(TEX_FILE_WRONG, file);
		return (false);
	}
	close(fd);
	return (true);
}
