/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/15 15:15:18 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
	int			y;
	static int	last_m_x;

	data = (t_data *)param;
	last_m_x = data->mouse_x;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(data->mlx, &data->mouse_x, &y);
	if (data->mouse_x > last_m_x)
		turn_right(data, player);
	else if (data->mouse_x < last_m_x)
		turn_left(data, player);
	if (data->mouse_x > 2555)
		data->mouse_x = 5;
	else if (data->mouse_x < 5)
		data->mouse_x = 2555;
}

void	hodor(mlx_key_data_t keydata, void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS
		&& data->minimap->has_key == true)
		switch_door(data->minimap, data->mlx_data);
}
