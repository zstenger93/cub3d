/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/04 12:18:31 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_wall(int y, int x, char **matrix)
{
	// write(1, "IN IS_WALL\n", 12);
	
	// char * new_y = ft_itoa(y);
	// write(1, new_y, ft_strlen(new_y));

	// write(1, " : ", 5);
	
	// char * new_x = ft_itoa(x);
	// write(1, new_x, ft_strlen(new_x));


	// write(1, "\n", 2);
	if (matrix[y][x] == '0')
		return (false);
	return (true);
}

void	move(void	*param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data*) param;
	player = &data->minimap->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (is_wall(player->y - 0.03, player->x, data->minimap->matrix) == false)
		{
			player->y -= 0.03;
			printf("UP: %f : %f\n", player->y, player->x);
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (is_wall(player->y + 0.03, player->x, data->minimap->matrix) == false)
		{
			printf("DOWN: %f : %f\n", player->y, player->x);
			player->y += 0.03;
		}
	}
	draw_minimap(data->minimap);
}

void	add_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &move, data);

	
}

