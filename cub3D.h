/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:09:59 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/04 17:25:46 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int F;
	int C;
	char **map;
}	t_game;

void	print_error(void);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_strcpy(char *dest, const char *src, size_t len);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif