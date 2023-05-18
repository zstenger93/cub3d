/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:04:44 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/18 11:14:28 by jergashe         ###   ########.fr       */
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
	free_mlx_data(data, data->mlx_data);
	mlx_terminate(data->mlx);
}
