/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:49 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/04 10:15:51 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
  	mlx_t *mlx;
	// t_mlx_data	*data;
	t_minimap	*minimap;
	t_data		data;

	// if (input_check(argc, argv[1], data) == false)
	// 	return (EXIT_FAILURE);

	mlx = mlx_init(WIDTH, HEIGHT, "Survive The NORM", 1);

	minimap = init_minimap(mlx, argv[1]);

	data.mlx = mlx;
	data.minimap = minimap;
	draw_minimap(minimap);

	mlx_image_to_window(mlx, minimap->map, 0, 0);
	add_hooks(&data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
