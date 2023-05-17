/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:15:19 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/17 12:04:14 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_rays_on_minimap(t_map *map)
{
	double	distance_x;
	double	distance_y;
	double	distance_delta;
	double	delta_x;
	double	delta_y;

	if (map->matrix[(int)map->map_y][(int)map->map_x] > '0'
			&& map->matrix[(int)map->map_y][(int)map->map_x] != 'd'
			&& map->matrix[(int)map->map_y][(int)map->map_x] != 'K')
	{
		distance_y = map->map_y;
		distance_x = map->map_x;
	printf("%f:%f\n", distance_y, distance_x);

	}
	else
		return ;
	


	delta_x = fabs(map->player.pos.x + distance_x);
	delta_y = fabs(map->player.pos.y + distance_y);

	distance_delta = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	
	distance_x /= distance_delta;
	distance_y /= distance_delta;

	// printf("%f:    %f x %f\n", distance_delta, MINIMAP_SIZE / 2 + distance_y * 20, MINIMAP_SIZE / 2 + distance_x * 20);
	// while (distance_x > 0.0 &&  distance_y > 0.0 && distance_delta > 0.0)
	while (distance_delta > 0.0)
	{
		// if (MINIMAP_SIZE < MINIMAP_SIZE / 2 + distance_x * 20
		// 	&& MINIMAP_SIZE < MINIMAP_SIZE / 2 + distance_y * 20)
			mlx_put_pixel(map->img_map, 
					MINIMAP_SIZE / 2 - (distance_x + distance_delta) * 2,
					MINIMAP_SIZE / 2 - (distance_y + distance_delta) * 2, 
					rgb(0, 200, 0, map->op_max));
		distance_delta -= 0.05;


		
		// distance_x -= 0.05;
		// distance_y -= 0.05;
	}
}

// void	draw_rays_on_minimap(t_map *map)
// {
// 	double	pix_x;
// 	double	pix_y;
// 	double	pix1_x;
// 	double	pix1_y;
// 	double	delta_x;
// 	double	delta_y;
// 	double	len;

// 	pix_x = MINIMAP_SIZE/2;
// 	pix_y = MINIMAP_SIZE/2;
// 	pix1_x = (MINIMAP_SIZE/2 + ((int)map->player.pos.x - (int)map->ray.side_dist.x)) * 20 - 30;
// 	pix1_y = (MINIMAP_SIZE/2 + ((int)map->player.pos.y - (int)map->ray.side_dist.y)) * 20 - 30;
// 	delta_x = pix1_x - pix_x;
// 	delta_y = pix1_y - pix_y;
// 	len = sqrt(pow(delta_x, 2) - pow(delta_y, 2));
// 	delta_x /= len;
// 	delta_y /= len;

// 	while (len > 0)
// 	{
// 		if (pix_x < MINIMAP_SIZE && pix_y < MINIMAP_SIZE
// 			&& pix_x > 0 && pix_y > 0)
// 		{
// 			// printf("%f:%f\n", pix_y, pix_x);
// 			mlx_put_pixel(map->img_map, pix_x, pix_y, rgb(0, 200, 0, map->op_max));
// 		}
// 		pix_x += delta_x;
// 		pix_y += delta_y;
// 		len--;
// 	}	
// }

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
		draw_rays_on_minimap(m);
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
		if (map->matrix[(int)map->map_y][(int)map->map_x] > '0'
			&& map->matrix[(int)map->map_y][(int)map->map_x] != 'd'
			&& map->matrix[(int)map->map_y][(int)map->map_x] != 'K')
			hit = 1;
	}
	if (map->side == 0)
		map->ray.wall_dist = map->ray.side_dist.x - map->ray.delta_dist.x;
	else
		map->ray.wall_dist = map->ray.side_dist.y - map->ray.delta_dist.y;
	if (map->ray.wall_dist < 1e-4)
		map->ray.wall_dist = 0.4;
}
