/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:28:42 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/05 14:30:02 by aychikhi         ###   ########.fr       */
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

char	**ft_split(char *str)
{
	int		i;
	int		j;
	int		w;
	int		c;
	char	**ptr;

	i = 0;
	w = 0;
	c = count_word(str);
	ptr = malloc((c + 1) * sizeof(char *));
	while (str[i])
	{
		j = 0;
		while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			i++;
		while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
		{
			j++;
			i++;
		}
		ptr[w] = malloc((j + 1));
		ptr[w] = ft_strcpy1(ptr[w], str, i - j);
		w++;
	}
	ptr[c] = NULL;
	return (ptr);
}
