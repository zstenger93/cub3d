/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:00:33 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/15 19:00:14 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	turn_left(t_data *data, t_player *playr)
{
	double	sp;
	double	old_dir_x;
	double	old_plane_x;

	if (playr->speed_is_life == false)
		sp = NORMAL_SPEED;
	else
		sp = FAST_SPEED;
	old_dir_x = playr->dir.x;
	playr->dir.x = playr->dir.x * cos(-sp) - playr->dir.y * sin(-sp);
	playr->dir.y = old_dir_x * sin(-sp) + playr->dir.y * cos(-sp);
	old_plane_x = playr->plane.x;
	playr->plane.x = playr->plane.x * cos(-sp) - playr->plane.y * sin(-sp);
	playr->plane.y = old_plane_x * sin(-sp) + playr->plane.y * cos(-sp);
}

void	turn_right(t_data *data, t_player *player)
{
	double	sp;
	double	old_dir_x;
	double	old_plane_x;

	if (player->speed_is_life == false)
		sp = NORMAL_SPEED;
	else
		sp = FAST_SPEED;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(sp) - player->dir.y * sin(sp);
	player->dir.y = old_dir_x * sin(sp) + player->dir.y * cos(sp);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(sp) - player->plane.y * sin(sp);
	player->plane.y = old_plane_x * sin(sp) + player->plane.y * cos(sp);
}
