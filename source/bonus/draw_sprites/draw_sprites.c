/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:16:16 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/15 11:50:05 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	sprites(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	calculate_sprite_attributes(data->minimap);
	draw_sprite(data->minimap);
}

void	calculate_sprite_attributes(t_map *map)
{
	t_sprite	*sprite;

	sprite = &map->sprite;
		
	sprite->distance = ((map->player.pos.x - sprite->pos.x) * (map->player.pos.x - sprite->pos.x) + (map->player.pos.y - sprite->pos.y) * (map->player.pos.y - sprite->pos.y));
	
	sprite->x = sprite->pos.x - map->player.pos.x;
	sprite->y = sprite->pos.y - map->player.pos.y;
	
	sprite->inv_det = 1.0 / (map->player.plane.x * map->player.dir.y - map->player.dir.x * map->player.plane.y);

	sprite->transform_x = sprite->inv_det * (map->player.dir.y * sprite->x - map->player.dir.x * sprite->y);
	sprite->transform_y = sprite->inv_det * (-map->player.plane.y * sprite->x + map->player.plane.x * sprite->y);
	
	// printf("%f:%f\n", sprite->y, sprite->x);
	sprite->screen_x = (int)((WIDTH / 2) * (1 + sprite->transform_x / sprite->transform_y));

	sprite->v_move_screen = (int)(VMOVE / sprite->transform_y);

	sprite->size.y = fabs((HEIGHT / sprite->transform_y)) / VDIV;
	sprite->size.x = fabs((HEIGHT / sprite->transform_y)) / UDIV;
	
	sprite->draw_start.y = -sprite->size.y / 2 + HEIGHT / 2 + sprite->v_move_screen;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->size.y / 2 + HEIGHT / 2 + sprite->v_move_screen;
	if (sprite->draw_end.y >= HEIGHT)
		sprite->draw_end.y = HEIGHT - 1;
	
	sprite->draw_start.x = -sprite->size.x / 2 + sprite->screen_x;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->size.x / 2 + sprite->screen_x;
	if (sprite->draw_end.x > WIDTH)
		sprite->draw_end.x = WIDTH;
}

void	draw_sprite(t_map *map)
{
	int			y;
	int			d;
	int			texture_x;
	int			texture_y;
	t_sprite	*sprite;
	uint32_t	color;

	sprite = &map->sprite;
	sprite->stripe = (int)sprite->draw_start.x;
	while (sprite->stripe++ < (int)sprite->draw_end.x)
	{
				// write(1, "here\n", 5);
		texture_x = (int)(256 * ((int)sprite->draw_start.x - ((int)-sprite->size.y / 2 + sprite->screen_x)) * 64 / (int)sprite->size.y) / 256;
		if ((int)sprite->transform_y > 0 && sprite->transform_y < map->z_buffer[sprite->stripe])
		{
			y = sprite->draw_start.y;
			while (y++ < sprite->draw_end.y)
			{
				// printf("stripe: %d start x: %f end x: %f\n", sprite->stripe, sprite->draw_start.x, sprite->draw_end.x);
				d = (y - sprite->v_move_screen) * 256 - HEIGHT * 128 + sprite->size.y * 128;
				texture_y = ((d * 64) / sprite->size.y) / 256;

				color = rgb(sprite->textures[0]->pixels[64 * texture_y * 4 + texture_x * 1],
								sprite->textures[0]->pixels[64 * texture_y * 4 + texture_x * 1 + 1],
								sprite->textures[0]->pixels[64 * texture_y * 4 + texture_x * 1 + 2],
								sprite->textures[0]->pixels[64 * texture_y * 4 + texture_x * 1 + 3]);
				// printf("%d,%d,%d,%d\n", sprite->textures[0]->pixels[64 * texture_y * 4 + texture_x * 4], sprite->textures[0]->pixels[64 * texture_y * 4 + texture_x * 4 + 1], sprite->textures[0]->pixels[64 * texture_y * 4 + texture_x * 4 + 2], sprite->textures[0]->pixels[64 * texture_y * 4 + texture_x * 4] + 3);
				if ((color & 0x00FFFFFF) != 0)
					map->buffer[sprite->stripe][y] = color;
			}
		}
	}
}
