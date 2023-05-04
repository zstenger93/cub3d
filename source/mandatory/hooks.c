/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/04 16:29:00 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_wall(int y, int x, char **matrix)
{
	if (matrix[y][x] == '1')
		return (true);
	return (false);
}

void	move(double y, double x, t_minimap *minimap)
{
	if (is_wall(y, x, minimap->matrix))
		return ;
	minimap->player.y = y;
	minimap->player.x = x;
	printf("UP: %f : %f\n", minimap->player.y, minimap->player.x);
}

void	move_keys(void	*param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data*) param;
	player = &data->minimap->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move(player->y - 0.05, player->x, data->minimap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move(player->y + 0.05, player->x, data->minimap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move(player->y, player->x - 0.05, data->minimap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move(player->y, player->x + 0.05, data->minimap);
	// else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))




	
	draw_minimap(data->minimap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
}

void	add_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &move_keys, data);

}

