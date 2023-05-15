/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:27:14 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/15 15:16:59 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw(t_map *map, t_mlx_data *mlx_data, t_vector *p, int i)
{
	draw_minimap(map, mlx_data, p, i);
	draw_floor_and_ceiling(map);
	draw_map(map, mlx_data);
	if (map->has_key == false)
	{
		calculate_sprite_attributes(map, &map->sprite);
		draw_sprite(map, &map->sprite);
	}
	draw_buff(map->img_tmp, map->buffer);
	draw_player(map);
	draw_rays(map);
}
