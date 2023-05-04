/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:14:26 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/04 10:38:33 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_player_position(t_minimap *minimap, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < minimap->height)
	{
		x = 0;
		while (x < minimap->width)
		{
			if (map[y][x] == 'P')
			{
				minimap->player.y = y;
				minimap->player.x = x;
				printf("\n%d:%d\n", y, x);
				return ;
			}
			x++;
		}
		y++;
	}
}

t_minimap*	init_minimap(mlx_t *mlx, char *map)
{
	t_minimap	*minimap;
	int			fd;

	fd = open(map, O_RDWR);
	minimap = malloc(sizeof(minimap));
	minimap->width = get_width_of_map(fd);
	close(fd);
	fd = open(map, O_RDWR);
	minimap->height = get_height_of_map(fd);
	close(fd);
	fd = open(map, O_RDWR);
	minimap->map = mlx_new_image(mlx, 160, 160);
	minimap->matrix = get_matrix(minimap, fd);

	set_player_position(minimap, minimap->matrix);
	close(fd);
	return (minimap);
}
