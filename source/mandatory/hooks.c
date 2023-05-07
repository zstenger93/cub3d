/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/07 15:25:34 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_wall(int y, int x, char **matrix)
{
	if (matrix[y + 1][x + 1] == '1')
		return (true);
	return (false);
}

void	move(double y, double x, t_minimap *minimap)
{
	// y += minimap->player.dir.y;
	// x += minimap->player.dir.x;
	if (is_wall(y, x, minimap->matrix))
		return ;
	minimap->player.pos.y = y;
	minimap->player.pos.x = x;
}

void	move_keys(void	*param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data*) param;
	player = &data->minimap->player;
	draw_minimap(data->minimap, data->mlx_data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		move(player->pos.y - 0.1, player->pos.x, data->minimap);	
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		move(player->pos.y + 0.1, player->pos.x, data->minimap);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		move(player->pos.y, player->pos.x - 0.1, data->minimap);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		move(player->pos.y, player->pos.x + 0.1, data->minimap);
	}


		
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->minimap->player.angle -= 0.1;
			
			printf("%f\n", data->minimap->player.angle);
			write(1, "\nleft\n", 6);
		if (data->minimap->player.angle <= 0)
		{
			data->minimap->player.angle = 2 * M_PI;
		}
			data->minimap->player.dir.x = cos(data->minimap->player.angle);
			data->minimap->player.dir.y = sin(data->minimap->player.angle);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->minimap->player.angle += 0.1;
			printf("%f\n", data->minimap->player.angle);
			write(1, "\nright\n", 7);
		if (data->minimap->player.angle >= 2 * M_PI)
		{
			data->minimap->player.angle = 0;
		}
			data->minimap->player.dir.x = cos(data->minimap->player.angle);
			data->minimap->player.dir.y = sin(data->minimap->player.angle);
	}
	
	
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
}

void	add_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &move_keys, data);

}

