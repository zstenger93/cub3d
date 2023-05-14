/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:00:33 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/14 10:42:17 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	turn_left(t_data *data, t_player *playr)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = playr->dir.x;
	playr->dir.x = playr->dir.x * cos(-0.05) - playr->dir.y * sin(-0.05);
	playr->dir.y = old_dir_x * sin(-0.05) + playr->dir.y * cos(-0.05);
	old_plane_x = playr->plane.x;
	playr->plane.x = playr->plane.x * cos(-0.05) - playr->plane.y * sin(-0.05);
	playr->plane.y = old_plane_x * sin(-0.05) + playr->plane.y * cos(-0.05);
}

void	turn_right(t_data *data, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(0.05) - player->dir.y * sin(0.05);
	player->dir.y = old_dir_x * sin(0.05) + player->dir.y * cos(0.05);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(0.05) - player->plane.y * sin(0.05);
	player->plane.y = old_plane_x * sin(0.05) + player->plane.y * cos(0.05);
}
