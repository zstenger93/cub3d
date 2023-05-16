/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:27:14 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/16 16:08:46 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw(t_map *map, t_mlx_data *mlx_data, t_vector *p, int i)
{
	if (map->draw_minimap == true)
		visible_map(map, mlx_data, p, i);
	else
		invisible_map(map, mlx_data, p, i);
	draw_floor_and_ceiling(map);
	draw_map(map, mlx_data);
	if (map->has_key == false)
	{
		calculate_sprite_attributes(map, &map->sprite);
		draw_sprite(map, &map->sprite);
	}
	draw_buff(map->img_tmp, map->buffer);
}

void	visible_map(t_map *m, t_mlx_data *mlx_d, t_vector *p, int i)
{
	m->op_min = OP_ZERO;
	m->op_mid = OP_M;
	m->op_max = OPM;
	draw_minimap(m, mlx_d, p, i);
	draw_player(m);
	draw_rays(m);
}

void	invisible_map(t_map *m, t_mlx_data *mlx_d, t_vector *p, int i)
{
	m->op_min = OP_ZERO;
	m->op_mid = OP_ZERO;
	m->op_max = OP_ZERO;
	draw_minimap(m, mlx_d, p, i);
	draw_player(m);
	draw_rays(m);
}
