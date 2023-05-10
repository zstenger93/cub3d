/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:52:26 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/10 18:35:18 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	print_vertical_lines(t_map *m, int i)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HEIGHT / m->ray.wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	while (draw_start < draw_end)
	{
		if (m->side == 0)
			mlx_put_pixel(m->img_tmp, i, draw_start, rgb(0, 0, 255, 255));
		else
			mlx_put_pixel(m->img_tmp, i, draw_start, rgb(0, 255, 0, 255));
		draw_start++;
	}
}
