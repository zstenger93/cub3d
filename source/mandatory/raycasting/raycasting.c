/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:15:19 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/09 10:20:30 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_map(t_map *map)
{
	int	i;
	int	hit;

	empty_map(map->img_tmp);
	i = -1;
	while (++i < WIDTH)
	{
		hit = 0;
		map->ray.camera.x = 2 * i / (double) WIDTH - 1;
		map->ray.dir.y = map->player.dir.y + map->player.plane.y * map->ray.camera.x;
		map->ray.dir.x = map->player.dir.x + map->player.plane.x * map->ray.camera.x;
		// map->ray.dir.y = sin(map->player.angle);
		// map->ray.dir.x = cos(map->player.angle);
		map->map_x = (int)map->player.pos.x;
		map->map_y = (int)map->player.pos.y;
		map->ray.delta_dist.y = fabs(1 / map->ray.dir.y);
		map->ray.delta_dist.x = fabs(1 / map->ray.dir.x);
		calculate_the_direction_of_the_ray(map, i);
		cast_the_ray_until_hits_the_wall(map, hit);
		print_vertical_lines(map, i);
	}
}

void	empty_map(mlx_image_t *img)
{
	int	i;
	int	k;

	i = -1;
	while (++i < HEIGHT)
	{
		k = -1;
		while (++k < WIDTH)
		{
			mlx_put_pixel(img, k, i, get_rgba(85, 85, 85, 255));
		}
	}
}

void	calculate_the_direction_of_the_ray(t_map *map, int i)
{
	if (map->ray.dir.y == 0)
		map->ray.delta_dist.y = 1e30;
	if (map->ray.dir.x == 0)
		map->ray.delta_dist.x = 1e30;
	if (map->ray.dir.y < 0)
	{
		map->step.x = -1;
		map->ray.side_dist.x = (map->player.pos.x - map->map_x) * map->ray.delta_dist.x;
	}
	else
	{
		map->step.x = 1;
		map->ray.side_dist.x = (map->map_x + 1.0 - map->player.pos.x) * map->ray.delta_dist.x;
	}
	if (map->ray.dir.x < 0)
	{
		map->step.y = -1;
		map->ray.side_dist.y = (map->player.pos.y - map->map_y) * map->ray.delta_dist.y;
	}
	else
	{
		map->step.y = 1;
		map->ray.side_dist.y = (map->map_y + 1.0 - map->player.pos.y) * map->ray.delta_dist.y;
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
		if (map->matrix[(int)map->map_x][(int)map->map_y] > '0')
			hit = 1;
	}
	if (map->side == 0)
		map->ray.wall_dist = map->ray.side_dist.x - map->ray.delta_dist.x;
	else
		map->ray.wall_dist = map->ray.side_dist.y - map->ray.delta_dist.y;
}

void	print_vertical_lines(t_map *map, int i)
{
	int line_height;
	int draw_start;
	int	draw_end;

	line_height = (int)(HEIGHT / map->ray.wall_dist);
	draw_start = - line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if(draw_start < 0)
		draw_start = 0;
	if(draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	while (draw_start < draw_end)
	{
		if (map->side == 0)
			mlx_put_pixel(map->img_tmp, i, draw_start, get_rgba(0, 0, 255, 255));
		else
			mlx_put_pixel(map->img_tmp, i, draw_start, get_rgba(0, 255, 0, 255));
		draw_start++;
	}
}
