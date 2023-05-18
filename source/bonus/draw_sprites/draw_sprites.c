/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:16:16 by jergashe          #+#    #+#             */
/*   Updated: 2023/05/18 08:41:53 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	calculate_sprite_attributes(t_map *map, t_sprite *sprite)
{
	love_norm(map, sprite);
	sprite->draw_start.y = -sprite->size.y / 2 + HEIGHT / 2
		+ sprite->v_move_screen;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->size.y / 2 + HEIGHT / 2
		+ sprite->v_move_screen;
	if (sprite->draw_end.y >= HEIGHT)
		sprite->draw_end.y = HEIGHT - 1;
	sprite->draw_start.x = -sprite->size.x / 2 + sprite->screen_x;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->size.x / 2 + sprite->screen_x;
	if (sprite->draw_end.x > WIDTH)
		sprite->draw_end.x = WIDTH;
}

// setting sprite attributes first part
void	love_norm(t_map *map, t_sprite *sprite)
{
	sprite->distance = ((map->player.pos.x - sprite->pos.x)
			* (map->player.pos.x - sprite->pos.x)
			+ (map->player.pos.y - sprite->pos.y)
			* (map->player.pos.y - sprite->pos.y));
	sprite->x = sprite->pos.x - map->player.pos.x + 0.5;
	sprite->y = sprite->pos.y - map->player.pos.y + 0.5;
	sprite->inv_det = 1.0 / (map->player.plane.x * map->player.dir.y
			- map->player.dir.x * map->player.plane.y);
	sprite->transform_x = sprite->inv_det * (map->player.dir.y * sprite->x
			- map->player.dir.x * sprite->y);
	sprite->transform_y = sprite->inv_det
		* (-map->player.plane.y * sprite->x + map->player.plane.x * sprite->y);
	sprite->screen_x = (int)((WIDTH / 2)
			* (1 + sprite->transform_x / sprite->transform_y));
	sprite->v_move_screen = (int)(VMOVE / sprite->transform_y);
	sprite->size.y = fabs((HEIGHT / sprite->transform_y)) / VDIV;
	sprite->size.x = fabs((HEIGHT / sprite->transform_y)) / UDIV;
}

// speed of the key sprite it's spinning with
void	set_fps_counter(t_sprite *sprite)
{
	sprite->fps++;
	if (sprite->fps > 16)
	{
		sprite->fps = 0;
		sprite->index = 0;
	}
	else if (sprite->fps > 14)
		sprite->index = 7;
	else if (sprite->fps > 12)
		sprite->index = 3;
	else if (sprite->fps > 10)
		sprite->index = 6;
	else if (sprite->fps > 8)
		sprite->index = 2;
	else if (sprite->fps > 6)
		sprite->index = 5;
	else if (sprite->fps > 4)
		sprite->index = 1;
	else if (sprite->fps > 2)
		sprite->index = 4;
}

void	draw_sprite(t_map *map, t_sprite *sprite)
{
	set_fps_counter(sprite);
	sprite->stripe = (int)sprite->draw_start.x;
	while (sprite->stripe++ < (int)sprite->draw_end.x)
	{
		sprite->texture_x = (int)(256 * (sprite->stripe - ((int)-sprite->size.y
						/ 2 + sprite->screen_x)) * 64
				/ (int)sprite->size.y) / 256;
		if ((int)sprite->transform_y > 0 && sprite->transform_y
			< map->z_buffer[sprite->stripe])
		{
			sprite->d_y = sprite->draw_start.y;
			while (sprite->d_y++ < sprite->draw_end.y)
			{
				sprite->d = (sprite->d_y - sprite->v_move_screen) * 256
					- HEIGHT * 128 + sprite->size.y * 128;
				sprite->texture_y = ((sprite->d * 64) / sprite->size.y) / 256;
				sprite->color = get_pixels(sprite, sprite->texture_x,
						sprite->texture_y);
				if ((sprite->color & 0x00FFFFFF) != 0)
					map->buffer[sprite->stripe][sprite->d_y] = sprite->color;
			}
		}
	}
}

uint32_t	get_pixels(t_sprite *sprite, int texture_x, int texture_y)
{
	uint32_t	color;

	color = rgb(sprite->textures[sprite->index]->pixels[64 * texture_y
			* 4 + texture_x * 4],
			sprite->textures[sprite->index]->pixels[64 * texture_y
			* 4 + texture_x * 4 + 1],
			sprite->textures[sprite->index]->pixels[64 * texture_y
			* 4 + texture_x * 4 + 2],
			sprite->textures[sprite->index]->pixels[64 * texture_y * 4
			+ texture_x * 4 + 3]);
	return (color);
}
