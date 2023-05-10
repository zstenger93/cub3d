/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:03:58 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/10 14:34:47 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// save the path to the textures
void	save_texture_to_data(char *file, t_mlx_data *data, char option)
{
	if (option == 'N')
		data->no = ft_strdup(file);
	if (option == 'S')
		data->so = ft_strdup(file);
	if (option == 'W')
		data->we = ft_strdup(file);
	if (option == 'E')
		data->ea = ft_strdup(file);
}

// save the rgb colors as int
void	save_color_to_data(char **rgb, t_mlx_data *data, char option)
{
	if (option == 'F')
	{
		data->floor_color[0] = ft_atoi(rgb[0]);
		data->floor_color[1] = ft_atoi(rgb[1]);
		data->floor_color[2] = ft_atoi(rgb[2]);
	}
	else if (option == 'C')
	{
		data->ceiling_color[0] = ft_atoi(rgb[0]);
		data->ceiling_color[1] = ft_atoi(rgb[1]);
		data->ceiling_color[2] = ft_atoi(rgb[2]);
	}
}
