/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:16:21 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/04 11:06:56 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player(t_minimap *minimap)
{
	int	y;
	int	x;
	int	i;
	int	k;

	y = (minimap->player.y * 20) + 8.5;
	x = (minimap->player.x * 20) + 8.5;
	i = 0;
	while (i < 5)
	{
		k = 0;
		while (k < 5)
		{
			mlx_put_pixel(minimap->map, x + k, y + i, get_rgba(0, 255, 0, 255));
			k++;
		}
		i++;
	}
}

void	draw_minimap(t_minimap *minimap)
{
	int	i;
	int	k;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		k = 0;
		while (k < MINIMAP_SIZE)
		{
			if (((k % 20 == 0 || i % 20 == 0) && minimap->matrix[i / MINIMAP_REC][k / MINIMAP_REC] == '1') || // DRAW WALL
			((k % 20 == 0 || i % 20 == 0) && minimap->matrix[(i - 1 )/ MINIMAP_REC][(k - 1) / MINIMAP_REC] == '1'))
				mlx_put_pixel(minimap->map, k, i, get_rgba(50, 50, 50, 255));
			else
				mlx_put_pixel(minimap->map, k, i, get_rgba(250, 50, 50, 255)); // DRAW REST
			k++;
		}
		i++;
	}
	draw_player(minimap);
}
