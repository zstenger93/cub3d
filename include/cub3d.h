/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:28 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/12 13:14:29 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// HEADERS
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <float.h>

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"

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
	// MINIMAP_REC
# define R 20
# define WIDTH 2560
# define HEIGHT 1440
# define MINIMAP_SIZE 320

typedef struct s_vector
{
	double	y;// [8][8], y = 6, x =3
	double	x;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		angle;
	double		speed;
}	t_player;

typedef struct s_ray
{
	double		x_hit_point;
	t_vector	dir;
	t_vector	camera;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		wall_dist;
}	t_ray;

typedef struct s_mlx_data
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	mlx_texture_t	*t_no;
	mlx_texture_t	*t_so;
	mlx_texture_t	*t_we;
	mlx_texture_t	*t_ea;
	mlx_texture_t	*texture;
	int				error; // flag for input check from dfs in case the map is wrong
	t_player		*player;
	char			**raw_map; // map copied from the file
	int				map_length; // heigth of the map
	char			**map_copy; // raw map copy for dfs
	int				reading_pos; // actual map reading starts from here
	int				f_color[3];
	int				c_color[3];
}	t_mlx_data;

typedef struct s_tex
{
	double		step;
	double		t_pos;
	int			line_height;
	t_vector	tex;
	int			color;
	int			d_start;
	int			d_end;
}	t_tex;

typedef struct s_map
{
	int			buffer[WIDTH][HEIGHT];
	t_tex		*tex;
	t_ray		ray;
	int			side;
	t_vector	step;
	int			map_x;
	int			map_y;
	t_player	player;
	mlx_image_t	*img_map;
	mlx_image_t	*img_tmp;
	char		**matrix;
}	t_map;

typedef struct s_data
{
	int			mouse_x;
	mlx_t		*mlx;
	t_map		*minimap;
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

// INIT MAP
double		get_angle(char c);
int			get_longest_line(char **map);
void		set_plan(t_vector *plane, char c);
char		*init_line(char *old_line, int l);
void		set_player_position(t_map *minimap);
char		**init_matrix(char **map, int height);
t_map		*init_map(t_mlx_data *mlx_data, mlx_t *mlx);

// INIT
t_mlx_data	*init_data(void);
void		init_textures(t_mlx_data *mlx_data);
int			init(int argc, char **argv, t_data *data);

// RAYCASTING
void		draw_map(t_map *minimap, t_mlx_data *mlx_data);
void		empty_map(mlx_image_t *img, t_mlx_data *mlx_data);
void		set_ray_distance(t_map *map);
void		calculate_the_direction_of_the_ray(t_map *map, int i);
void		cast_the_ray_until_hits_the_wall(t_map *map, int hit);

// DRAW TEXTURE
void		print_textures(t_map *minimap, int i, t_mlx_data *mlx_data);
void		print_vertical_lines(t_map *m, int i);

// DRAW_MINIMAP
void		draw_rays(t_map *minimap);
void		draw_player(t_map *minimap);
void		draw(t_map *map, t_mlx_data *mlx_data);
void		draw_minimap(t_map *minimap, t_mlx_data *mlx_d, t_vector *p, int i);

// HOOKS
void		add_hooks(t_data *data);

// MOVEMENT
void		move_keys(void *param);
bool		is_wall(int y, int x, char **matrix);
void		move_up(double y, double x, t_map *map);
void		move_down(double y, double x, t_map *map);
void		move_left(double y, double x, t_map *map);
void		move_right(double y, double x, t_map *map);

// TURN L/R & MOUSE
void		mouse_rotate(void *param);
void		turn_left(t_data *data, t_player *playr);
void		turn_right(t_data *data, t_player *player);

// UTILS
char		*dup3(int size, char ch);
void		free_char_array(char **array);
char		**copy_2d_char_array(char **array);
uint32_t	rgb(int r, int g, int b, int a);
char		*ft_strdup2(char *str, int start, int end);





void	print_textures(t_map *m, int x, t_mlx_data *mlx_data);
mlx_texture_t	*get_texture(t_map *map, t_mlx_data *mlx_data);
mlx_texture_t	*set_variables(t_map *map, t_mlx_data *mlx_data, int x);
int	get_pixel_color(t_map *map, mlx_texture_t *tex);
void	draw_buff(mlx_image_t *img_tmp, int32_t buffer[WIDTH][HEIGHT]);
void	set_tex_struct(t_map *map);



// FOR TESTING
void		write2(int n);
char		put_chars(char c);
char		*double_to_string(double num);
void		print_map_objects(t_mlx_data *data);
void		ft_print_2d_char_array(char **array_2d);

#endif