/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:16:21 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/04 14:26:35 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player(t_minimap *minimap)
{
	int	y;
	int	x;
	int	i;
	int	k;
	
	y = (minimap->player.y * 20);
	x = (minimap->player.x * 20);
	i = -3;
	while (++i < 3)
	{
		k = -3;
		while (++k < 3)
			mlx_put_pixel(minimap->map, x + k, y + i, get_rgba(0, 255, 0, 255));
	}
}

void	draw_minimap(t_minimap *minimap)
{
	int	i;
	int	k;

	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		k = -1;
		while (++k < MINIMAP_SIZE)
		{
			if (((k % 20 == 0 || i % 20 == 0) && minimap->matrix[i / MINIMAP_REC][k / MINIMAP_REC] == '1') || // DRAW WALL
			((k % 20 == 0 || i % 20 == 0) && minimap->matrix[(i - 1 )/ MINIMAP_REC][(k - 1) / MINIMAP_REC] == '1'))
				mlx_put_pixel(minimap->map, k, i, get_rgba(50, 50, 50, 255));
			else
				mlx_put_pixel(minimap->map, k, i, get_rgba(250, 50, 50, 255)); // DRAW REST
		}
	}
	draw_player(minimap);
}
