/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:52:26 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/12 09:19:56 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	empty_buffer(t_map *map)
{
	int	y;
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
			map->buffer[x][y] = 0;
		y++;	
	}
}

// void	ray_hitting_point(t_map *map, int hit)
// {
	
// 	map->tex->line_height = (int)(HEIGHT * 0.6 / map->ray.wall_dist);
// 	map->tex->d_start = -map->tex->line_height / 2 + HEIGHT / 2;
// 	map->tex->d_end = map->tex->line_height / 2 + HEIGHT / 2;
// 	if (map->tex->d_start < 0)
// 		map->tex->d_start = 0;
// 	if (map->tex->d_end >= HEIGHT)
// 		map->tex->d_end = HEIGHT - 1;

// 	if (map->side == 0)
// 		map->ray.wall_dist = map->ray.side_dist.x - map->ray.delta_dist.x;
// 	else
// 		map->ray.wall_dist = map->ray.side_dist.y - map->ray.delta_dist.y;
// 	map->ray.wall_dist = map->ray.wall_dist - (double)((int)map->ray.wall_dist);
	// map->tex->tex.x = (int)(map->ray.wall_dist) * (double)64;
	// if (map->side == 0 && map->ray.dir.x > 0 || (map->side == 1 && map->ray.dir.y < 0))
	// 	map->tex->tex.x = 64 - map->tex->tex.x - 1;
// }

void	print_textures(t_map *m, int x, t_mlx_data *mlx_data)
{
	mlx_texture_t	*tex;
	int				i;

	tex = set_variables(m, mlx_data, x);
	// empty_buffer(m);
	while (m->tex->d_start < m->tex->d_end)
	{
		m->tex->tex.y = (int)m->tex->t_pos & (64 - 1);
		m->tex->t_pos += m->tex->step;
		m->tex->height = get_pixel_color(m, tex);
		// if (m->side == 1)
		// 	m->tex->height = (m->tex->height >> 1) & 8355711;
		m->buffer[x][m->tex->d_start] = m->tex->height;
		m->tex->d_start++;
	}
	i = m->tex->d_start;
	while (i < HEIGHT)
		m->buffer[x][i++] = rgb(mlx_data->floor_color[0], mlx_data->floor_color[1], mlx_data->floor_color[2], 255);
}

mlx_texture_t	*get_texture(t_map *map, t_mlx_data *mlx_data)
{
	if (map->side == 0 && map->ray.dir.x > 0) //gets in
		return (mlx_data->t_ea);
	if (map->side == 0 && map->ray.dir.x < 0) //gets in but load nothing
		return (mlx_data->t_we);
	if (map->side == 1 && map->ray.dir.y > 0) //gets in
		return (mlx_data->t_no);
	if (map->side == 1 && map->ray.dir.y < 0) //gets in
		return (mlx_data->t_so);
	// write(1, "here\n", 6);
	return (NULL);
}

mlx_texture_t	*set_variables(t_map *map, t_mlx_data *mlx_data, int x)
{
	int				i;
	mlx_texture_t	*tex;
	int pitch = 100;

	tex = get_texture(map, mlx_data);
	map->tex->line_height = (int)(HEIGHT / map->ray.wall_dist);
	map->tex->d_start = -map->tex->line_height / 2 + HEIGHT / 2 + pitch;
	map->tex->d_end = map->tex->line_height / 2 + HEIGHT / 2 + pitch;
	map->tex->step = 1.0 * 64 / map->tex->line_height;
	map->tex->t_pos = (map->tex->d_start - pitch - HEIGHT / 2 + map->tex->line_height / 2) * map->tex->step;
	if (map->tex->d_start < 0)
		map->tex->d_start = 0;
	if (map->tex->d_end >= HEIGHT)
		map->tex->d_end = HEIGHT - 1;
		
	if (map->side == 0)
		map->ray.x_hit_point = map->player.pos.y + map->ray.wall_dist * map->ray.dir.y;
	else
		map->ray.x_hit_point = map->player.pos.x + map->ray.wall_dist * map->ray.dir.x;
	map->ray.x_hit_point -= (int)map->ray.x_hit_point;
	
	map->tex->tex.x = (int)((map->ray.x_hit_point) * (double)64);
	
	if ((map->side == 0 && map->ray.dir.x > 0) || (map->side == 1 && map->ray.dir.y < 0))
		map->tex->tex.x = 64 - map->tex->tex.x - 1;
	i = 0;
	while (i < map->tex->d_start)
		map->buffer[x][i++] = rgb(mlx_data->ceiling_color[0], mlx_data->ceiling_color[1], mlx_data->ceiling_color[2], 255);
	return (tex);
}

int	get_pixel_color(t_map *map, mlx_texture_t *tex)
{
	return (rgb(tex->pixels[64 * (int)map->tex->tex.y * 4 + (int)map->tex->tex.x * 4], \
				tex->pixels[64 * (int)map->tex->tex.y * 4 + (int)map->tex->tex.x * 4 + 1], \
				tex->pixels[64 * (int)map->tex->tex.y * 4 + (int)map->tex->tex.x * 4 + 2], \
				tex->pixels[64 * (int)map->tex->tex.y * 4 + (int)map->tex->tex.x * 4 + 3]));
}

void	draw_buff(mlx_image_t *img_tmp, int32_t buffer[WIDTH][HEIGHT])
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			// printf("%d ", buffer[j][i]);
			// if (buffer[j][i] != 0)
			mlx_put_pixel(img_tmp, j, i, buffer[j][i]);
			j++;
		}
			// printf("\n");
		i++;
	}
}

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
