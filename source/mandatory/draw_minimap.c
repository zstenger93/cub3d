/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:58:04 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/08 08:38:03 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player(t_minimap *minimap) // change
{
	int	y;
	int	x;
	int	i;
	int	k;

	y = MINIMAP_SIZE / 2;
	x = MINIMAP_SIZE / 2;
	
	mlx_put_pixel(minimap->img_map, x, y - 2, get_rgba(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y - 1, get_rgba(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x - 1, y, get_rgba(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x - 2, y, get_rgba(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y, get_rgba(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x + 1, y, get_rgba(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x + 2, y, get_rgba(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y + 1, get_rgba(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y + 2, get_rgba(0, 0, 0, 255));
	// i = -3;
	// while (++i < 3)
	// {
	// 	k = -3;
	// 	while (++k < 3)
	// 		mlx_put_pixel(minimap->img_map, x + k, y + i, get_rgba(0, 0, 0, 255));
	// }
}

void	draw_rays(t_minimap *minimap)
{
	int	i;
	double	y;
	double	x;

	double tmp_y = minimap->player.dir.y / 5;
	double tmp_x = minimap->player.dir.x / 5;
	y = minimap->player.dir.y;
	x = minimap->player.dir.x;
			
	i = 0;
	while (i < 15)
	{
		mlx_put_pixel(minimap->img_map, 
		MINIMAP_SIZE / 2 + x,
		MINIMAP_SIZE / 2 + y, 
		get_rgba(0, 0, 255, 255));
		y += tmp_y;
		x += tmp_x;
		i++;
	}
	
}


void	draw_minimap(t_minimap *minimap, t_mlx_data *mlx_data)
{
	t_vector	*p;
	int	i;
	int	k;
	int	pix_y;
	int	pix_x;

	p = &minimap->player.pos;
	i = ((MINIMAP_SIZE / MINIMAP_REC) / 2) * (-1);
	pix_y = -1;
	while (++pix_y < MINIMAP_SIZE)
	{
		k = ((MINIMAP_SIZE / MINIMAP_REC) / 2) * (-1);
		pix_x = -1;
		while (++pix_x < MINIMAP_SIZE)
		{
			if (minimap->matrix[(int)p->y + i][(int)p->x + k] == '1')
				// && (pix_x % MINIMAP_REC == (int)((p->x - (int)p->x) * 10)
				// || pix_y % MINIMAP_REC == (int)((p->y - (int)p->y) * 10))
				// || (pix_x - 1) % MINIMAP_REC == (int)((p->x - (int)p->x) * 10)
				// || (pix_y - 1) % MINIMAP_REC == (int)((p->y - (int)p->y) * 10))
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(250, 50, 50, 255));
			else
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(160, 190, 150, 255)); // DRAW REST
			if ((pix_x) % 20 == 0)
				k++;
		}
		if ((pix_y) % 20 == 0)
			i++;

	}
	draw_player(minimap);
	draw_rays(minimap);
}
// void	draw_minimap(t_minimap *minimap, t_mlx_data *mlx_data)
// {
// 	int	i;
// 	int	k;
// 	int	pix_y;
// 	int	pix_x;

// 	pix_y = -1;
// 	// i = (MINIMAP_SIZE / MINIMAP_REC) / 2 - minimap->player.pos.y;
// 	i = (int)((minimap->player.pos.y - (int)minimap->player.pos.y) * 10);
// 	while (++pix_y < MINIMAP_SIZE)
// 	{
// 		// k =(MINIMAP_SIZE / MINIMAP_REC) / 2 - minimap->player.pos.x;
// 		k = (int)((minimap->player.pos.x - (int)minimap->player.pos.x) * 10);
// 		pix_x = -1;
// 		while (++pix_x < MINIMAP_SIZE)
// 		{
// 			if (((pix_x % MINIMAP_REC == k || pix_y % MINIMAP_REC == i ) && minimap->matrix[(int)minimap->player.pos.y + (pix_y % 20) - 5][(int)minimap->player.pos.x + (pix_x % 20) - 5] == '1') ||// DRAW WALL
// 				(((pix_x + 1) % MINIMAP_REC == k || (pix_y + 1) % MINIMAP_REC == i ) && minimap->matrix[(int)minimap->player.pos.y - (pix_y % 20) - 5][(int)minimap->player.pos.x - (pix_x % 20) - 5] == '1'))
// 				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(250, 50, 50, 255));
// 			else
// 				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(160, 190, 150, 255)); // DRAW REST
// 			if (pix_x % MINIMAP_REC == 0)
// 				k++;
// 		}
// 		if (pix_y % MINIMAP_REC == 0)
// 			++i;
// 	}
// 	draw_player(minimap);
// 	// draw_rays(minimap);
// }
