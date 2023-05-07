/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:58:04 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/07 11:09:40 by jergashe         ###   ########.fr       */
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

void	draw_rays(t_minimap *minimap)
{

	int	i;
	int	k;
	int	hit;
	int	side;
	t_vector	map;

	i = -1;
	while (++i < WIDTH)
	{
		
		
	hit = 0;
	map.x = (int)minimap->player.pos.x;
	map.y = (int)minimap->player.pos.y;

	minimap->ray.camera.x = 2 * i / (double) WIDTH - 1;
	minimap->ray.dir.y = minimap->player.dir.y + minimap->player.plane.y * minimap->ray.camera.x;
	minimap->ray.dir.x = minimap->player.dir.x + minimap->player.plane.x * minimap->ray.camera.x;
	minimap->ray.delta_dist.y = fabs(1 / minimap->ray.dir.y);
	minimap->ray.delta_dist.x = fabs(1 / minimap->ray.dir.x);
	if (minimap->ray.dir.y == 0)
		minimap->ray.delta_dist.y = 1e30;
	if (minimap->ray.dir.x == 0)
		minimap->ray.delta_dist.x = 1e30;
	double	step_x; // del
	double	step_y; // del
	if (minimap->ray.dir.x < 0)
	{
		step_x = -1;
		minimap->ray.side_dist.x = (minimap->player.pos.x - map.x) * minimap->ray.delta_dist.x;
	}
	else
	{
		step_x = 1;
		minimap->ray.side_dist.x = (map.x + 1.0 - minimap->player.pos.x) * minimap->ray.delta_dist.x;
	}
	if (minimap->ray.dir.y < 0)
	{
		step_y = -1;
		minimap->ray.side_dist.y = (minimap->player.pos.y - map.y) * minimap->ray.delta_dist.y;
	}
	else
	{
		step_y = 1;
		minimap->ray.side_dist.y = (map.y + 1.0 - minimap->player.pos.y) * minimap->ray.delta_dist.y;
	}
	
	while (hit == 0)
	{
		if (minimap->ray.side_dist.x < minimap->ray.side_dist.y)
		{
			minimap->ray.side_dist.x += minimap->ray.delta_dist.x;
			map.x += step_x;
			side = 0;
		}
		else
		{
			minimap->ray.side_dist.y += minimap->ray.delta_dist.y;
			map.y += step_y;
			side = 1;
		}
		if (minimap->matrix[(int)map.y][(int)map.x] < 1)
			hit = 1;
	}
	
	if (side == 0)
		minimap->ray.wall_dist = minimap->ray.side_dist.x - minimap->ray.delta_dist.x;
	else
		minimap->ray.wall_dist = minimap->ray.side_dist.y - minimap->ray.delta_dist.y;
	
	
	int lineHeight = (HEIGHT / (minimap->ray.wall_dist + 1));
	int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if(drawStart < 0) drawStart = 0;
    // int drawEnd = HEIGHT - 1;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
	
	write2(lineHeight);
	write2(drawStart);
	write2(drawEnd);
	write(1, "\n", 1);
	while (drawStart < drawEnd && drawStart < HEIGHT - 1)
	{

		// write(2, "\n",2);
		mlx_put_pixel(minimap->img_tmp, drawStart, i, get_rgba(0, 255, 255, 255));
		drawStart++;
	}
	}
}

// void	draw_rays(t_minimap *minimap)
// {
// 	int	i;
// 	int	k;
// 	int	hit;
// 	int	side;
// 	t_vector	map;

// 	i = -1;
// 	while (++i < MINIMAP_SIZE)
// 	{
		
		
// 	hit = 0;
// 	map.x = (int)minimap->player.pos.x;
// 	map.y = (int)minimap->player.pos.y;

