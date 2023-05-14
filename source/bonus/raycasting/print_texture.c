/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:52:26 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/14 14:23:16 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

	// empty_buffer(m);
void	print_textures(t_map *m, int x, t_mlx_data *mlx_data)
{
	mlx_texture_t	*tex;
	int				i;

	tex = set_variables(m, mlx_data, x);
	while (m->tex->d_start < m->tex->d_end)
	{
		m->tex->tex.y = (int)m->tex->t_pos & (64 - 1);
		m->tex->t_pos += m->tex->step;
		m->tex->color = get_pixel_color(m, tex);
		m->buffer[x][m->tex->d_start] = m->tex->color;
		m->tex->d_start++;
	}
	i = m->tex->d_start;
	// while (i < HEIGHT)
	// 	m->buffer[x][i++] = rgb(mlx_data->f_color[0],
	// 			mlx_data->f_color[1], mlx_data->f_color[2], 200);
}

mlx_texture_t	*get_texture(t_map *map, t_mlx_data *mlx_data)
{
	if (map->matrix[(int)map->map_y][(int)map->map_x] == 'D')
		return (mlx_data->door);
	else if (map->side == 0 && map->ray.dir.x > 0)
		return (mlx_data->t_ea);
	else if (map->side == 0 && map->ray.dir.x < 0)
		return (mlx_data->t_we);
	else if (map->side == 1 && map->ray.dir.y > 0)
		return (mlx_data->t_no);
	else if (map->side == 1 && map->ray.dir.y < 0)
		return (mlx_data->t_so);
	return (NULL);
}

void	set_floor(t_map *map)
{
	int y;
	int p;
	float pos_z;
	float row_distance;
	float f_step_x;
	float f_step_y;
	float f_x;
	float f_y;
	mlx_texture_t *tex = mlx_load_png("resource/lava.png");
	mlx_texture_t *tex2 = mlx_load_png("resource/greystone.png");

	y = 0;
	while (y < HEIGHT)
	{
		float rayDirX0 = map->player.dir.x - map->player.plane.x;
    	float rayDirY0 = map->player.dir.y - map->player.plane.y;
    	float rayDirX1 = map->player.dir.x + map->player.plane.x;
    	float rayDirY1 = map->player.dir.y + map->player.plane.y;

		p = y - HEIGHT / 2;
		pos_z = 0.5 * HEIGHT; 
		row_distance = pos_z / p;
		f_step_x = row_distance * (rayDirX1 - rayDirX0) / WIDTH;
		f_step_y = row_distance * (rayDirY1 - rayDirY0) / WIDTH;

    	f_x = map->player.pos.x + row_distance * rayDirX0;
    	f_y = map->player.pos.y + row_distance * rayDirY0;
		for(int x = 0; x < WIDTH; ++x)
		{
			int	cell_x = (int)f_x;
			int	cell_y = (int)f_y;
			
			int tx = (int)(64 * (f_x - cell_x)) & (64 - 1);
			int ty = (int)(64 * (f_y - cell_y)) & (64 - 1);

			f_x += f_step_x;
			f_y += f_step_y;

			map->buffer[x][y] = rgb(tex->pixels[64 * (int)ty * 4 + (int)tx * 4], \
				tex->pixels[64 * (int)ty * 4 + (int)tx * 4 + 1], \
				tex->pixels[64 * (int)ty * 4 + (int)tx * 4 + 2], \
				tex->pixels[64 * (int)ty * 4 + (int)tx * 4 + 3]);
						
			map->buffer[x][HEIGHT - y - 1] = rgb(tex2->pixels[64 * (int)ty * 4 + (int)tx * 4], \
				tex2->pixels[64 * (int)ty * 4 + (int)tx * 4 + 1], \
				tex2->pixels[64 * (int)ty * 4 + (int)tx * 4 + 2], \
				tex2->pixels[64 * (int)ty * 4 + (int)tx * 4 + 3]);
		}
		y++;
	}
}

// trippy mode
// map->tex->t_pos = (map->tex->d_start + HEIGHT / 2
// 			- map->tex->line_height / 2) * map->tex->step;
void	set_tex_struct(t_map *map)
{
	map->tex->line_height = (int)(HEIGHT / map->ray.wall_dist);
	map->tex->d_start = -map->tex->line_height / 2 + HEIGHT / 2;
	if (map->tex->d_start < 0)
		map->tex->d_start = 0;
	map->tex->d_end = map->tex->line_height / 2 + HEIGHT / 2;
	if (map->tex->d_end >= HEIGHT)
		map->tex->d_end = HEIGHT - 1;
	map->tex->step = 1.0 * 64 / map->tex->line_height;
	map->tex->t_pos = (map->tex->d_start - HEIGHT / 2
			+ map->tex->line_height / 2) * map->tex->step;
}

mlx_texture_t	*set_variables(t_map *map, t_mlx_data *m_d, int x)
{
	int	i;

	set_tex_struct(map);
	if (map->side == 0)
		map->ray.x_hit_point = map->player.pos.y
			+ map->ray.wall_dist * map->ray.dir.y;
	else
		map->ray.x_hit_point = map->player.pos.x
			+ map->ray.wall_dist * map->ray.dir.x;
	map->ray.x_hit_point -= (int)map->ray.x_hit_point;
	map->tex->tex.x = (int)((map->ray.x_hit_point) * (double)64);
	if ((map->side == 0 && map->ray.dir.x > 0)
		|| (map->side == 1 && map->ray.dir.y < 0))
		map->tex->tex.x = 64 - map->tex->tex.x - 1;
	i = 0;
	// while (i < map->tex->d_start)
	// 	map->buffer[x][i++] = rgb(m_d->c_color[0],
	// 			m_d->c_color[1], m_d->c_color[2], 200);
	return (get_texture(map, m_d));
}

void	draw_buff(mlx_image_t *img_tmp, int32_t buffer[WIDTH][HEIGHT])
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
			mlx_put_pixel(img_tmp, i, j, buffer[i][j]);
	}
}

// void	print_vertical_lines(t_map *m, int i)
// {
// 	int	line_height;
// 	int	draw_start;
// 	int	draw_end;

// 	line_height = (int)(HEIGHT / m->ray.wall_dist);
// 	draw_start = -line_height / 2 + HEIGHT / 2;
// 	draw_end = line_height / 2 + HEIGHT / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	if (draw_end >= HEIGHT)
// 		draw_end = HEIGHT - 1;
// 	while (draw_start < draw_end)
// 	{
// 		if (m->side == 0)
// 			mlx_put_pixel(m->img_tmp, i, draw_start, rgb(0, 0, 255, 255));
// 		else
// 			mlx_put_pixel(m->img_tmp, i, draw_start, rgb(0, 255, 0, 255));
// 		draw_start++;
// 	}
// }
