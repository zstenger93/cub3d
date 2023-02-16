/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:28 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/16 17:00:30 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TRUE 1
# define FALSE 0

# define WRONG_INPUT ""
# define EXTENSION ""

typedef struct s_map
{
	char	*input;
    char	**full_map;
    char	*north;
    char	*west;
    char	*south;
    char	*east;
}   t_map;

typedef struct s_coord
{
	char	*player;
	char	*enemy;
	char	*door;
	char	*teleport;
	char	*chest;
}	t_coord;

typedef struct s_nightmode
{

}	t_nightmode;

typedef struct s_image
{
		*player;
		*enemy;
}	t_image;

typedef struct s_texture
{
		*player;
		*enemy;
}	t_texture;

# include "../libft/includes/libft.h"

int	input_check(int argc, char **argv);


#endif