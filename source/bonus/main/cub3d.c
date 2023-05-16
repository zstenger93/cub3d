/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:49 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/16 12:05:22 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data		data;

	init(argc, argv, &data);
	system("afplay ./resource/background.mp3 &");
	mlx_image_to_window(data.mlx, data.minimap->img_tmp, 0, 0);
	mlx_image_to_window(data.mlx, data.minimap->img_map, 0, 0);
	add_hooks(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	system("pkill afplay &");
	exit(0);
}

// void	print_map_objects(t_mlx_data *data)
// {
// 	ft_printf("NO: %s\n", data->no);
// 	ft_printf("SO: %s\n", data->so);
// 	ft_printf("WE: %s\n", data->we);
// 	ft_printf("EA: %s\n", data->ea);
// 	ft_printf("F: %d,%d,%d\n", data->f_color[0],
// 		data->f_color[1], data->f_color[2]);
// 	ft_printf("C: %d,%d,%d\n", data->c_color[0],
// 		data->c_color[1], data->c_color[2]);
// }
