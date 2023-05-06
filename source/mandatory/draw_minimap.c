/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:58:04 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/06 15:12:39 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player(t_minimap *minimap)
{
	int	y;
	int	x;
	int	i;
	int	k;

	y = MINIMAP_SIZE / 2;
	x = MINIMAP_SIZE / 2;
	i = -3;
	while (++i < 3)
	{
		k = -3;
		while (++k < 3)
			mlx_put_pixel(minimap->img_map, x + k, y + i, get_rgba(0, 0, 0, 255));
	}
}

void	draw_minimap(t_minimap *minimap, t_mlx_data *mlx_data)
{
	int	i;
	int	k;
	int	pix_y;
	int	pix_x;

	pix_y = -1;
	i = minimap->player.pos.y - (MINIMAP_SIZE / MINIMAP_REC) / 2;
	while (++pix_y < MINIMAP_SIZE)
	{
		k = minimap->player.pos.x - (MINIMAP_SIZE / MINIMAP_REC) / 2;
		pix_x = -1;
		while (++pix_x < MINIMAP_SIZE)
		{
			if (((pix_y % MINIMAP_REC == 0 || pix_x % MINIMAP_REC == 0) && minimap->matrix[i][k] == '1') || // DRAW WALL
			(((pix_y - 1) % MINIMAP_REC == 0 || (pix_x - 1) % MINIMAP_REC == 0) && minimap->matrix[i][k] == '1'))
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(250, 50, 50, 255));
			else
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(160, 190, 150, 255)); // DRAW REST
			if (pix_x % MINIMAP_REC == 0)
				k++;
		}
		if (pix_y % MINIMAP_REC == 0)
			++i;
	}
	draw_player(minimap);
}
