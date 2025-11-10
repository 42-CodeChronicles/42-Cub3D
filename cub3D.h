/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:09:59 by aychikhi          #+#    #+#             */
/*   Updated: 2025/11/10 01:28:14 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

// #### WINDOW DIMENSIONS ###
# define W_WIDTH 800
# define W_HEIGHT 600

# define TILE_SIZE 64
# define MINIMAP_TILES 17
# define MINIMAP_SIZE (MINIMAP_TILES * TILE_SIZE)
// #define TILE_SIZE 10
// #define DOT_SIZE 4
// #define MINIMAP_TILES 9

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define WALL_HEIGHT 64
# define NUM_RAYS SCREEN_WIDTH
# define FOV 60

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

// ##########################

# include "./MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_sprite
{
	double			x;
	double			y;
	mlx_texture_t	**frames;
	int				frame_count;
	int				current_frame;
	double			frame_time;
	double			last_update;
}					t_sprite;

typedef struct s_weapon
{
	mlx_texture_t	**frames;
	int				frame_count;
	int				current_frame;
	int				is_shooting;
	double			frame_time;
	double			last_update;
}					t_weapon;

typedef struct s_tex_data
{
	mlx_texture_t	*texture;
	int				tex_x;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
}					t_tex_data;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
}					t_mlx;

typedef struct s_wall
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				color;
	int				tex_start_offset;
}					t_wall;

typedef struct s_wall_pos
{
	double			wall_x;
	int				map_x;
	int				map_y;
}					t_wall_pos;

typedef struct s_door
{
	int				x;
	int				y;
	int				is_open;
	double			open_amount;
}					t_door;

typedef struct s_flags
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				f;
	int				c;
	int				in_map;
}					t_flags;

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;

typedef struct s_point
{
	double			x;
	double			y;
	double			angle;
	int				flag;
}					t_point;

typedef struct s_ray
{
	double			angle;
	double			distance;
	int				hit_vertical;
}					t_ray;

typedef struct s_map
{
	char			**array_map;
	int				height;
	int				width;
	t_point			player_pos;
	char			player_dir;
}					t_map;

typedef struct s_config
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	int				f[3];
	int				c[3];
	t_flags			flags;
	t_map			map;
	mlx_image_t		*minimap_image;
	mlx_image_t		*view_3d;
	mlx_t			*mlx_ptr;
	int				wall_side;
	t_door			*doors;
	int				door_count;
	mlx_texture_t	*door_texture;
	t_sprite		*sprites;
	int				sprite_count;
	t_weapon		weapon;
}					t_config;

typedef struct s_draw_params
{
	int				x;
	t_wall			*wall;
	t_config		*data;
	t_wall_pos		*pos;
}					t_draw_params;

int					cube(char *str);
int					ft_isspace(int c);
void				print_error(void);
int					is_valide(char c);
int					ft_isdigit(int c);
long				ft_atoi(char *str);
char				**ft_split(char *s);
int					check_num(char *ptr);
void				print_error_map(void);
int					array_len(char **tab);
t_list				*ft_lstnew(void *str);
char				*get_next_line(int fd);
int					ft_lstsize(t_list *lst);
int					check_spaces(char *str);
void				free_array(char **array);
void				init_doors(t_config *data);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *str);
void				free_map_list(t_list **map);
int					check_config(t_flags flags);
void				sprite_init(t_config *data);
void				free_config(t_config *data);
void				load_texture(t_config *data);
int					validate_map(t_config *data);
int					check_line_is_valide(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strchr(const char *s, int c);
void				parse_map(int fd, t_config *data);
char				**ft_split2(char const *s, char c);
int					parse_config(int fd, t_config *data);
void				check_line(char *str, t_config *data);
void				handle_rgb(char *str, t_config *data);
void				free_map_copy(char **map, int height);
void				*ft_memset(void *ptr, int x, size_t n);
void				lst_to_2d(t_config **data, t_list *map);
int					check_door(t_config *data, int x, int y);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_strcmp(const char *s1, const char *s2);
void				handle_texture(char *str, t_config *data);
mlx_texture_t		*get_texture(t_config *data, int y, int x);
char				*ft_strtrim(char const *s1, char const *set);
t_door				*get_door_state(t_config *data, int x, int y);
void				check_map(char *str, t_config *data, t_list **map);
void				ft_strcpy(char *dest, const char *src, size_t len);
uint32_t			get_texture_color(mlx_texture_t *texture, int tex_x,
						int tex_y);
void				get_weapon_dimensions(mlx_texture_t *texture, int *w,
						int *h);
void				flood_fill(char **map, int x, int y, t_map *map_data);
double				get_sprite_distance(t_config *data, t_sprite *sprite);
t_sprite			*created_sprite(double x, double y, char **frame_path,
						int count);
void				update_all_sprites(t_config *data, double current_time);
void				get_weapon_position(int weapon_width, int weapon_height,
						int *start_x, int *start_y);
char				*ft_substr(const char *s, unsigned int start, size_t len);
void				update_sprite_frame(t_sprite *sprite, double current_time);
void				draw_sprite(mlx_image_t *img, t_config *data,
						t_sprite *sprite);
void				weapon_init(t_config *data);
void				draw_weapon(mlx_image_t *img, t_config *data);
void				update_weapon_frame(t_weapon *weapon, double current_time);

// ### ayaarab's functions ###

// Minimap core
void				init_minimap(t_config *data);
void				handle_key(void *param);

// Minimap utils
void				draw_tile(mlx_image_t *img, int x, int y, int color);
int					is_valid_pos(t_config *data, int x, int y);
int					check_collision(t_config *data, int new_x, int new_y);
void				normalize_angle(double *angle);

// Minimap draw
void				draw_player_dot(mlx_image_t *img, int x, int y);
void				draw_line_dda(mlx_image_t *img, t_config *data,
						double angle, double distance, int color);
void				draw_direction_line(mlx_image_t *img, t_config *data);
void				draw_minimap(mlx_image_t *minimap_image, t_config *data);

// Minimap init
void				init_angle(t_config *data);
void				init_values(t_config *data);

// Rays - Ray casting functions
double				cast_ray(t_config *data, double ray_angle,
						int *hit_vertical, double *wall_x, int *map_x,
						int *map_y);
void				cast_all_rays(mlx_image_t *img, t_config *data);
// 3D View
void				render_3d_view(mlx_image_t *img, t_config *data);
void				calculate_wall_height(t_wall *wall, double distance,
						double ray_angle, t_config *data);
void				draw_wall_slice_texture(mlx_image_t *img,
						t_draw_params *params);

// ##########################
#endif