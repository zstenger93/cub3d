/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:30:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/18 09:16:23 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	add_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &move_keys, data);
	mlx_loop_hook(data->mlx, &mouse_rotate, data);
}

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
