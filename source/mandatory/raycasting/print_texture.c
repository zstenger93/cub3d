/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:52:26 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/15 10:44:52 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

	// empty_buffer(m);
		// if (m->side == 1)
		// 	m->tex->color = (m->tex->color >> 1) & 8355711;
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
	while (i < HEIGHT)
		m->buffer[x][i++] = rgb(mlx_data->f_color[0],
				mlx_data->f_color[1], mlx_data->f_color[2], 255);
}

mlx_texture_t	*get_texture(t_map *map, t_mlx_data *mlx_data)
{
	if (map->side == 0 && map->ray.dir.x > 0)
		return (mlx_data->t_ea);
	if (map->side == 0 && map->ray.dir.x < 0)
		return (mlx_data->t_we);
	if (map->side == 1 && map->ray.dir.y > 0)
		return (mlx_data->t_no);
	if (map->side == 1 && map->ray.dir.y < 0)
		return (mlx_data->t_so);
	return (NULL);
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
	while (i < map->tex->d_start)
		map->buffer[x][i++] = rgb(m_d->c_color[0],
				m_d->c_color[1], m_d->c_color[2], 255);
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
