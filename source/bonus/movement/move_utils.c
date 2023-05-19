/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:01:40 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/19 11:32:54 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	is_wall(int y, int x, char **matrix)
{
	if (matrix[y][x] == '1' || matrix[y][x] == 'D')
		return (true);
	return (false);
}

void	is_escape(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		free_data(data);
		system("leaks cub3D");
		exit(0);
	}
}

void	set_speed(t_player *player)
{
	if (player->speed_is_life == false)
		player->speed = NORMAL;
	else
		player->speed = FAST;
}

void	is_key_collected(t_map *m, t_player *player, t_sprite *sprite)
{
	int	i;

	i = 0;
	set_speed(player);
	if (m->has_key == false
		&& fabs(sprite->pos.x - player->pos.x) < (double)1
		&& fabs(sprite->pos.y - player->pos.y) < (double)1.5)
	{
		i++;
		if (i == 1)
			system("afplay ./resource/keys.mp3 &");
		m->has_key = true;
	}
}
