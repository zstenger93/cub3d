/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_f_and_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:51:57 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/14 16:54:44 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_floor_and_ceiling(t_map *map)
{
	t_fc_tex	fc;
	int			y;
	int			x;

	y = 0;
	fc = map->fc;
	fc.tex = mlx_load_png("resource/lava.png");
	fc.tex2 = mlx_load_png("resource/greystone.png");
	while (y < HEIGHT)
	{
		init_variables_for_y(map, &fc, y);
		x = 0;
		while (x++ < WIDTH)
			init_variables_for_x(map, &fc, x, y);
		y++;
	}
}

void	init_variables_for_y(t_map *map, t_fc_tex *fc, int y)
{
	fc->ray_dir_x0 = map->player.dir.x - map->player.plane.x;
	fc->ray_dir_y0 = map->player.dir.y - map->player.plane.y;
	fc->ray_dir_x1 = map->player.dir.x + map->player.plane.x;
	fc->ray_dir_y1 = map->player.dir.y + map->player.plane.y;
	fc->p = y - HEIGHT / 2;
	fc->pos_z = 0.5 * HEIGHT;
	fc->row_distance = fc->pos_z / fc->p;
	fc->f_step_x = fc->row_distance
		* (fc->ray_dir_x1 - fc->ray_dir_x0) / WIDTH;
	fc->f_step_y = fc->row_distance
		* (fc->ray_dir_y1 - fc->ray_dir_y0) / WIDTH;
	fc->f_x = map->player.pos.x + fc->row_distance * fc->ray_dir_x0;
	fc->f_y = map->player.pos.y + fc->row_distance * fc->ray_dir_y0;
}

void	init_variables_for_x(t_map *map, t_fc_tex *fc, int x, int y)
{
	fc->cell_x = (int)fc->f_x;
	fc->cell_y = (int)fc->f_y;
	fc->tx = (int)(64 * (fc->f_x - fc->cell_x)) & (64 - 1);
	fc->ty = (int)(64 * (fc->f_y - fc->cell_y)) & (64 - 1);
	fc->f_x += fc->f_step_x;
	fc->f_y += fc->f_step_y;
	map->buffer[x][y] = rgb(fc->tex->pixels[64 * (int)fc->ty
			* 4 + (int)fc->tx * 4], \
		fc->tex->pixels[64 * (int)fc->ty * 4 + (int)fc->tx * 4 + 1], \
		fc->tex->pixels[64 * (int)fc->ty * 4 + (int)fc->tx * 4 + 2], \
		fc->tex->pixels[64 * (int)fc->ty * 4 + (int)fc->tx * 4 + 3]);
	map->buffer[x][HEIGHT - y - 1] = rgb(fc->tex2->pixels[64 * (int)fc->ty
			* 4 + (int)fc->tx * 4], \
		fc->tex2->pixels[64 * (int)fc->ty * 4 + (int)fc->tx * 4 + 1], \
		fc->tex2->pixels[64 * (int)fc->ty * 4 + (int)fc->tx * 4 + 2], \
		fc->tex2->pixels[64 * (int)fc->ty * 4 + (int)fc->tx * 4 + 3]);
}
