/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:28 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/06 15:25:17 by jergashe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdio.h>

# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h" 

# define COMMA "Error! The amount of comma in the RGB list is wrong.\n"
# define RGB_IS "The RGB color is out of range, "
# define OUT_OF_RANGE "all numbers must be between 0 and 255.\n"
# define DUPLICATE "Error! Duplicates found on the map for the attributes.\n"
# define TMA "Wrong number of arguments.\n"
# define HOW_TO_LAUNCH "Please launch it as ./cub3d path/to/map.\n"
# define INVALID_CHAR "Error! Map has at least one invalid char: "
# define WRONG_EXTENSION "Map file has wrong format. It needs .ber format.\n"

# define TOGGLE_MINIMAP "M"

# define SPACES " \t\n\v\r\f"

# define WIDTH 5120
# define HEIGHT 2880
# define MINIMAP_REC 20
# define MINIMAP_SIZE 1020



typedef struct s_vector
{
	double	y; // [8][8], y = 6, x =3
	double	x;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_minimap
{
	mlx_image_t *img_map;
	char		**matrix;
	t_player	player;
}	t_minimap;

typedef struct s_mlx_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**raw_map;// map copied from the file
	int		reading_pos;// actual map reading starts from here
	int		map_length;// heigth of the map
	t_player	*player;
	char	**map_copy;// raw map copy for dfs
	int		error;// flag for input check from dfs in case the map is wrong
}	t_mlx_data;

typedef struct s_data
{
	mlx_t		*mlx;
	t_minimap	*minimap;
	t_mlx_data	*mlx_data;
	
}	t_data;







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
	// OBJECT VALIDATING
int			contains_valid_objects(char *line, t_mlx_data *data);
int			is_duplicate(char *line, t_mlx_data *data);
int			validate_texture(char *line, t_mlx_data *data);
int			validate_no_so(char *line, t_mlx_data *data);
int			validate_we_ea(char *line, t_mlx_data *data);
	// COLOR VALIDATING
int			valid_rgb(char **rgb);
int			commacounter(char *line);
int			has_duplicate_rgb(char *line);
int			rgb_contains_letters(char *line);
char		**split_rgb(char *line, char *trim_with);
int			validate_color(char *line, t_mlx_data *data);
	// SAVE DATA
void		save_texture_to_data(char *file, t_mlx_data *data, char option);
void		save_color_to_data(char **rgb, t_mlx_data *data, char option);
	// MAP VALIDATING
int			map_validathor(char *map_file, t_mlx_data *data, int fd);
void		get_map_length(int fd, char *map_file, t_mlx_data *data);
int			line_cotains_only_spaces(char *line);
int			line_has_invalid_chars(char *line);
void		map_checks(t_mlx_data *data);
void		set_map_error(t_mlx_data *data);
void		dfs(char **map, int y, int x, t_mlx_data *data);
int			map_has_multiple_players_or_none(char c);
	// INPUT UTILS
int			it_can_be_opened(char *file);

// INIT_MINIMAP
t_minimap*	init_minimap(t_mlx_data *mlx_data, mlx_t *mlx);
void		set_player_position(t_minimap *minimap);

// DRAW_MINIMAP
void		draw_minimap(t_minimap *minimap, t_mlx_data *mlx_data);
void		draw_player(t_minimap *minimap);

// HOOKS
void		add_hooks(t_data *data);

// UTILS
void		free_char_array(char **array);
char		*copy_map_line(char *content);
char		**copy_2d_char_array(char **array);
char		*ft_strdup2(char *str, int start, int end);


// FOR TESTING
void		print_map_objects(t_mlx_data *data);
void		ft_print_2d_char_array(char **array_2d);
char		put_chars(char c);

int			get_width_of_map(int fd);
int			get_height_of_map(int fd);
char		**get_matrix(t_minimap *minimap, int fd);
uint32_t	 get_rgba(int r, int g, int b, int a);

// FOR TESTING
void		print_map_objects(t_mlx_data *data);
void		ft_print_2d_char_array(char **array_2d);
char		put_chars(char c);

#endif