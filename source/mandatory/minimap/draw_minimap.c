/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:58:04 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/10 18:42:48 by zstenger         ###   ########.fr       */
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
	mlx_put_pixel(minimap->img_map, x, y - 4, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y - 3, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y - 2, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x - 2, y, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x - 3, y, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x - 4, y, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x + 2, y, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x + 3, y, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x + 4, y, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y + 2, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y + 3, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x, y + 4, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x + 2, y + 2, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x - 2, y - 2, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x - 2, y + 2, rgb(0, 0, 0, 255));
	mlx_put_pixel(minimap->img_map, x + 2, y - 2, rgb(0, 0, 0, 255));
}

void	draw_minimap(t_map *m, t_mlx_data *mlx_d, t_vector *p, int i)
{
	int			k;
	int			y;
	int			x;

	y = -1;
	while (++y < MINIMAP_SIZE)
	{
		k = ((MINIMAP_SIZE / R) / 2) * (-1);
		x = -1;
		while (++x < MINIMAP_SIZE)
		{
			if (m->matrix[(int)p->y + i][(int)p->x + k] == '1'
				|| (x % R == (int)m->player.pos.x - (int)m->player.pos.x * 10))
				mlx_put_pixel(m->img_map, x, y, rgb(255, 0, 0, 255));
			else if (m->matrix[(int)p->y + i][(int)p->x + k] == '0'
				|| (x % R == (int)m->player.pos.x - (int)m->player.pos.x * 10))
				mlx_put_pixel(m->img_map, x, y, rgb(145, 145, 145, 255));
			else
				mlx_put_pixel(m->img_map, x, y, rgb(160, 190, 150, 255));
			if (x % R == 0)
				k++;
		}
		if ((y) % (R) == 0)
			i++;
	}
}

void	draw(t_map *map, t_mlx_data *mlx_data)
{
	draw_map(map, mlx_data);
	draw_player(map);
	draw_rays(map);
}

void	draw_rays(t_map *minimap)
{
	int		i;
	double	y;
	double	x;
	double	tmp_y;
	double	tmp_x;

	tmp_y = minimap->player.dir.y / 5;
	tmp_x = minimap->player.dir.x / 5;
	y = minimap->player.dir.y;
	x = minimap->player.dir.x;
	i = 0;
	while (i < 80)
	{
		mlx_put_pixel(minimap->img_map,
			MINIMAP_SIZE / 2 + x,
			MINIMAP_SIZE / 2 + y,
			rgb(0, 0, 255, 255));
		y += tmp_y;
		x += tmp_x;
		i++;
	}
}
