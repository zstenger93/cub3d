/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:18 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/16 17:16:44 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	input_check(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_strstr(argv[1], ".cub") == 0)
			return (1);
		else
			return (0);
	}
	return (0);
}