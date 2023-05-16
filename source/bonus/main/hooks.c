/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/16 18:12:27 by zstenger         ###   ########.fr       */
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
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		switch_door(data->minimap, data->mlx_data);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS
		&& data->minimap->draw_minimap == false)
		data->minimap->draw_minimap = true;
	else if (keydata.key == MLX_KEY_N && keydata.action == MLX_PRESS
		&& data->minimap->draw_minimap == true)
		data->minimap->draw_minimap = false;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_REPEAT
		&& data->minimap->player.speed_is_life == false)
	{
		data->minimap->player.speed_is_life = true;
		system("afplay ./resource/piu.mp3 &");
	}
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE
		&& data->minimap->player.speed_is_life == true)
		data->minimap->player.speed_is_life = false;
	steps(keydata, data);
}

void	steps(mlx_key_data_t keydata, t_data *data)
{
	static int	i;

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS
		|| keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS
		|| keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS
		|| keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS
		|| keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS
		|| keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		i++;
		if (i % 2 == 0)
			system("afplay ./resource/step1.mp3 &");
	}
}
