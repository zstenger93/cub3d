/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:58:04 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/09 08:23:39 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_player(t_map *minimap)
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

void	draw_minimap(t_map *minimap, t_mlx_data *mlx_data)
{
	t_vector	*p;
	int	i;
	int	k;
	int	pix_y;
	int	pix_x;

	p = &minimap->player.pos;
	
	i = ((MINIMAP_SIZE / MINIMAP_REC) / 2) * (-1);

	ft_print_2d_char_array(minimap->matrix);
	pix_y = -1;
	int t = 0;
	while (minimap->matrix[t] != NULL)
		t++;
	write2(t);
	write(1, " x ", 3);
	write2(ft_strlen(minimap->matrix[0]));

	while (++pix_y < MINIMAP_SIZE)
	{
		k = ((MINIMAP_SIZE / MINIMAP_REC) / 2) * (-1);
		pix_x = -1;
		while (++pix_x < MINIMAP_SIZE)
		{
			if (minimap->matrix[(int)p->y + i][(int)p->x + k] == '1'
				|| (pix_x % MINIMAP_REC == (int)minimap->player.pos.x - (int)minimap->player.pos.x * 10))
				// || ((int)((minimap->player.pos.y - (int)minimap->player.pos.y) * 10)))) ||
				// (pix_y % MINIMAP_REC == (int)((minimap->player.pos.y - (int)minimap->player.pos.y) * 10) && minimap->matrix[(int)p->y + i][(int)p->x + k] == '1')))
				// (minimap->matrix[(int)p->y + i][(int)p->x + k] == '1' && (pix_x % MINIMAP_REC == (int)((minimap->player.pos.x - (int)minimap->player.pos.x) * 10 || (int)((minimap->player.pos.y - (int)minimap->player.pos.y) * 10))))))
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(255, 0, 0, 255));
			else
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(160, 190, 150, 255)); // DRAW REST
			if ((pix_x) % (MINIMAP_REC) == 0)
				k++;
		}
		if ((pix_y) % (MINIMAP_REC) == 0)
			i++;
	}
	draw_map(minimap);
	draw_player(minimap);
	draw_rays(minimap);

}

void	draw_rays(t_map *minimap)
{
	int	i;
	double	y;
	double	x;

	double tmp_y = minimap->player.dir.y / 5;
	double tmp_x = minimap->player.dir.x / 5;
	y = minimap->player.dir.y;
	x = minimap->player.dir.x;
			
	i = 0;
	while (i < 40)
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
