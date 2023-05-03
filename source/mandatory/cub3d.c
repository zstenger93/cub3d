/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:49 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/03 17:30:06 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

mlx_t *open_mapsize_window(char *map, int count)
{	
	mlx_t *mlx;
	int x;
	int y;
	int fd;
	char *buffer;

	fd = open(map, O_RDWR);
	buffer = get_next_line(fd);
	y = 0;
	while (buffer != 0) {
		x = 0;
		while (buffer[count] != '\n' && buffer[count] != '\0') count++;
		x = count;
		count = 0;
		y++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	mlx = mlx_init(x * 64, y * 64, "Survive The NORM", 1);
	return (mlx);
}

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

void	draw_player(t_minimap *minimap)
{
	int	y;
	int	x;
	int	i;
	int	k;

	y = (minimap->player.y * 20) - 10;
	x = (minimap->player.x * 20) - 10;
	i = 0;
	while (i < 5)
	{
		k = 0;
		while (k < 5)
		{
			mlx_put_pixel(minimap->map, x + k, y + i, get_rgba(0, 255, 0, 255));
			k++;
		}
		i++;
	}
}

void	draw_minimap(t_minimap *minimap)
{
	int	i;
	int	k;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		k = 0;
		while (k < MINIMAP_SIZE)
		{
			if (((k % 20 == 0 || i % 20 == 0) && minimap->matrix[i / MINIMAP_REC][k / MINIMAP_REC] == '1') ||
			((k % 20 == 0 || i % 20 == 0) && minimap->matrix[(i - 1 )/ MINIMAP_REC][(k - 1) / MINIMAP_REC] == '1'))
				mlx_put_pixel(minimap->map, k, i, get_rgba(50, 50, 50, 255));
			else
				mlx_put_pixel(minimap->map, k, i, get_rgba(250, 50, 50, 255));
			k++;
		}
		i++;
	}
	draw_player(minimap);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
  	mlx_t *mlx;
	t_mlx_data	*data;
	t_minimap	*minimap;


	if (input_check(argc, argv[1], data) == false)
		return (EXIT_FAILURE);
	mlx = mlx_init(WIDTH, HEIGHT, "Survive The NORM", 1);
	minimap = init_minimap(mlx, argv[1]);
	
	
	draw_minimap(minimap);
	mlx_image_to_window(mlx, minimap->map, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
