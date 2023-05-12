/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/12 19:21:21 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	add_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &move_keys, data);
	mlx_loop_hook(data->mlx, &mouse_rotate, data);
	mlx_key_hook(data->mlx, &hodor, data);
}

	// float distance = m_x - last_m_x;
	// float time = 0.016f;
	// float speed = distance / time;
	// m_x = (float)data->mouse_x;
	// float		m_x;
void	mouse_rotate(void *param)
{
	t_data		*data;
	t_player	*player;
	int			x;
	int			y;
	float		last_m_x;

	data = (t_data *)param;
	x = data->mouse_x;
	last_m_x = data->mouse_x;
	mlx_get_mouse_pos(data->mlx, &data->mouse_x, &y);
	if (data->mouse_x > x)
		turn_right(data, player);
	else if (data->mouse_x < x)
		turn_left(data, player);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
}

void	switch_door(t_map *map, t_mlx_data *mlx_data)
{
	if (is_closed_door_here(map) == true)
	{
		mlx_delete_texture(mlx_data->door);
		mlx_data->door = mlx_load_png("resource/transparent.png");
	}
	else if (is_open_door_here(map) == true)
	{
		mlx_delete_texture(mlx_data->door);
		mlx_data->door = mlx_load_png("resource/vortex1.png");
	}
}

bool	is_closed_door_here(t_map *m)
{
	if (m->matrix[(int)m->map_y][(int)m->map_x] == 'D')
		return (m->matrix[(int)m->map_y][(int)m->map_x] = 'd', true);
	else if (m->matrix[(int)m->map_y + 1][(int)m->map_x + 1] == 'D')
		return (m->matrix[(int)m->map_y + 1][(int)m->map_x + 1] = 'd', true);
	else if (m->matrix[(int)m->map_y][(int)m->map_x + 1] == 'D')
		return (m->matrix[(int)m->map_y][(int)m->map_x + 1] = 'd', true);
	else if (m->matrix[(int)m->map_y + 1][(int)m->map_x] == 'D')
		return (m->matrix[(int)m->map_y + 1][(int)m->map_x] = 'd', true);
	else if (m->matrix[(int)m->map_y][(int)m->map_x - 1] == 'D')
		return (m->matrix[(int)m->map_y][(int)m->map_x - 1] = 'd', true);
	else if (m->matrix[(int)m->map_y - 1][(int)m->map_x] == 'D')
		return (m->matrix[(int)m->map_y - 1][(int)m->map_x] = 'd', true);
	else if (m->matrix[(int)m->map_y - 1][(int)m->map_x - 1] == 'D')
		return (m->matrix[(int)m->map_y - 1][(int)m->map_x - 1] = 'd', true);
	return (false);
}

bool	is_open_door_here(t_map *m)
{
	if (m->matrix[(int)m->map_y][(int)m->map_x] == 'd')
		return (m->matrix[(int)m->map_y][(int)m->map_x] = 'D', true);
	else if (m->matrix[(int)m->map_y + 1][(int)m->map_x + 1] == 'd')
		return (m->matrix[(int)m->map_y + 1][(int)m->map_x + 1] = 'D', true);
	else if (m->matrix[(int)m->map_y][(int)m->map_x + 1] == 'd')
		return (m->matrix[(int)m->map_y][(int)m->map_x + 1] = 'D', true);
	else if (m->matrix[(int)m->map_y + 1][(int)m->map_x] == 'd')
		return (m->matrix[(int)m->map_y + 1][(int)m->map_x] = 'D', true);
	else if (m->matrix[(int)m->map_y][(int)m->map_x - 1] == 'd')
		return (m->matrix[(int)m->map_y][(int)m->map_x - 1] = 'D', true);
	else if (m->matrix[(int)m->map_y - 1][(int)m->map_x] == 'd')
		return (m->matrix[(int)m->map_y - 1][(int)m->map_x] = 'D', true);
	else if (m->matrix[(int)m->map_y - 1][(int)m->map_x - 1] == 'd')
		return (m->matrix[(int)m->map_y - 1][(int)m->map_x - 1] = 'D', true);
	return (false);
}

void	hodor(mlx_key_data_t keydata, void *param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		switch_door(data->minimap, data->mlx_data);
}
