/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:28 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/08 12:04:33 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// HEADERS
# include <fcntl.h>
# include <stdio.h>
# include <stdio.h>
# include <math.h>
# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h" 

// ERROR MESSAGES
# define TMA "Wrong number of arguments.\n"
# define RGB_IS "The RGB color is out of range, "
# define OUT_OF_RANGE "all numbers must be between 0 and 255.\n"
# define INVALID_CHAR "Error! Map has at least one invalid char: "
# define HOW_TO_LAUNCH "Please launch it as ./cub3d path/to/map.\n"
# define COMMA "Error! The amount of comma in the RGB list is wrong.\n"
# define DUPLICATE "Error! Duplicates found on the map for the attributes.\n"
# define WRONG_EXTENSION "Map file has wrong format. It needs .cub format.\n"

// MISC
# define TOGGLE_MINIMAP "M"
# define SPACES " \t\n\v\r\f"

// SIZES FOR MAP CALC
# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_REC 20
# define MINIMAP_SIZE 420



typedef struct s_img
{
	mlx_image_t	*minimap_wall;
}	t_img;

typedef struct s_txt
{
	mlx_image_t	minimap_wall;
}	t_txt;

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
	double		angle;
}	t_player;

typedef struct s_ray
{
	t_vector	camera;
	t_vector	dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		wall_dist;
}	t_ray;

typedef struct s_minimap
{
	mlx_image_t *img_map;
	mlx_image_t *img_tmp;
	char		**matrix;
	t_player	player;
	t_ray		ray;
}	t_minimap;

typedef struct s_mlx_data
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			error;// flag for input check from dfs in case the map is wrong
	t_player	*player;
	char		**raw_map;// map copied from the file
	int			map_length;// heigth of the map
	char		**map_copy;// raw map copy for dfs
	int			reading_pos;// actual map reading starts from here
	int			floor_color[3];
	int			ceiling_color[3];
}	t_mlx_data;

typedef struct s_data
{
	t_img		*images;
	mlx_t		*mlx;
	t_minimap	*minimap;
	t_mlx_data	*mlx_data;
}	t_data;

// INPUT CHECKS
int			validate_content(char *map_file, t_mlx_data *data);
int			input_check(int argc, char *argv, t_mlx_data *data);
	// OBJECT VALIDATING
int			invalid_attribute(char *line);
int			is_duplicate(char *line, t_mlx_data *data);
int			validate_no_so(char *line, t_mlx_data *data);
int			validate_we_ea(char *line, t_mlx_data *data);
int			validate_texture(char *line, t_mlx_data *data);
int			contains_valid_objects(char *line, t_mlx_data *data);
	// COLOR VALIDATING
int			valid_rgb(char **rgb);
int			commacounter(char *line);
int			has_duplicate_rgb(char *line);
int			rgb_contains_letters(char *line);
char		**split_rgb(char *line, char *trim_with);
int			validate_color(char *line, t_mlx_data *data);
	// SAVE DATA
void		save_color_to_data(char **rgb, t_mlx_data *data, char option);
void		save_texture_to_data(char *file, t_mlx_data *data, char option);
	// MAP VALIDATING
void		set_map_error(t_mlx_data *data);
int			line_has_invalid_chars(char *line);
int			map_checks(t_mlx_data *data, int i);
int			line_cotains_only_spaces(char *line);
void		dfs(char **map, int y, int x, t_mlx_data *data);
int			map_has_multiple_players_or_none(char c, char option);
int			map_validathor(char *map_file, t_mlx_data *data, int fd);
void		get_map_length(int fd, char *map_file, t_mlx_data *data);
	// INPUT UTILS
int			it_can_be_opened(char *file);
char		*copy_map_line(char *content);

// INIT_MINIMAP
void		set_player_position(t_minimap *minimap);
t_minimap*	init_minimap(t_mlx_data *mlx_data, mlx_t *mlx);

// DRAW_MINIMAP
void		draw_player(t_minimap *minimap);
void		draw_minimap(t_minimap *minimap, t_mlx_data *mlx_data);

// HOOKS
void		add_hooks(t_data *data);

// UTILS
void		free_char_array(char **array);
char		**copy_2d_char_array(char **array);
uint32_t	get_rgba(int r, int g, int b, int a);
char		*ft_strdup2(char *str, int start, int end);

// FOR TESTING
char		put_chars(char c);
void		print_map_objects(t_mlx_data *data);
void		ft_print_2d_char_array(char **array_2d);



void	draw_rays(t_minimap *minimap);
void    draw_map(t_minimap *minimap);



void	write2(int n);
char *double_to_string(double num);

#endif