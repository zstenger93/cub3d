/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:04 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/13 01:32:25 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	move_keys(void	*param)
{
	t_data		*data;
	t_player	*player;
	t_vector	*p;
	int			i;

	data = (t_data *)param;
	player = &data->minimap->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_down(player->pos.y, player->pos.x, data->minimap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_up(player->pos.y, player->pos.x, data->minimap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_right(player->pos.y, player->pos.x, data->minimap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_left(player->pos.y, player->pos.x, data->minimap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		turn_left(data, player);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		turn_right(data, player);
	p = &data->minimap->player.pos;
	i = ((MINIMAP_SIZE / R) / 2) * (-1);
	draw(data->minimap, data->mlx_data, p, i);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
}

void	move_up(double y, double x, t_map *map)
{
	y -= map->player.dir.y * map->player.speed;
	x -= map->player.dir.x * map->player.speed;
	if (is_wall(y, x, map->matrix))
		return ;
	map->player.pos.y = y;
	map->player.pos.x = x;
	if (map->matrix[(int)y + 1][(int)x] == '1' && y - (int)y > 0.85)
		map->player.pos.y = (int)y + 0.89;
	if (map->matrix[(int)y][(int)x + 1] == '1' && x - (int)x > 0.85)
		map->player.pos.x = (int)x + 0.89;
}

void	move_down(double y, double x, t_map *map)
{
	y += map->player.dir.y * map->player.speed;
	x += map->player.dir.x * map->player.speed;
	if (is_wall(y, x, map->matrix))
		return ;
	map->player.pos.y = y;
	map->player.pos.x = x;
	if (map->matrix[(int)y + 1][(int)x] == '1' && y - (int)y > 0.85)
		map->player.pos.y = (int)y + 0.89;
	if (map->matrix[(int)y][(int)x + 1] == '1' && x - (int)x > 0.85)
		map->player.pos.x = (int)x + 0.89;
}

void	move_left(double y, double x, t_map *map)
{
	double	y_delta;
	double	x_delta;

	y_delta = map->player.dir.x * map->player.speed;
	x_delta = -map->player.dir.y * map->player.speed;
	if (!is_wall(y + y_delta, x + x_delta, map->matrix))
	{
		map->player.pos.y += y_delta;
		map->player.pos.x += x_delta;
	}
}

void	move_right(double y, double x, t_map *map)
{
	double	y_delta;
	double	x_delta;

	y_delta = -map->player.dir.x * map->player.speed;
	x_delta = map->player.dir.y * map->player.speed;
	if (!is_wall(y + y_delta, x + x_delta, map->matrix))
	{
		map->player.pos.y += y_delta;
		map->player.pos.x += x_delta;
	}
}
