/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:58:04 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/08 12:03:03 by zstenger         ###   ########.fr       */
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

void    draw_map(t_minimap *minimap)
{
    int i;
    int k;
    int map_x;
    int map_y;
    int hit;
    int side;
    double  step_x;
    double  step_y;
    i = -1;
    while (++i < WIDTH)
    {
    minimap->ray.camera.x = 2 * i / (double) WIDTH - 1;
    minimap->ray.dir.y = minimap->player.dir.y + minimap->player.plane.y * minimap->ray.camera.x;
    minimap->ray.dir.x = minimap->player.dir.x + minimap->player.plane.x * minimap->ray.camera.x;
    hit = 0;
    map_x = (int)minimap->player.pos.x;
    map_y = (int)minimap->player.pos.y;
    minimap->ray.delta_dist.y = fabs(1 / minimap->ray.dir.y);
    minimap->ray.delta_dist.x = fabs(1 / minimap->ray.dir.x);
    if (minimap->ray.dir.y == 0)
        minimap->ray.delta_dist.y = 1e30;
    if (minimap->ray.dir.x == 0)
        minimap->ray.delta_dist.x = 1e30;
    if (minimap->ray.dir.x < 0)
    {
        step_x = -1;
        minimap->ray.side_dist.x = (minimap->player.pos.x - map_x) * minimap->ray.delta_dist.x;
    }
    else
    {
        step_x = 1;
        minimap->ray.side_dist.x = (map_x + 1.0 - minimap->player.pos.x) * minimap->ray.delta_dist.x;
    }
    if (minimap->ray.dir.y < 0)
    {
        step_y = -1;
        minimap->ray.side_dist.y = (minimap->player.pos.y - map_y) * minimap->ray.delta_dist.y;
    }
    else
    {
        step_y = 1;
        minimap->ray.side_dist.y = (map_y + 1.0 - minimap->player.pos.y) * minimap->ray.delta_dist.y;
    }
    while (hit == 0)
    {
        if (minimap->ray.side_dist.x < minimap->ray.side_dist.y)
        {
            minimap->ray.side_dist.x += minimap->ray.delta_dist.x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            minimap->ray.side_dist.y += minimap->ray.delta_dist.y;
            map_y += step_y;
            side = 1;
        }
        if (minimap->matrix[(int)map_x][(int)map_y] > '0')
            hit = 1;
    }
    if (side == 0)
        minimap->ray.wall_dist = minimap->ray.side_dist.x - minimap->ray.delta_dist.x;
    else
        minimap->ray.wall_dist = minimap->ray.side_dist.y - minimap->ray.delta_dist.y;
    int lineHeight = (int)(HEIGHT / minimap->ray.wall_dist);
    int drawStart = - lineHeight / 2 + HEIGHT / 2;
    if(drawStart < 0)
        drawStart = 0;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if(drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
    while (drawStart < drawEnd)
    {
        mlx_put_pixel(minimap->img_tmp, i, drawStart, get_rgba(0, 0, 255, 255));
        drawStart++;
    }
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
		// write2(i);
		k = ((MINIMAP_SIZE / MINIMAP_REC) / 2) * (-1);
		pix_x = -1;
		while (++pix_x < MINIMAP_SIZE)
		{
			// write2(k);
			if (minimap->matrix[(int)p->y + i][(int)p->x + k] == '1'
				|| (pix_x % MINIMAP_REC == (int)minimap->player.pos.x - (int)minimap->player.pos.x * 10))
				// || ((int)((minimap->player.pos.y - (int)minimap->player.pos.y) * 10)))) ||
				// (pix_y % MINIMAP_REC == (int)((minimap->player.pos.y - (int)minimap->player.pos.y) * 10) && minimap->matrix[(int)p->y + i][(int)p->x + k] == '1')))
				// (minimap->matrix[(int)p->y + i][(int)p->x + k] == '1' && (pix_x % MINIMAP_REC == (int)((minimap->player.pos.x - (int)minimap->player.pos.x) * 10 || (int)((minimap->player.pos.y - (int)minimap->player.pos.y) * 10))))))
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(250, 50, 50, 255));
			else
				mlx_put_pixel(minimap->img_map, pix_x, pix_y, get_rgba(160, 190, 150, 255)); // DRAW REST
			if ((pix_x) % (MINIMAP_REC) == 0)
				k++;
		}
		if ((pix_y) % (MINIMAP_REC) == 0)
			i++;

	}
	draw_map(minimap);
	draw_rays(minimap);
	draw_player(minimap);
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