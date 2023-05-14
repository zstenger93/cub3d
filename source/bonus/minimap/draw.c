/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:27:14 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/14 14:27:56 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw(t_map *map, t_mlx_data *mlx_data, t_vector *p, int i)
{
	draw_minimap(map, mlx_data, p, i);
	draw_map(map, mlx_data);
	draw_player(map);
	draw_rays(map);
}
