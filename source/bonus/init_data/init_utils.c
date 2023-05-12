/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:06:07 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/10 16:21:25 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	get_longest_line(char **map)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (map[i] != NULL)
	{
		if (result < ft_strlen(map[i]))
			result = ft_strlen(map[i]);
		i++;
	}
	return (result);
}

char	*dup3(int size, char ch)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	while (i != size)
	{
		str[i] = ch;
		i++;
	}
	return (str);
}

double	get_angle(char c)
{
	if (c == 'S')
		return (M_PI_2);
	if (c == 'W')
		return (0);
	if (c == 'N')
		return (M_PI + M_PI_2);
	return (M_PI * 2);
}

void	set_plan(t_vector *plane, char c)
{
	if (c == 'N')
	{
		plane->y = 0;
		plane->x = 1;
	}
	if (c == 'S')
	{
		plane->y = 0;
		plane->x = -1;
	}
	if (c == 'W')
	{
		plane->y = -1;
		plane->x = 0;
	}
	if (c == 'E')
	{
		plane->y = 1;
		plane->x = 0;
	}
}
