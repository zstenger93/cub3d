/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:15:19 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/10 14:39:22 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_map(t_map *m, t_mlx_data *mlx_data)
{
	int	i;
	int	hit;

	empty_map(m->img_tmp, mlx_data);
	i = -1;
	while (++i < WIDTH)
	{
		hit = 0;
		m->ray.camera.x = 2 * i / (double) WIDTH - 1;
		m->ray.dir.y = m->player.dir.y + m->player.plane.y * m->ray.camera.x;
		m->ray.dir.x = m->player.dir.x + m->player.plane.x * m->ray.camera.x;
		m->map_x = (int)m->player.pos.x;
		m->map_y = (int)m->player.pos.y;
		m->ray.delta_dist.y = fabs(1 / m->ray.dir.y);
		m->ray.delta_dist.x = fabs(1 / m->ray.dir.x);
		calculate_the_direction_of_the_ray(m, i);
		cast_the_ray_until_hits_the_wall(m, hit);
		print_vertical_lines(m, i);
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
			mlx_put_pixel(img, k, i, get_rgba(mlx_d->ceiling_color[0],
					mlx_d->ceiling_color[1], mlx_d->ceiling_color[2], 255));
	}
	while (++i < HEIGHT)
	{
		k = -1;
		while (++k < WIDTH)
			mlx_put_pixel(img, k, i, get_rgba(mlx_d->floor_color[0],
					mlx_d->floor_color[1], mlx_d->floor_color[2], 255));
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
	while (hit == 0)
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
		if (map->matrix[(int)map->map_y][(int)map->map_x] > '0')
			hit = 1;
	}
	if (map->side == 0)
		map->ray.wall_dist = map->ray.side_dist.x - map->ray.delta_dist.x;
	else
		map->ray.wall_dist = map->ray.side_dist.y - map->ray.delta_dist.y;
	if (map->ray.wall_dist < 1e-4)
		map->ray.wall_dist = 0.4;
}

void	print_vertical_lines(t_map *m, int i)
{
	int line_height;
	int draw_start;
	int	draw_end;

	line_height = (int)(HEIGHT / m->ray.wall_dist);
	draw_start = - line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if(draw_start < 0)
		draw_start = 0;
	if(draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	while (draw_start < draw_end)
	{
		if (m->side == 0)
			mlx_put_pixel(m->img_tmp, i, draw_start, get_rgba(0, 0, 255, 255));
		else
			mlx_put_pixel(m->img_tmp, i, draw_start, get_rgba(0, 255, 0, 255));
		draw_start++;
	}
}
