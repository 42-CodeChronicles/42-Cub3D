/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:52:52 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/06 18:02:11 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_map_copy(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	parse_config(int fd, t_config *data)
{
	char	*str;

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			return (0);
		if (check_spaces(str))
			check_line(str, data);
		if (!check_config(data->flags))
		{
			free(str);
			return (1);
		}
		free(str);
	}
}

void	parse_map(int fd, t_config *data)
{
	char	*str;
	t_list	*map;

	map = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		check_map(str, data, &map);
		free(str);
	}
	if (ft_lstsize(map) == 0)
		print_error_map();
	lst_to_2d(&data, map);
	free_map_list(&map);
}

void	check_line(char *str, t_config *data)
{
	char	**array;

	array = ft_split(str);
	if (!ft_strcmp(array[0], "WE") || !ft_strcmp(array[0], "EA")
		|| !ft_strcmp(array[0], "NO") || !ft_strcmp(array[0], "SO"))
		handle_texture(str, data);
	else if (!ft_strcmp(array[0], "F") || !ft_strcmp(array[0], "C"))
		handle_rgb(str, data);
	else
		print_error();
	free_array(array);
}

int	check_config(t_flags flags)
{
	if (!flags.ea || !flags.no || !flags.so || !flags.we || !flags.c
		|| !flags.f)
		return (1);
	return (0);
}
