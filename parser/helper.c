/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:19:33 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/06 12:19:51 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

static int	parse_config(int fd, t_config *data)
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

static void	parse_map(int fd, t_config *data)
{
	char	*str;

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		check_map(str, data);
		free(str);
	}
}

void	cube(char *str)
{
	int			fd;
	t_config	data;

	ft_memset(&data, 0, sizeof(t_config));
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	if (!parse_config(fd, &data))
		return ;
	parse_map(fd, &data);
	close(fd);
	free_config(&data);
}
