/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:16:16 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/14 20:11:49 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// void	sprites(void *param)
// {
// 	t_data	*data;

// 	data = (t_data *)param;
	
// 	draw_sprites(data->minimap);
// }


void	draw_sprites(t_map *map)
{
	t_sprite	sprite;

	sprite = map->sprite;
	
	sprite.distance = ((map->player.pos.x - sprite.pos.x) * (map->player.pos.x - sprite.pos.x) + (map->player.pos.y - sprite.pos.y) * (map->player.pos.y - sprite.pos.y));
	
	sprite.x = sprite.pos.x - map->player.pos.x;
	sprite.y = sprite.pos.y - map->player.pos.y;
	
	sprite.inv_det = 1.0 / (map->player.plane.x * map->player.dir.y - map->player.dir.x * map->player.plane.y);

	sprite.transform_x = sprite.inv_det * (map->player.dir.y * sprite.x - map->player.dir.x * sprite.y);
	sprite.transform_y = sprite.inv_det * (-map->player.plane.y * sprite.x + map->player.plane.x * sprite.y);
	
	sprite.screen_x = (int)((WIDTH / 2) * (1 + sprite.transform_x / sprite.transform_y));

	sprite.size.y = abs((int)(HEIGHT / (sprite.transform_y)));
	sprite.size.x = abs((int)(HEIGHT / (sprite.transform_y)));
	
	sprite.draw_start.y = -sprite.size.y / 2 + HEIGHT / 2;
	if (sprite.draw_start.y < 0)
		sprite.draw_start.y = 0;
	sprite.draw_end.y = sprite.size.y / 2 + HEIGHT / 2;
	if (sprite.draw_end.y >= HEIGHT)
		sprite.draw_end.y = HEIGHT - 1;
	
	sprite.draw_start.x = -sprite.size.x / 2 + sprite.screen_x;
	if (sprite.draw_start.x < 0)
		sprite.draw_start.x = 0;
	sprite.draw_end.x = sprite.size.x / 2 + sprite.screen_x;
	if (sprite.draw_end.x >= WIDTH)
		sprite.draw_end.x = WIDTH - 1;

	
}