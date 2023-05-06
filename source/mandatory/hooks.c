/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/06 08:50:52 by jergashe         ###   ########.fr       */
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
	minimap->player.pos.y = y;
	minimap->player.pos.x = x;
	printf("UP: %f : %f\n", minimap->player.pos.y, minimap->player.pos.x);
}

void	move_keys(void	*param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data*) param;
	player = &data->minimap->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move(player->pos.y - 0.5, player->pos.x, data->minimap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move(player->pos.y + 0.5, player->pos.x, data->minimap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move(player->pos.y, player->pos.x - 0.5, data->minimap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move(player->pos.y, player->pos.x + 0.5, data->minimap);
	

	draw_minimap(data->minimap, data->mlx_data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
}

void	add_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &move_keys, data);

}

