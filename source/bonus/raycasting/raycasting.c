/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:15:19 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/18 08:18:01 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

	// empty_map(m->img_tmp, mlx_data);
		// print_vertical_lines(m, i);
void	draw_map(t_map *m, t_mlx_data *mlx_data)
{
	int	i;

	i = -1;
	while (++i < WIDTH)
	{
		m->hit = 0;
		m->ray.camera.x = ((2 * i) / (double)WIDTH) - 1;
		m->ray.dir.y = m->player.dir.y + m->player.plane.y * m->ray.camera.x;
		m->ray.dir.x = m->player.dir.x + m->player.plane.x * m->ray.camera.x;
		m->map_x = (int)m->player.pos.x;
		m->map_y = (int)m->player.pos.y;
		if (m->ray.delta_dist.x == 0)
			m->ray.delta_dist.x = DBL_MAX;
		else
			m->ray.delta_dist.x = fabs(1 / m->ray.dir.x);
		if (m->ray.delta_dist.y == 0)
			m->ray.delta_dist.y = DBL_MAX;
		else
			m->ray.delta_dist.y = fabs(1 / m->ray.dir.y);
		calculate_the_direction_of_the_ray(m, i);
		cast_the_ray_until_hits_the_wall(m, m->hit);
		print_textures(m, i, mlx_data);
	}
}

void	empty_map(mlx_image_t *img, t_mlx_data *mlx_d)
{
	int	i;
	int	k;

	i = -1;
	while (++i < HEIGHT / 2)
	{
		k = -1;
		while (++k < WIDTH)
			mlx_put_pixel(img, k, i, rgb(mlx_d->c_color[0],
					mlx_d->c_color[1], mlx_d->c_color[2], 255));
	}
	while (++i < HEIGHT)
	{
		k = -1;
		while (++k < WIDTH)
			mlx_put_pixel(img, k, i, rgb(mlx_d->f_color[0],
					mlx_d->f_color[1], mlx_d->f_color[2], 255));
	}
}

void	set_ray_distance(t_map *map)
{
	if (map->ray.dir.y == 0)
		map->ray.delta_dist.y = 1e30;
	if (map->ray.dir.x == 0)
		map->ray.delta_dist.x = 1e30;
}

void	calculate_the_direction_of_the_ray(t_map *map, int i)
{
	set_ray_distance(map);
	if (map->ray.dir.x < 0)
	{
		map->step.x = -1;
		map->ray.side_dist.x = (map->player.pos.x - map->map_x)
			* map->ray.delta_dist.x;
	}
	else
	{
		map->step.x = 1;
		map->ray.side_dist.x = (map->map_x + 1.0 - map->player.pos.x)
			* map->ray.delta_dist.x;
	}
	if (map->ray.dir.y < 0)
	{
		map->step.y = -1;
		map->ray.side_dist.y = (map->player.pos.y - map->map_y)
			* map->ray.delta_dist.y;
	}
	else
	{
		map->step.y = 1;
		map->ray.side_dist.y = (map->map_y + 1.0 - map->player.pos.y)
			* map->ray.delta_dist.y;
	}
}

void	cast_the_ray_until_hits_the_wall(t_map *map, int hit)
{
	while (map->hit == 0)
	{
		if (map->ray.side_dist.x < map->ray.side_dist.y)
		{
			map->ray.side_dist.x += map->ray.delta_dist.x;
			map->map_x += map->step.x;
			map->side = 0;
		}
		else
		{
			map->ray.side_dist.y += map->ray.delta_dist.y;
			map->map_y += map->step.y;
			map->side = 1;
		}
		if (map->matrix[(int)map->map_y][(int)map->map_x] > '0'
			&& map->matrix[(int)map->map_y][(int)map->map_x] != 'd'
			&& map->matrix[(int)map->map_y][(int)map->map_x] != 'K')
			map->hit = 1;
	}
	if (map->side == 0)
		map->ray.wall_dist = map->ray.side_dist.x - map->ray.delta_dist.x;
	else
		map->ray.wall_dist = map->ray.side_dist.y - map->ray.delta_dist.y;
	if (map->ray.wall_dist < 1e-4)
		map->ray.wall_dist = 0.4;
}
