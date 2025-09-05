/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:15:22 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/05 17:38:44 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	ft_edit_array(char **array)
{
	char	*tmp;
	int		i;

	i = 0;
	while (array[i])
	{
		tmp = ft_strtrim(array[i], " \t\n");
		free(array[i]);
		array[i] = tmp;
		i++;
	}
}

static void	validate_and_set_rgb(char **array, int *rgb_values)
{
	int	j;

	j = 0;
	while (j < 3)
	{
		if (ft_atoi(array[j]) < 0 || ft_atoi(array[j]) > 255
			|| !check_num(array[j]))
			print_error();
		rgb_values[j] = ft_atoi(array[j]);
		j++;
	}
}

static void	process_floor_color(char *str, int *i, t_config *data,
		t_flags *flags)
{
	char	**array;

	if (flags->f)
		print_error();
	(*i)++;
	array = ft_split2(str + *i, ',');
	if (array_len(array) != 3)
		print_error();
	ft_edit_array(array);
	validate_and_set_rgb(array, data->f);
	flags->f = 1;
}

static void	process_ceiling_color(char *str, int *i, t_config *data,
		t_flags *flags)
{
	char	**array;

	if (flags->c)
		print_error();
	(*i)++;
	array = ft_split2(str + *i, ',');
	if (array_len(array) != 3)
		print_error();
	ft_edit_array(array);
	validate_and_set_rgb(array, data->c);
	flags->c = 1;
}

void	handle_rgb(char *str, t_config *data, t_flags *flags)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'F' && ft_isspace(str[i + 1]))
			process_floor_color(str, &i, data, flags);
		else if (str[i] == 'C' && ft_isspace(str[i + 1]))
			process_ceiling_color(str, &i, data, flags);
		i++;
	}
}

// static void	ft_edit_array(char **array)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	while (array[i])
// 	{
// 		tmp = ft_strtrim(array[i], " \t\n");
// 		free(array[i]);
// 		array[i] = tmp;
// 		i++;
// 	}
// }
//
// void	handle_rgb(char *str, t_config *data, t_flags *flags)
// {
// 	char	**array;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 'F' && ft_isspace(str[i + 1]))
// 		{
// 			if (flags->f)
// 				print_error();
// 			i++;
// 			array = ft_split2(str + i, ',');
// 			if (array_len(array) != 3)
// 				print_error();
// 			ft_edit_array(array);
// 			j = 0;
// 			while (j < 3)
// 			{
// 				if (atoi(array[j]) < 0 || atoi(array[j]) > 255
// 					|| !check_num(array[j]))
// 					print_error();
// 				data->f[j] = ft_atoi(array[j]);
// 				j++;
// 			}
// 			flags->f = 1;
// 		}
// 		if (str[i] == 'C' && ft_isspace(str[i + 1]))
// 		{
// 			if (flags->c)
// 				print_error();
// 			i++;
// 			array = ft_split2(str + i, ',');
// 			if (array_len(array) != 3)
// 				print_error();
// 			j = 0;
// 			while (j < 3)
// 			{
// 				if (atoi(array[j]) < 0 || atoi(array[j]) > 255
// 					|| !check_num(array[j]))
// 					print_error();
// 				data->c[j] = ft_atoi(array[j]);
// 				j++;
// 			}
// 			flags->c = 1;
// 		}
// 		i++;
// 	}
// }