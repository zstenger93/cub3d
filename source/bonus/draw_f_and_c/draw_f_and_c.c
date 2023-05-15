/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_f_and_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:51:57 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/15 19:40:20 by zstenger         ###   ########.fr       */
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

//p -> current y position compared to the center of the screen
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
	fc->floor_x = map->player.pos.x + fc->row_distance * fc->ray_dir_x0;
	fc->floor_y = map->player.pos.y + fc->row_distance * fc->ray_dir_y0;
}

void	init_variables_for_x(t_map *map, t_fc_tex *fc, int x, int y)
{
	uint32_t	color;
	uint32_t	color2;

	fc->cell_x = (int)fc->floor_x;
	fc->cell_y = (int)fc->floor_y;
	fc->tex_x = (int)(64 * (fc->floor_x - fc->cell_x)) & (64 - 1);
	fc->tex_y = (int)(64 * (fc->floor_y - fc->cell_y)) & (64 - 1);
	fc->floor_x += fc->f_step_x;
	fc->floor_y += fc->f_step_y;
	color = rgb((int)fc->tex->pixels[64 * fc->tex_y
			* 4 + fc->tex_x * 4], \
		(int)fc->tex->pixels[64 * fc->tex_y * 4 + fc->tex_x * 4 + 1], \
		(int)fc->tex->pixels[64 * fc->tex_y * 4 + fc->tex_x * 4 + 2], \
		(int)fc->tex->pixels[64 * fc->tex_y * 4 + fc->tex_x * 4 + 3]);
	if ((color & 0x00FFFFFF) != 0)
		map->buffer[x][y] = color;
	color2 = rgb((int)fc->tex2->pixels[64 * fc->tex_y
			* 4 + fc->tex_x * 4], \
		(int)fc->tex2->pixels[64 * fc->tex_y * 4 + fc->tex_x * 4 + 1], \
		(int)fc->tex2->pixels[64 * fc->tex_y * 4 + fc->tex_x * 4 + 2], \
		(int)fc->tex2->pixels[64 * fc->tex_y * 4 + fc->tex_x * 4 + 3]);
	if ((color2 & 0x00FFFFFF) != 0)
		map->buffer[x][HEIGHT - y - 1] = color2;
}
