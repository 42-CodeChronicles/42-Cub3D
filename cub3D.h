/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:09:59 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/06 15:41:24 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include "./MLX/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	int				x;
	int				y;
	int				flag;
}					t_point;

typedef struct s_map
{
	char			**array_map;
	int				height;
	int				weight;
	t_point			player_pos;
	char			player_dir;
}					t_map;

typedef struct s_config
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f[3];
	int				c[3];
	t_flags			flags;
	t_map			map;
}					t_config;

void				cube(char *str);
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
char				*ft_strdup(const char *s1);
void				free_map_list(t_list **map);
size_t				ft_strlen(const char *str);
int					check_config(t_flags flags);
void				free_config(t_config *data);
int					check_line_is_valide(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strchr(const char *s, int c);
char				**ft_split2(char const *s, char c);
void				check_line(char *str, t_config *data);
void				handle_rgb(char *str, t_config *data);
void				*ft_memset(void *ptr, int x, size_t n);
void				lst_to_2d(t_config **data, t_list *map);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_strcmp(const char *s1, const char *s2);
void				handle_texture(char *str, t_config *data);
char				*ft_strtrim(char const *s1, char const *set);
void				check_map(char *str, t_config *data, t_list **map);
void				ft_strcpy(char *dest, const char *src, size_t len);
char				*ft_substr(const char *s, unsigned int start, size_t len);

#endif