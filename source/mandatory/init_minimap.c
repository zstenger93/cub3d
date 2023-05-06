/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:14:26 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/06 10:33:25 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_player_position(t_minimap *minimap)
{
	int	y;
	int	x;

	y = 0;
	while (minimap->matrix[y] != NULL)
	{
		x = 0;
		while (minimap->matrix[y][x] != '\n' && minimap->matrix[y][x] != '\0')
		{
			if (minimap->matrix[y][x] == 'N')
			{
				minimap->player.pos.y = y;
				minimap->player.pos.x = x;
				printf("\n%f:%f\n\n", minimap->player.pos.y, minimap->player.pos.x);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	get_longest_line(char **map)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (map[i] != NULL)
	{
		if (result < ft_strlen(map[i]))
			result = ft_strlen(map[i]);
		i++;
	}
	return (result);
}

char	*dup3(int size, char ch)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	while (i != size)
	{
		str[i] = ch;
		i++;
	}
	return (str);
}

char	*init_line(char *line, int len)
{
	char	*result;

	result = ft_strjoin(dup3(4, '+'), ft_strdup(line)); // "    line"
	result = ft_strjoin(result, dup3(len - 4 - ft_strlen(line), '+')); // "    line    "
	return(result);
}

char	**init_matrix(char **map, int height)
{
	char	**matrix;
	int		len;
	int		i;

	matrix = malloc(sizeof(char *) * (height + 8 + 1));
	matrix[height + 8] = NULL;
	len = get_longest_line(map) + 8;
	i = 0;
	matrix[i++] = dup3(len, '+');
	matrix[i++] = dup3(len, '+');
	matrix[i++] = dup3(len, '+');
	matrix[i++] = dup3(len, '+');
	while (map[i - 4] != NULL)
	{
		matrix[i] = init_line(map[i - 4], len);
		i++;
	}
	matrix[i++] = dup3(len, '+');
	matrix[i++] = dup3(len, '+');
	matrix[i++] = dup3(len, '+');
	matrix[i++] = dup3(len, '+');
	return (matrix);
}

t_minimap*	init_minimap(t_mlx_data *mlx_data, mlx_t *mlx)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	minimap->matrix = init_matrix(mlx_data->raw_map, mlx_data->map_length);
	ft_print_2d_char_array(minimap->matrix);
	// set_player_position(minimap); // + init player dir & plane
	// minimap->img_map = mlx_new_image(mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	return (minimap);
}
