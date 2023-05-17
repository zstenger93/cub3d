/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:58:04 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/17 17:57:10 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_player(t_map *map)
{
	int	y;
	int	x;
	int	i;
	int	k;

	y = MINIMAP_SIZE / 2;
	x = MINIMAP_SIZE / 2;
	mlx_put_pixel(map->img_map, x, y - 4, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x, y - 3, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x, y - 2, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x - 2, y, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x - 3, y, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x - 4, y, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x, y, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x + 2, y, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x + 3, y, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x + 4, y, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x, y + 2, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x, y + 3, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x, y + 4, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x + 2, y + 2, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x - 2, y - 2, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x - 2, y + 2, rgb(0, 0, 0, map->op_max));
	mlx_put_pixel(map->img_map, x + 2, y - 2, rgb(0, 0, 0, map->op_max));
}

void	put_pixels_on_minimap(t_map *m, int i, int k, t_vector *p)
{
	if (m->matrix[(int)p->y + i][(int)p->x + k] == '1'
		|| (m->x % R == (int)m->player.pos.x - (int)m->player.pos.x * 10))
		mlx_put_pixel(m->img_map, m->x, m->y, rgb(230, 0, 0, m->op_mid));
	else if (m->matrix[(int)p->y + i][(int)p->x + k] == '0'
		|| (m->x % R == (int)m->player.pos.x - (int)m->player.pos.x * 10))
		mlx_put_pixel(m->img_map, m->x, m->y, rgb(145, 145, 145, m->op_mid));
	else if (m->matrix[(int)p->y + i][(int)p->x + k] == 'D'
		|| (m->x % R == (int)m->player.pos.x - (int)m->player.pos.x * 10))
		mlx_put_pixel(m->img_map, m->x, m->y, rgb(145, 0, 145, m->op_mid));
	else if (m->matrix[(int)p->y + i][(int)p->x + k] == 'K'
		|| (m->x % R == (int)m->player.pos.x - (int)m->player.pos.x * 10))
		mlx_put_pixel(m->img_map, m->x, m->y, rgb(145, 145, 145, m->op_mid));
	else
		mlx_put_pixel(m->img_map, m->x, m->y, rgb(160, 190, 150, m->op_mid));
}

void	draw_minimap(t_map *map, t_mlx_data *mlx_d, t_vector *p, int i)
{
	int	k;

	map->y = -1;
	while (++map->y < MINIMAP_SIZE)
	{
		k = ((MINIMAP_SIZE / R) / 2) * (-1);
		map->x = -1;
		while (++map->x < MINIMAP_SIZE)
		{
			put_pixels_on_minimap(map, i - 1, k - 1, p);
			if (map->x % R == 0)
				k++;
		}
		if ((map->y) % (R) == 0)
			i++;
	}
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
			(int)(MINIMAP_SIZE / 2 + x),
			(int)(MINIMAP_SIZE / 2 + y),
			rgb(0, 0, minimap->op_max, minimap->op_max));
		y += tmp_y;
		x += tmp_x;
		i++;
	}
}

int	get_pixel_color(t_map *map, mlx_texture_t *tex)
{
	return (rgb(tex->pixels[64 * (int)map->tex->tex.y * 4
				+ (int)map->tex->tex.x * 4], \
		tex->pixels[64 * (int)map->tex->tex.y * 4
				+ (int)map->tex->tex.x * 4 + 1], \
		tex->pixels[64 * (int)map->tex->tex.y * 4
				+ (int)map->tex->tex.x * 4 + 2], \
		tex->pixels[64 * (int)map->tex->tex.y * 4
				+ (int)map->tex->tex.x * 4 + 3]));
}
