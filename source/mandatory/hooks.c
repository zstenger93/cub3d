/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/10 13:19:23 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_wall(int y, int x, char **matrix)
{
	if (matrix[y][x] == '1')
		return (true);
	return (false);
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

void move_left(double y, double x, t_map *map)
{
    double y_delta = map->player.dir.x * map->player.speed;
    double x_delta = -map->player.dir.y * map->player.speed;
    if (!is_wall(y + y_delta, x + x_delta, map->matrix))
    {
        map->player.pos.y += y_delta;
        map->player.pos.x += x_delta;
    }
}

void move_right(double y, double x, t_map *map)
{
    double y_delta = -map->player.dir.x * map->player.speed;
    double x_delta = map->player.dir.y * map->player.speed;
    if (!is_wall(y + y_delta, x + x_delta, map->matrix))
    {
        map->player.pos.y += y_delta;
        map->player.pos.x += x_delta;
    }
}


void	move(double y, double x, t_map *map)
{
	y += map->player.dir.y;
	x += map->player.dir.x;
	if (is_wall(y, x, map->matrix))
		return ;
	map->player.pos.y = y;
	map->player.pos.x = x;
	if (map->matrix[(int)y + 1][(int)x] == '1' && y - (int)y > 0.85)
		map->player.pos.y = (int)y + 0.89;
	if (map->matrix[(int)y][(int)x + 1] == '1' && x - (int)x > 0.85)
		map->player.pos.x = (int)x + 0.89;
}

void	move_keys(void	*param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data*) param;
	player = &data->minimap->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_down(player->pos.y, player->pos.x, data->minimap);	
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_up(player->pos.y, player->pos.x, data->minimap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_right(player->pos.y, player->pos.x, data->minimap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_left(player->pos.y, player->pos.x, data->minimap);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) )
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
	playr->dir.x = playr->dir.x * cos(-0.05) - playr->dir.y * sin(-0.05);
	playr->dir.y = old_dir_x * sin(-0.05) + playr->dir.y * cos(-0.05);
	old_plane_x = playr->plane.x;
	playr->plane.x = playr->plane.x * cos(-0.05) - playr->plane.y * sin(-0.05);
	playr->plane.y = old_plane_x * sin(-0.05) + playr->plane.y * cos(-0.05);
}

void	turn_right(t_data *data, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(0.05) - player->dir.y * sin(0.05);
	player->dir.y = old_dir_x * sin(0.05) + player->dir.y * cos(0.05);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(0.05) - player->plane.y * sin(0.05);
	player->plane.y = old_plane_x * sin(0.05) + player->plane.y * cos(0.05);
}

void	add_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &move_keys, data);
}
