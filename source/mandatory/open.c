/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:17:59 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/05 15:18:28 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

mlx_t *open_mapsize_window(char *map, int count)
{	
	mlx_t	*mlx;
	int		x;
	int		y;
	int		fd;
	char	*buffer;

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