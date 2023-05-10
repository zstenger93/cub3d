/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/09 17:24:25 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_wall(int y, int x, char **matrix)
{
	if (matrix[y + 1][x + 1] == '1')
		return (true);
	return (false);
}

void	move(double y, double x, t_map *map)
{
	if (is_wall(y, x, map->matrix))
		return ;

	// if (map->matrix[(int)(map->player.pos.y + map->player.dir.y * 0.1)][(int)map->player.pos.x])
	// 	map->player.pos.y += map->player.dir.y * 30;
	// if (map->matrix[(int)map->player.pos.y][(int)(map->player.pos.x + map->player.dir.x * 0.1)])
	// 	map->player.pos.x += map->player.dir.x * 30;

	map->player.pos.y = y;
	map->player.pos.x = x;
}

// if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
// if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;

void	move_keys(void	*param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data*) param;
	player = &data->minimap->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move(player->pos.y - 0.1, player->pos.x, data->minimap);	
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move(player->pos.y + 0.1, player->pos.x, data->minimap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move(player->pos.y, player->pos.x - 0.1, data->minimap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move(player->pos.y, player->pos.x + 0.1, data->minimap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		turn_left(data, player);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		turn_right(data, player);
	draw_minimap(data->minimap, data->mlx_data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
}

void	turn_left(t_data *data, t_player *playr)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = playr->dir.x;
	playr->dir.x = playr->dir.x * cos(-0.1) - playr->dir.y * sin(-0.1);
	playr->dir.y = old_dir_x * sin(-0.1) + playr->dir.y * cos(-0.1);
	old_plane_x = playr->plane.x;
	playr->plane.x = playr->plane.x * cos(-0.1) - playr->plane.y * sin(-0.1);
	playr->plane.y = old_plane_x * sin(-0.1) + playr->plane.y * cos(-0.1);
}

void	turn_right(t_data *data, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(0.1) - player->dir.y * sin(0.1);
	player->dir.y = old_dir_x * sin(0.1) + player->dir.y * cos(0.1);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(0.1) - player->plane.y * sin(0.1);
	player->plane.y = old_plane_x * sin(0.1) + player->plane.y * cos(0.1);
}

void	add_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &move_keys, data);
}
