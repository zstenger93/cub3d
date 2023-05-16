/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:49 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/16 10:31:50 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	free_mlx_data(t_data *data, t_mlx_data *mlx_data)
{
	free(mlx_data->no);
	free(mlx_data->so);
	free(mlx_data->we);
	free(mlx_data->ea);
	mlx_delete_texture(mlx_data->t_no);
	mlx_delete_texture(mlx_data->t_so);
	mlx_delete_texture(mlx_data->t_we);
	mlx_delete_texture(mlx_data->t_ea);
	mlx_delete_texture(mlx_data->door);
	mlx_delete_texture(mlx_data->texture);
	free_char_array(mlx_data->raw_map);
	free_char_array(mlx_data->map_copy);
	free(mlx_data);
}

void	free_map(t_data *data, t_map *map)
{
	mlx_delete_image(data->mlx, map->img_map);
	mlx_delete_image(data->mlx, map->img_tmp);
	free_char_array(map->matrix);
	free(map->tex);
	free(map);
}

void	free_data(t_data *data)
{
	free_map(data, data->minimap);
	free_data(data);
}

int	main(int argc, char **argv)
{
	t_data		data;

	init(argc, argv, &data);
	mlx_image_to_window(data.mlx, data.minimap->img_tmp, 0, 0);
	mlx_image_to_window(data.mlx, data.minimap->img_map, 0, 0);
	add_hooks(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_data(&data);
	exit(0);
}

void	print_map_objects(t_mlx_data *data)
{
	ft_printf("NO: %s\n", data->no);
	ft_printf("SO: %s\n", data->so);
	ft_printf("WE: %s\n", data->we);
	ft_printf("EA: %s\n", data->ea);
	ft_printf("F: %d,%d,%d\n", data->f_color[0],
		data->f_color[1], data->f_color[2]);
	ft_printf("C: %d,%d,%d\n", data->c_color[0],
		data->c_color[1], data->c_color[2]);
}
