/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:58:04 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/08 18:53:23 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void    draw_map(t_map *map)
{
    int i;
    int hit;
	int k = -1;

	empty_map(map->img_tmp);
    i = -1;
    while (++i < WIDTH)
    {
		hit = 0;
		map->ray.camera.x = 2 * i / (double) WIDTH - 1;
		map->ray.dir.y = map->player.dir.y + map->player.plane.y * map->ray.camera.x;
		map->ray.dir.x = map->player.dir.x + map->player.plane.x * map->ray.camera.x;
		map->map_x = (int)map->player.pos.x;
		map->map_y = (int)map->player.pos.y;
		map->ray.delta_dist.y = fabs(1 / map->ray.dir.y);
		map->ray.delta_dist.x = fabs(1 / map->ray.dir.x);
		calculate_the_direction_of_the_ray(map, i);
		cast_the_ray_until_hits_the_wall(map, hit);
		print_vertical_lines(map, i);
		// while (++k < HEIGHT)
		// 	mlx_put_pixel(map->img_tmp, i, k, get_rgba(0, 85, 0, 255));
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

void	draw_minimap(t_map *minimap, t_mlx_data *mlx_data)
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
