/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:03:46 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/18 19:50:08 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	init(int argc, char **argv, t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	data->mlx_data = init_data();
	if (argc == 1)
		return (p_err("%s%s", TMA, HOW_TO_LAUNCH), false);
	if (input_check(argc, argv[1], data->mlx_data) == false)
	{
		free_mlx_data_on_error(data->mlx_data, data);
		exit(0);
	}
	data->minimap = init_map(data->mlx_data, data->mlx);
	init_textures(data->mlx_data, &data->minimap->fc);
	data->minimap->tex = malloc(sizeof(t_tex));
	if (data->minimap->tex == NULL)
		return (p_err(MALLOC_FAIL), 1);
	init_spirite_position(data->minimap);
	system("afplay ./resource/background.mp3 &");
	return (0);
}

void	init_spirite_position(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (map->matrix[++y] != NULL)
	{
		x = -1;
		while (map->matrix[y][++x] != '\0')
		{
			if (map->matrix[y][x] == 'K')
			{
				map->sprite.pos.x = x;
				map->sprite.pos.y = y;
				break ;
			}
		}
	}
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

void	init_textures(t_mlx_data *mlx_data, t_fc_tex *fc)
{
	mlx_data->door = mlx_load_png("resource/bhole.png");
	if (mlx_data->door == NULL)
	{
		p_err(BAD_DOOR);
		exit(0);
	}
	mlx_data->t_no = mlx_load_png(mlx_data->no);
	mlx_data->t_so = mlx_load_png(mlx_data->so);
	mlx_data->t_we = mlx_load_png(mlx_data->we);
	mlx_data->t_ea = mlx_load_png(mlx_data->ea);
	fc->tex = mlx_load_png("resource/lava.png");
	if (fc->tex == NULL)
	{
		p_err(BAD_FLOOR);
		exit(0);
	}
	fc->tex2 = mlx_load_png("resource/greystone.png");
	if (fc->tex2 == NULL)
	{
		p_err(BAD_CEILING);
		exit(0);
	}
}

void	free_mlx_data_on_error(t_mlx_data *mlx_data, t_data *data)
{
	system("pkill afplay &");
	free(mlx_data->no);
	free(mlx_data->so);
	free(mlx_data->we);
	free(mlx_data->ea);
	free(mlx_data);
	mlx_terminate(data->mlx);
}
