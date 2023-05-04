/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:14:26 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/04 15:09:17 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_player_position(t_minimap *minimap, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < minimap->height)
	{
		x = -1;
		while (++x < minimap->width)
		{
			if (map[y][x] == 'P')
			{
				minimap->player.y = y;
				minimap->player.x = x;
				printf("\n%d:%d\n", y, x);
				return ;
			}
		}
	}
	minimap->player.angle = M_PI / 2;
	minimap->player.delta_x = cos(minimap->player.angle) * 5;
	minimap->player.delta_x = sin(minimap->player.angle) * 5;
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
