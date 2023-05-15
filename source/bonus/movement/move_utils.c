/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:01:40 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/15 15:13:34 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	is_wall(int y, int x, char **matrix)
{
	if (matrix[y][x] == '1' || matrix[y][x] == 'D')
		return (true);
	return (false);
}

void	is_key_collected(t_map *map, t_player *player, t_sprite *sprite)
{
	if (map->has_key == false
		&& fabs(sprite->pos.x - player->pos.x) < (double)1
		&& fabs(sprite->pos.y - player->pos.y) < (double)1.5)
		map->has_key = true;
}
