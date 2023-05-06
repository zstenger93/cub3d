/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:04:54 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/06 18:49:13 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	dfs(char **map, int y, int x, t_mlx_data *data)
{
	if (data->map_copy[y][x] == ' ' || data->map_copy[y][x] == '\n')
		return (set_map_error(data));
	if (y < 0 || x < 0)
		return ;
	if (data->map_copy[y][x] == '1')
		return ;
	if (data->map_copy[y][x] != '0' && data->map_copy[y][x] != 'N'
		&& data->map_copy[y][x] != 'S' && data->map_copy[y][x] != 'E'
		&& data->map_copy[y][x] != 'W')
		return ;
	data->map_copy[y][x] = 'X';
	dfs(data->map_copy, y + 1, x + 1, data);
	dfs(data->map_copy, y + 1, x, data);
	dfs(data->map_copy, y + 1, x - 1, data);
	dfs(data->map_copy, y, x + 1, data);
	dfs(data->map_copy, y, x - 1, data);
	dfs(data->map_copy, y - 1, x + 1, data);
	dfs(data->map_copy, y - 1, x, data);
	dfs(data->map_copy, y - 1, x - 1, data);
}

void	set_map_error(t_mlx_data *data)
{
	data->error = true;
}
