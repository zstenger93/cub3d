/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:49 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/15 16:55:07 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data		data;

	init(argc, argv, &data);
	data.minimap->sprite.textures[0] = mlx_load_png("resource/key17.png");
	data.minimap->sprite.textures[1] = mlx_load_png("resource/key15.png");
	data.minimap->sprite.textures[2] = mlx_load_png("resource/key20.png");
	data.minimap->sprite.textures[3] = mlx_load_png("resource/key16.png");
	data.minimap->sprite.textures[4] = mlx_load_png("resource/key13.png");
	data.minimap->sprite.textures[5] = mlx_load_png("resource/key14.png");
	data.minimap->sprite.textures[6] = mlx_load_png("resource/key11.png");
	data.minimap->sprite.textures[7] = mlx_load_png("resource/key10.png");
	mlx_image_to_window(data.mlx, data.minimap->img_tmp, 0, 0);
	mlx_image_to_window(data.mlx, data.minimap->img_map, 0, 0);
	add_hooks(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	exit(0);
}

void	print_map_objects(t_mlx_data *data)
{
	printf("NO: %s\n", data->no);
	printf("SO: %s\n", data->so);
	printf("WE: %s\n", data->we);
	printf("EA: %s\n", data->ea);
	printf("F: %d,%d,%d\n", data->f_color[0],
		data->f_color[1], data->f_color[2]);
	printf("C: %d,%d,%d\n", data->c_color[0],
		data->c_color[1], data->c_color[2]);
}
