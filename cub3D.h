/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:09:59 by aychikhi          #+#    #+#             */
/*   Updated: 2025/11/06 16:28:05 by aychikhi         ###   ########.fr       */
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

# define TILE_SIZE 32
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
# include <unistd.h>

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

typedef struct s_draw_params
{
	int				x;
	t_wall			*wall;
	t_config		*data;
	t_wall_pos		*pos;
}					t_draw_params;

typedef struct s_door
{
	int		x;
	int		y;
	int		is_open;
	double	open_amount;
}			t_door;

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
}					t_config;

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
t_door *get_door_state(t_config *data, int x, int y);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_strcmp(const char *s1, const char *s2);
void				handle_texture(char *str, t_config *data);
char				*ft_strtrim(char const *s1, char const *set);
void				check_map(char *str, t_config *data, t_list **map);
void				ft_strcpy(char *dest, const char *src, size_t len);
void				flood_fill(char **map, int x, int y, t_map *map_data);
char				*ft_substr(const char *s, unsigned int start, size_t len);

// ### ayaarab's functions ###

// Minimap core
void				init_minimap(t_config data);
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
						int *hit_vertical, double *wall_x,
						int *map_x, int *map_y);
void				cast_all_rays(mlx_image_t *img, t_config *data);
// 3D View
void				render_3d_view(mlx_image_t *img, t_config *data);
void				calculate_wall_height(t_wall *wall, double distance,
						double ray_angle, t_config *data);
void				draw_wall_slice_texture(mlx_image_t *img,
						t_draw_params *params);

// ##########################
#endif