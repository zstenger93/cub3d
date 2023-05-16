/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:01:40 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/16 12:20:40 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	is_wall(int y, int x, char **matrix)
{
	if (matrix[y][x] == '1')
		return (true);
	return (false);
}

void	is_escape(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		system("pkill afplay &");
		free_data(data);
		system("leaks cub3D");
		exit(0);
	}
}
