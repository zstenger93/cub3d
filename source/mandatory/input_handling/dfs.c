/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:04:54 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/05 11:25:34 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	dfs(char **map, int y, int x, int rows, t_mlx_data *data)
{
	if (y < 2 || x < 2)
		return ;
	if (data->map_copy[y][x] == '1')
		return ;
	if (data->map_copy[y][x] != '0' && data->map_copy[y][x] != 'N'
		&& data->map_copy[y][x] != 'S' && data->map_copy[y][x] != 'E'
		&& data->map_copy[y][x] != 'W' && data->map_copy[y][x] != 'X')
		return ;
	data->map_copy[y][x] = 'X';
	dfs(data->map_copy, x - 1, y, rows, data);
	dfs(data->map_copy, x + 1, y, rows, data);
	dfs(data->map_copy, x, y - 1, rows, data);
	dfs(data->map_copy, x, y + 1, rows, data);
	dfs(data->map_copy, x - 1, y + 1, rows, data);
	dfs(data->map_copy, x + 1, y - 1, rows, data);
	dfs(data->map_copy, x + 1, y + 1, rows, data);
	dfs(data->map_copy, x - 1, y - 1, rows, data);
}
