/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:28:42 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/05 15:09:10 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	count_word(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			i++;
		if (str[i])
			c++;
		while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
			i++;
	}
	return (c);
}

static char	*ft_strcpy1(char *dest, char *src, int index)
{
	int	i;

	i = 0;
	while (src[index] && src[index] != ' ' && src[index] != '\n'
		&& src[index] != '\t')
	{
		dest[i] = src[index];
		index++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		i++;
	return (i);
}

static int	get_word_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char *str)
{
	int		i;
	int		w;
	int		word_len;
	char	**ptr;

	i = 0;
	w = 0;
	ptr = malloc((count_word(str) + 1) * sizeof(char *));
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (!str[i])
			break ;
		word_len = get_word_len(str, i);
		ptr[w] = malloc(word_len + 1);
		ptr[w] = ft_strcpy1(ptr[w], str, i);
		i += word_len;
		w++;
	}
	ptr[w] = NULL;
	return (ptr);
}
