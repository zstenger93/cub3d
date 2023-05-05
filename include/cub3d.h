/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:28 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/05 07:08:24 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>

# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h" 


# define TOGGLE_MINIMAP "M"

# define SPACES " \t\n\v\r\f"

# define WIDTH 5120
# define HEIGHT 2880
# define MINIMAP_REC 20
# define MINIMAP_SIZE 160

typedef struct s_player
{
	double	y; // [8][8], y = 6, x =3
	double	x;
}	t_player;

typedef struct s_minimap
{
	mlx_image_t *map;
	int			width;
	int			height;
	char		**matrix;
	t_player	player;
	
	
}	t_minimap;

typedef struct s_data
{
	mlx_t		*mlx;
	t_minimap	*minimap;
}	t_data;

typedef struct s_mlx_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**raw_map;
	int		reading_pos;
	int		map_length;
	t_player	*player;
	char	**map_copy;
	
}	t_mlx_data;








// typedef struct s_map
// {
// 	char	*input;
//     char	**full_map;
//     char	*north;
//     char	*west;
//     char	*south;
//     char	*east;
// }   t_map;

// typedef struct s_coord
// {
// 	char	*player;
// 	char	*enemy;
// 	char	*door;
// 	char	*teleport;
// 	char	*chest;
// }	t_coord;

// typedef struct s_image
// {
// 		*player;
// 		*enemy;
// }	t_image;

// typedef struct s_texture
// {
// 		*player;
// 		*enemy;
// }	t_texture;



// INPUT CHECKS
int			input_check(int argc, char *argv, t_mlx_data *data);
int			validate_content(char *map_file, t_mlx_data *data);
int	contains_valid_objects(char *line, t_mlx_data *data);
int	is_duplicate(char *line, t_mlx_data *data);
int	validate_texture(char *line, t_mlx_data *data);
int	it_can_be_opened(char *file);
void	save_texture_to_data(char *file, t_mlx_data *data, char option);
int	validate_color(char *line, t_mlx_data *data);
int	commacounter(char *line);
int	valid_rgb(char **rgb);
int	rgb_contains_letters(char *line);
void	save_color_to_data(char **rgb, t_mlx_data *data, char option);
int	map_validathor(char *map_file, t_mlx_data *data, int fd);
int	line_cotains_only_spaces(char *line);
int	line_has_invalid_chars(char *line);
void	get_map_length(int fd, char *map_file, t_mlx_data *data);


int	dfs(char **map, int y, int x, int rows, t_mlx_data *data);
int	map_checks(t_mlx_data *data);




int			get_width_of_map(int fd);
int			get_height_of_map(int fd);
char		**get_matrix(t_minimap *minimap, int fd);
uint32_t	 get_rgba(int r, int g, int b, int a);


// INIT_MINIMAP
t_minimap*	init_minimap(mlx_t *mlx, char *map);
void		set_player_position(t_minimap *minimap, char **map);

// DRAW_MINIMAP
void		draw_minimap(t_minimap *minimap);
void		draw_player(t_minimap *minimap);

// HOOKS
void		add_hooks(t_data *data);

// UTILS
void	free_char_array(char **array);
char	*copy_map_line(char *content);
char	**copy_2d_char_array(char **array);


// FOR TESTING
void	print_map_objects(t_mlx_data *data);
void	ft_print_2d_char_array(char **array_2d);
char	put_chars(char c);
#endif