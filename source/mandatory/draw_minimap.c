/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:16:21 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/06 10:39:55 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player(t_minimap *minimap)
{
	int	y;
	int	x;
	int	i;
	int	k;

	y = 80;
	x = 80;
	i = -3;
	while (++i < 3)
	{
		k = -3;
		while (++k < 3)
			mlx_put_pixel(minimap->img_map, x + k, y + i, get_rgba(0, 255, 0, 255));
	}
}

void	draw_minimap(t_minimap *minimap, t_mlx_data *mlx_data)
{
	int	i;
	int	k;
	int	pix_y;
	int	pix_x;

	// i = get_printing_position_y(minimap->matrix, minimap->player.pos.y, mlx_data->map_length);

	pix_y = -1;
	while (++pix_y < MINIMAP_SIZE)
	{
		// k = get_printing_position_x(minimap->matrix, minimap->player.pos.y, minimap->player.pos.x);
		pix_x = -1;
		while (++pix_x < MINIMAP_SIZE)
		{
			if (pix_x % 20 == 0)
				k++;
			if (((pix_y % 20 == 0 || pix_x % 20 == 0) && minimap->matrix[i][k] == '1') || // DRAW WALL
			((pix_y % 20 == 0 || pix_x % 20 == 0) && minimap->matrix[i - 1][k - 1] == '1'))
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(50, 50, 50, 255));
			else
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(50, 150, 150, 255)); // DRAW REST
		}
		if (pix_y % 20 == 0)
			++i;
	}
	draw_player(minimap);
}
