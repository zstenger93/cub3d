/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:03:46 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/16 09:49:26 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	init(int argc, char **argv, t_data *data)
{
	if (argc == 1)
		return (ft_printf("%s%s", TMA, HOW_TO_LAUNCH), false);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	data->mlx_data = init_data();
	if (argc == 1)
		return (p_err("%s%s", TMA, HOW_TO_LAUNCH), false);
	if (input_check(argc, argv[1], data->mlx_data) == false)
		exit(0);
	data->minimap = init_map(data->mlx_data, data->mlx);
	init_m_textures(data->mlx_data);
	data->minimap->tex = malloc(sizeof(t_tex));
	if (data->minimap->tex == NULL)
		return (p_err(MALLOC_FAIL), 1);
	return (0);
}

t_mlx_data	*init_data(void)
{
	t_mlx_data	*mlx_data;

	mlx_data = malloc(sizeof(t_mlx_data));
	if (mlx_data == NULL)
		return (p_err(MALLOC_FAIL), NULL);
	mlx_data->no = ft_strdup("X");
	mlx_data->so = ft_strdup("X");
	mlx_data->we = ft_strdup("X");
	mlx_data->ea = ft_strdup("X");
	mlx_data->f_color[0] = -1;
	mlx_data->f_color[1] = -1;
	mlx_data->f_color[2] = -1;
	mlx_data->c_color[0] = -1;
	mlx_data->c_color[1] = -1;
	mlx_data->c_color[2] = -1;
	mlx_data->reading_pos = 0;
	mlx_data->map_length = 0;
	return (mlx_data);
}

void	init_m_textures(t_mlx_data *mlx_data)
{
	mlx_data->t_no = mlx_load_png(mlx_data->no);
	mlx_data->t_so = mlx_load_png(mlx_data->so);
	mlx_data->t_we = mlx_load_png(mlx_data->we);
	mlx_data->t_ea = mlx_load_png(mlx_data->ea);
}
