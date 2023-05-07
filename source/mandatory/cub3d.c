/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:49 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/07 10:41:26 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_mlx_data	*init_data(void)
{
	t_mlx_data	*mlx_data;

	mlx_data = malloc(sizeof(t_mlx_data));
	mlx_data->no = ft_strdup("X");
	mlx_data->so = ft_strdup("X");
	mlx_data->we = ft_strdup("X");
	mlx_data->ea = ft_strdup("X");
	mlx_data->floor_color[0] = -1;
	mlx_data->ceiling_color[0] = -1;
	mlx_data->reading_pos = 0;
	mlx_data->map_length = 0;
	return (mlx_data);
}

int	init(int argc, char **argv, t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	data->mlx_data = init_data();
	if (argc == 1)
		return (ft_printf("%s%s", TMA, HOW_TO_LAUNCH), false);
	if (input_check(argc, argv[1], data->mlx_data) == false)
		exit(0);
	data->minimap = init_minimap(data->mlx_data, data->mlx);
	return (0);
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
	exit(0);
}

void	print_map_objects(t_mlx_data *data)
{
	printf("NO: %s\n", data->no);
	printf("SO: %s\n", data->so);
	printf("WE: %s\n", data->we);
	printf("EA: %s\n", data->ea);
	printf("F: %d,%d,%d\n", data->floor_color[0], data->floor_color[1], data->floor_color[2]);
	printf("C: %d,%d,%d\n", data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
}
