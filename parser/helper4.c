/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:10:01 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/06 12:18:14 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	free_map_list(t_list *map)
{
	t_list	*current;
	t_list	*next;

	current = map;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

void	free_config(t_config *data)
{
	int	i;

	free(data->no);
	free(data->so);
	free(data->we);
	free(data->ea);
	free_map_list(data->map);
	i = 0;
	if (data->array_map)
	{
		while (data->array_map[i])
		{
			free(data->array_map[i]);
			i++;
		}
	}
	free(data->array_map);
}

int	is_valide(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& !ft_isspace(c))
		return (0);
	return (1);
}

int	check_line_is_valide(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_valide(str[i]))
		{
			printf("%s\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	check_map(char *str, t_config *data)
{
	char	*line_copy;
	size_t	len;

	if (!check_spaces(str) && data->flags.in_map)
		print_error();
	if (!check_spaces(str))
		return ;
	if (check_line_is_valide(str))
	{
		data->flags.in_map = 1;
		line_copy = ft_strdup(str);
		if (!line_copy)
			print_error();
		len = ft_strlen(line_copy);
		if (len > 0 && line_copy[len - 1] == '\n')
			line_copy[len - 1] = '\0';
		if (!data->map)
			data->map = ft_lstnew(line_copy);
		else
			ft_lstadd_back(&data->map, ft_lstnew(line_copy));
	}
}
