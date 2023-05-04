/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:49 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/04 16:14:39 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_data(t_mlx_data *mlx_data)
{
	mlx_data->no = ft_strdup("X");
	mlx_data->so = ft_strdup("X");
	mlx_data->we = ft_strdup("X");
	mlx_data->ea = ft_strdup("X");
	mlx_data->floor_color[0] = -1;
	mlx_data->ceiling_color[0] = -1;
	mlx_data->reading_pos = 0;
	mlx_data->map_length = 0;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
  	mlx_t *mlx;
	t_mlx_data	mlx_data;
	t_minimap	*minimap;
	t_data		data;

	init_data(&mlx_data);
	if (input_check(argc, argv[1], &mlx_data) == false)
		exit(0);
	else
	{
		mlx = mlx_init(WIDTH, HEIGHT, "Survive The NORM", 1);

		minimap = init_minimap(mlx, argv[1]);

		data.mlx = mlx;
		data.minimap = minimap;
		draw_minimap(minimap);

		mlx_image_to_window(mlx, minimap->map, 0, 0);
		add_hooks(&data);
		mlx_loop(mlx);
		mlx_terminate(mlx);
		
	}
	exit(0);
}

void	print_map_objects(t_mlx_data *data)
{
	printf("NO: %s\n", data->no);
	printf("SO: %s\n", data->so);
	printf("WE: %s\n", data->we);
	printf("EA: %s\n", data->ea);
	
	printf("F: %d,%d,%d\n", data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
	printf("C: %d,%d,%d\n", data->floor_color[0], data->ceiling_color[1], data->ceiling_color[2]);
}
