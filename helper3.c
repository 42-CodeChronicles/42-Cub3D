/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:23:52 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/05 15:26:21 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_texture(char **texture, int *flag, char *path)
{
	if (*flag)
		print_error();
	*texture = ft_strdup(path);
	*flag = 1;
}

static void	handle_north_south(char **array, t_config *data, t_flags *flags,
		char *direction)
{
	if (array_len(array) != 2)
		print_error();
	if (!ft_strcmp(direction, "NO"))
		set_texture(&data->no, &flags->no, array[1]);
	else if (!ft_strcmp(direction, "SO"))
		set_texture(&data->so, &flags->so, array[1]);
}

static void	handle_west_east(char **array, t_config *data, t_flags *flags,
		char *direction)
{
	if (array_len(array) != 2)
		print_error();
	if (!ft_strcmp(direction, "WE"))
		set_texture(&data->we, &flags->we, array[1]);
	else if (!ft_strcmp(direction, "EA"))
		set_texture(&data->ea, &flags->ea, array[1]);
}

void	handle_texture(char *str, t_config *data, t_flags *flags)
{
	char	**array;

	array = ft_split(str);
	if (array_len(array) != 2)
		print_error();
	if (!ft_strcmp(array[0], "NO") || !ft_strcmp(array[0], "SO"))
		handle_north_south(array, data, flags, array[0]);
	else if (!ft_strcmp(array[0], "WE") || !ft_strcmp(array[0], "EA"))
		handle_west_east(array, data, flags, array[0]);
}

// void	handle_texture(char *str, t_config *data, t_flags *flags)
// {
// 	char	**array;

// 	array = ft_split(str);
// 	if (array_len(array) != 2)
// 		print_error();
// 	if (!ft_strcmp(array[0], "NO"))
// 	{
// 		if (flags->no)
// 			print_error();
// 		if (array_len(array) != 2)
// 			print_error();
// 		data->no = ft_strdup(array[1]);
// 		flags->no = 1;
// 	}
// 	else if (!ft_strcmp(array[0], "SO"))
// 	{
// 		if (flags->so)
// 			print_error();
// 		if (array_len(array) != 2)
// 			print_error();
// 		data->so = ft_strdup(array[1]);
// 		flags->so = 1;
// 	}
// 	else if (!ft_strcmp(array[0], "WE"))
// 	{
// 		if (flags->we)
// 			print_error();
// 		if (array_len(array) != 2)
// 			print_error();
// 		data->we = ft_strdup(array[1]);
// 		flags->we = 1;
// 	}
// 	else if (!ft_strcmp(array[0], "EA"))
// 	{
// 		if (flags->ea)
// 			print_error();
// 		if (array_len(array) != 2)
// 			print_error();
// 		data->ea = ft_strdup(array[1]);
// 		flags->ea = 1;
// 	}
// }
