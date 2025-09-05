/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:09:59 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/05 14:47:43 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_flags
{
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		F;
	int		C;
}			t_flags;

typedef struct s_game
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F[3];
	int		C[3];
	char	**map;
}			t_game;

int			ft_isspace(int c);
void		print_error(void);
int			ft_isdigit(int c);
long		ft_atoi(char *str);
char		**ft_split(char *s);
void		check_line(char *str);
char		*get_next_line(int fd);
int			check_spaces(char *str);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		**ft_split2(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_strcpy(char *dest, const char *src, size_t len);
void		handle_texture(char *str, t_game *data, t_flags *flags);
char		*ft_substr(const char *s, unsigned int start, size_t len);

#endif