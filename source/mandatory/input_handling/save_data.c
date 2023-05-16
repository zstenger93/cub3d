/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:03:58 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/16 07:54:02 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// save the path to the textures
void	save_texture_to_data(char *file, t_mlx_data *data, char option)
{
	if (option == 'N')
	{
		free(data->no);
		data->no = ft_strdup(file);
	}
	if (option == 'S')
	{
		free(data->no);
		data->so = ft_strdup(file);
	}
	if (option == 'W')
	{
		free(data->no);
		data->we = ft_strdup(file);
	}
	if (option == 'E')
	{
		free(data->no);
		data->ea = ft_strdup(file);
	}
}

// save the rgb colors as int
void	save_color_to_data(char **rgb, t_mlx_data *data, char option)
{
	if (option == 'F')
	{
		data->f_color[0] = ft_atoi(rgb[0]);
		data->f_color[1] = ft_atoi(rgb[1]);
		data->f_color[2] = ft_atoi(rgb[2]);
	}
	else if (option == 'C')
	{
		data->c_color[0] = ft_atoi(rgb[0]);
		data->c_color[1] = ft_atoi(rgb[1]);
		data->c_color[2] = ft_atoi(rgb[2]);
	}
}
