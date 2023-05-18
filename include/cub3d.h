/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:00:28 by zstenger          #+#    #+#             */
/*   Updated: 2023/05/18 08:21:11 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// HEADERS
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <float.h>

# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// ERROR MESSAGES
# define TMA "Wrong number of arguments.\n"
# define MALLOC_FAIL "Error! Malloc failed.\n"
# define RGB_IS "The RGB color is out of range, "
# define BAD_DOOR "Error! Png for door is bad.\n"
# define INVALID_MAP "Error! The map is invalid.\n"
# define BAD_FLOOR "Error! Png for floor is bad.\n"
# define BAD_CEILING "Error! Png for ceiling is bad.\n"
# define CANNOT_OPEN "Error! This map cannot be opened.\n"
# define BAD_KEY_PIC "Error! Png for key animation is bad.\n"
# define MISSING_PLAYER "Error! No players found on the map.\n"
# define OUT_OF_RANGE "all numbers must be between 0 and 255.\n"
# define RGB_DUPLICATE "Error! To many rgb values on the map.\n"
# define TOO_MANY_PLAYERS "Error! Too many players on the map.\n"
# define INVALID_CHAR "Error! Map has at least one invalid char: "
# define PLAYER_DUPLICATE "Error! Player duplicates on the map.\n"
# define HOW_TO_LAUNCH "Please launch it as ./cub3d path/to/map.\n"
# define WRONG_ATTRIBUTES "Error! Wrong attributes in the map file.\n"
# define COMMA "Error! The amount of comma in the RGB list is wrong.\n"
# define TEX_FILE_WRONG "Error! The %s texture file cannot be opened.\n"
# define DFS_ERROR "Error! The DFS algorithm found a problem on the map.\n"
# define MISSING_ATTRIBUTES "Error! Attributes are missing form the map.\n"
# define DUPLICATE "Error! Duplicates found on the map for the attributes.\n"
# define WRONG_EXTENSION "Map file has wrong format. It needs .cub format.\n"

// MOVING THE SPRITE ON THE MAP AND SCALE IT
# define UDIV 2
# define VDIV 2
# define VMOVE 222.0

// SIZES FOR MAP CALC
	// MINIMAP_REC
# define R 20
# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_SIZE 260

// MINIMAP OPACITY
# define OPM 255
# define OP_M 200
# define OP_ZERO 0

// SPEED TO MOVE
# define FAST 0.20
# define NORMAL 0.09

// SPEED TO TURN WITH
# define FAST_SPEED 0.14
# define NORMAL_SPEED 0.07

// CHANGE BRIGHTNESS
# define BRIGHT 1
# define FOG 0.05

typedef struct s_vector
{
	double	y;
	double	x;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		angle;
	double		speed;
	bool		speed_is_life;
}	t_player;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	camera;
	t_vector	side_dist;
	double		wall_dist;
	t_vector	delta_dist;
	double		x_hit_point;
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
	mlx_texture_t	*door;
	int				error;
	t_player		*player;
	char			**raw_map;
	int				f_color[3];
	int				c_color[3];
	int				map_length;
	char			**map_copy;
	int				reading_pos;
}	t_mlx_data;

typedef struct s_tex
{
	t_vector	tex;
	double		step;
	double		t_pos;
	uint32_t	color;
	int			d_end;
	int			d_start;
	int			line_height;
}	t_tex;

typedef struct s_fc_tex
{
	int				x;
	int				y;
	int				p;
	mlx_texture_t	*tex;
	mlx_texture_t	*tex2;
	int				tex_x;
	int				tex_y;
	float			pos_z;
	int				cell_x;
	int				cell_y;
	float			floor_x;
	float			floor_y;
	float			f_step_x;
	float			f_step_y;
	float			ray_dir_x0;
	float			ray_dir_y0;
	float			ray_dir_x1;
	float			ray_dir_y1;
	float			row_distance;
}	t_fc_tex;

typedef struct s_sprite
{
	double			x;
	double			y;
	int				d;
	int				d_y;
	t_vector		pos;
	int				fps;
	t_vector		size;
	uint32_t		color;
	int				index;
	int				stripe;
	double			inv_det;
	t_vector		draw_end;
	int				screen_x;
	double			distance;
	int				texture_x;
	int				texture_y;
	t_vector		draw_start;
	double			transform_x;
	double			transform_y;
	mlx_texture_t	*textures[8];
	int				v_move_screen;
}	t_sprite;

typedef struct s_map
{
	int			x;
	int			y;
	t_fc_tex	fc;
	int			hit;
	t_ray		ray;
	t_tex		*tex;
	int			side;
	t_vector	step;
	int			map_x;
	int			map_y;
	int			op_min;
	int			op_mid;
	int			op_max;
	t_player	player;
	t_sprite	sprite;
	bool		has_key;
	mlx_image_t	*img_map;
	mlx_image_t	*img_tmp;
	char		**matrix;
	bool		draw_minimap;
	double		z_buffer[WIDTH];
	int			buffer[WIDTH][HEIGHT];
}	t_map;

typedef struct s_data
{
	mlx_t		*mlx;
	int			mouse_x;
	t_map		*minimap;
	t_mlx_data	*mlx_data;
}	t_data;

// INPUT CHECKS
int				validate_content(char *map_file, t_mlx_data *data);
int				input_check(int argc, char *argv, t_mlx_data *data);
// OBJECT VALIDATING
int				invalid_attribute(char *line);
int				is_duplicate(char *line, t_mlx_data *data);
int				validate_no_so(char *line, t_mlx_data *data);
int				validate_we_ea(char *line, t_mlx_data *data);
int				validate_texture(char *line, t_mlx_data *data);
int				contains_valid_objects(char *line, t_mlx_data *data);
// COLOR VALIDATING
int				valid_rgb(char **rgb);
int				commacounter(char *line);
int				has_duplicate_rgb(char *line);
int				rgb_contains_letters(char *line);
char			**split_rgb(char *line, char *trim_with);
int				validate_color(char *line, t_mlx_data *data);
// SAVE DATA
void			save_color_to_data(char **rgb, t_mlx_data *data, char option);
void			save_texture_to_data(char *file, t_mlx_data *data, char option);
// MAP VALIDATING
char			*get_line(int fd, char *line);
void			set_map_error(t_mlx_data *data);
int				line_has_invalid_chars(char *line);
int				map_checks(t_mlx_data *data, int i);
int				line_cotains_only_spaces(char *line);
void			get_player_pos(char **map, int *py, int *px);
void			dfs(char **map, int y, int x, t_mlx_data *data);
int				map_has_multiple_players_or_none(char c, char option);
int				map_validathor(char *map_file, t_mlx_data *data, int fd);
void			get_map_length(int fd, char *map_file, t_mlx_data *data);
// INPUT UTILS
int				it_can_be_opened(char *file);
char			*copy_map_line(char *content);
void			free_mlx_data_on_error(t_mlx_data *mlx_data);

// INIT MAP
double			get_angle(char c);
int				init_key_images(t_map *map);
int				get_longest_line(char **map);
void			set_plan(t_vector *plane, char c);
char			*init_line(char *old_line, int l);
void			set_player_position(t_map *minimap);
char			**init_matrix(char **map, int height);
t_map			*init_map(t_mlx_data *mlx_data, mlx_t *mlx);

// INIT
t_mlx_data		*init_data(void);
void			init_spirite_position(t_map *map);
void			init_m_textures(t_mlx_data *mlx_data);
int				init(int argc, char **argv, t_data *data);
void			init_textures(t_mlx_data *mlx_data, t_fc_tex *fc);

// RAYCASTING
void			set_ray_distance(t_map *map);
void			draw_map(t_map *minimap, t_mlx_data *mlx_data);
void			empty_map(mlx_image_t *img, t_mlx_data *mlx_data);
void			calculate_the_direction_of_the_ray(t_map *map, int i);
void			cast_the_ray_until_hits_the_wall(t_map *map, int hit);

// DRAW TEXTURE
void			set_tex_struct(t_map *map);
mlx_texture_t	*get_texture(t_map *map, t_mlx_data *mlx_data);
int				get_pixel_color(t_map *map, mlx_texture_t *tex);
void			print_textures(t_map *m, int x, t_mlx_data *mlx_data);
mlx_texture_t	*set_variables(t_map *map, t_mlx_data *mlx_data, int x);
void			draw_buff(mlx_image_t *img_tmp, int32_t buffer[WIDTH][HEIGHT]);

// DRAW_MINIMAP
void			draw_player(t_map *map);
void			draw_rays(t_map *minimap);
void			draw(t_map *map, t_mlx_data *mlx_data, t_vector *p, int i);
void			put_pixels_on_minimap(t_map *m, int i, int k, t_vector *p);
void			visible_map(t_map *m, t_mlx_data *mlx_d, t_vector *p, int i);
void			invisible_map(t_map *m, t_mlx_data *mlx_d, t_vector *p, int i);
void			draw_minimap(t_map *map, t_mlx_data *mlx_d, t_vector *p, int i);

// HOOKS
void			add_hooks(t_data *data);
void			mouse_rotate(void *param);
void			hodor(mlx_key_data_t keydata, void *param);

// DOOR
bool			is_open_door_here(t_map *map);
bool			is_closed_door_here(t_map *map);
void			switch_door(t_map *map, t_mlx_data *mlx_data);

// FLOOR AND CEILING
void			draw_floor_and_ceiling(t_map *map);
void			init_variables_for_y(t_map *map, t_fc_tex *fc, int y);
void			init_variables_for_x(t_map *map, t_fc_tex *fc, int x, int y);

// SPRITES
void			love_norm(t_map *map, t_sprite *sprite);
void			draw_sprite(t_map *map, t_sprite *sprite);
void			calculate_sprite_attributes(t_map *map, t_sprite *sprite);
uint32_t		get_pixels(t_sprite *sprite, int texture_x, int texture_y);

// MOVEMENT
void			move_keys(void *param);
void			is_escape(t_data *data);
void			set_speed(t_player *player);
bool			is_wall(int y, int x, char **matrix);
void			move_up(double y, double x, t_map *map);
void			move_down(double y, double x, t_map *map);
void			move_left(double y, double x, t_map *map);
void			move_right(double y, double x, t_map *map);
void			steps(mlx_key_data_t keydata, t_data *data);
void			is_key_collected(t_map *m, t_player *player, t_sprite *sprite);

// TURN L/R & MOUSE
void			turn_left(t_data *data, t_player *playr);
void			turn_right(t_data *data, t_player *player);

// UTILS
void			free_data(t_data *data);
char			*dup3(int size, char ch);
void			free_char_array(char **array);
uint32_t		rgb(int r, int g, int b, int a);
char			**copy_2d_char_array(char **array);
char			*ft_strdup2(char *str, int start, int end);

// FOR PRINTING THE MAP
// char			put_chars(char c);
// void			print_map_objects(t_mlx_data *data);
// void			ft_print_2d_char_array(char **array_2d);

#endif