// 	minimap->ray.camera.x = 2 * i / (double) MINIMAP_SIZE - 1;
// 	minimap->ray.dir.y = minimap->player.dir.y + minimap->player.plane.y * minimap->ray.camera.x;
// 	minimap->ray.dir.x = minimap->player.dir.x + minimap->player.plane.x * minimap->ray.camera.x;
// 	minimap->ray.delta_dist.y = fabs(1 / minimap->ray.dir.y);
// 	minimap->ray.delta_dist.x = fabs(1 / minimap->ray.dir.x);
// 	if (minimap->ray.dir.y == 0)
// 		minimap->ray.delta_dist.y = 1e30;
// 	if (minimap->ray.dir.x == 0)
// 		minimap->ray.delta_dist.x = 1e30;
// 	double	step_x; // del
// 	double	step_y; // del
// 	if (minimap->ray.dir.x < 0)
// 	{
// 		step_x = -1;
// 		minimap->ray.side_dist.x = (minimap->player.pos.x - map.x) * minimap->ray.delta_dist.x;
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		minimap->ray.side_dist.x = (map.x + 1.0 - minimap->player.pos.x) * minimap->ray.delta_dist.x;
// 	}
// 	if (minimap->ray.dir.y < 0)
// 	{
// 		step_y = -1;
// 		minimap->ray.side_dist.y = (minimap->player.pos.y - map.y) * minimap->ray.delta_dist.y;
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		minimap->ray.side_dist.y = (map.y + 1.0 - minimap->player.pos.y) * minimap->ray.delta_dist.y;
// 	}
	
// 	while (hit == 0)
// 	{
// 		if (minimap->ray.side_dist.x < minimap->ray.side_dist.y)
// 		{
// 			minimap->ray.side_dist.x += minimap->ray.delta_dist.x;
// 			map.x += step_x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			minimap->ray.side_dist.y += minimap->ray.delta_dist.y;
// 			map.y += step_y;
// 			side = 1;
// 		}
// 		if (minimap->matrix[(int)map.x][(int)map.y] > 0)
// 			hit = 1;
// 	}
	
// 	if (side == 0)
// 		minimap->ray.wall_dist = minimap->ray.side_dist.x - minimap->ray.delta_dist.x;
// 	else
// 		minimap->ray.wall_dist = minimap->ray.side_dist.y - minimap->ray.delta_dist.y;
	
	
// 	int lineHeight = (int)(MINIMAP_SIZE / minimap->ray.wall_dist);
// 	int drawStart = - lineHeight / 2 + MINIMAP_SIZE / 2;
//     if(drawStart < 0) drawStart = 0;
//     int drawEnd = lineHeight / 2 + MINIMAP_SIZE / 2;
//     if(drawEnd >= MINIMAP_SIZE) drawEnd = MINIMAP_SIZE - 1;
// 	while (drawStart < drawEnd)
// 	{
// 		mlx_put_pixel(minimap->img_tmp, drawStart, i, get_rgba(0, 255, 255, 255));
// 		drawStart++;
// 	}
// 	write(2, "W\n",2);
// 	}
// }

void	draw_minimap(t_minimap *minimap, t_mlx_data *mlx_data)
{
	// int	i;
	// int	k;
	// int	pix_y;
	// int	pix_x;

	// pix_y = -1;
	// i = minimap->player.pos.y - (MINIMAP_SIZE / MINIMAP_REC) / 2;
	// while (++pix_y < MINIMAP_SIZE)
	// {
	// 	k = minimap->player.pos.x - (MINIMAP_SIZE / MINIMAP_REC) / 2;
	// 	pix_x = -1;
	// 	while (++pix_x < MINIMAP_SIZE)
	// 	{
	// 		if (((pix_y % MINIMAP_REC == 0 || pix_x % MINIMAP_REC == 0) && minimap->matrix[i][k] == '1') || // DRAW WALL
	// 		(((pix_y - 1) % MINIMAP_REC == 0 || (pix_x - 1) % MINIMAP_REC == 0) && minimap->matrix[i][k] == '1'))
	// 			mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(250, 50, 50, 255));
	// 		else
	// 			mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(160, 190, 150, 255)); // DRAW REST
	// 		if (pix_x % MINIMAP_REC == 0)
	// 			k++;
	// 	}
	// 	if (pix_y % MINIMAP_REC == 0)
	// 		++i;
	// }
	// draw_player(minimap);
	draw_rays(minimap);
}
