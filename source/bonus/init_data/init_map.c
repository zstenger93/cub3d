/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:14:26 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/08 11:50:33 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

t_map	*init_map(t_mlx_data *mlx_data, mlx_t *mlx)
{
	t_map	*minimap;

	minimap = malloc(sizeof(t_map));
	minimap->matrix = init_matrix(mlx_data->raw_map, mlx_data->map_length);
	ft_print_2d_char_array(minimap->matrix);
	set_player_position(minimap);
	minimap->img_map = mlx_new_image(mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	minimap->img_tmp = mlx_new_image(mlx, WIDTH, HEIGHT);
	return (minimap);
}

char	**init_matrix(char **m, int height)
{
	char	**matrix;
	int		len;
	int		i;

	matrix = malloc(sizeof(char *) * (height + MINIMAP_SIZE / R + 1));
	matrix[height + MINIMAP_SIZE / R] = NULL;
	len = get_longest_line(m) + (MINIMAP_SIZE / R) - 1;
	i = -1;
	while (++i < (MINIMAP_SIZE / R) / 2)
		matrix[i] = dup3(len, 'V');
	while (m[i - (MINIMAP_SIZE / R) / 2] != NULL)
	{
		matrix[i] = init_line(m[i - (MINIMAP_SIZE / R) / 2], len);
		i++;
	}
	while (i != height + MINIMAP_SIZE / R)
		matrix[i++] = dup3(len, 'V');
	return (matrix);
}

char	*init_line(char *old_line, int l)
{
	char	*res;
	char	*line;
	int		i;
	int		k;

	i = 0;
	while (old_line[i] != '\0' && old_line[i] != '\n')
		i++;
	line = ft_strdup2(old_line, 0, i);
	k = ft_strlen(line);
	old_line = ft_strdup(line);
	res = dup3((MINIMAP_SIZE / R) / 2, 'V');
	res = ft_strjoin(res, old_line);
	res = ft_strjoin(res, dup3(l - (MINIMAP_SIZE / R) / 2 - k, 'V'));
	i = -1;
	while (res[++i] != '\0')
		if (res[i] == ' ')
			res[i] = 'V';
	return (res);
}

void	set_player_position(t_map *minimap)
{
	int		y;
	int		x;
	double	plane_length;

	y = 0;
	minimap->player.speed = 0.07;
	while (minimap->matrix[y] != NULL)
	{
		x = 0;
		while (minimap->matrix[y][x] != '\n' && minimap->matrix[y][x] != '\0')
		{
			if (ft_pf_strchr("NESW", minimap->matrix[y][x]) != NULL)
			{
				minimap->player.pos.y = y;
				minimap->player.pos.x = x;
				minimap->player.dir.x = cos(get_angle(minimap->matrix[y][x]));
				minimap->player.dir.y = sin(get_angle(minimap->matrix[y][x]));
				set_plan(&minimap->player.plane, minimap->matrix[y][x]);
				minimap->matrix[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
