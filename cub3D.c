/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:10:02 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/05 14:47:49 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_error(void)
{
	printf("Invalid Control\n");
	exit(1);
}

int	array_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_num(char *ptr)
{
	while (*ptr)
	{
		while (ft_isspace(*ptr))
			ptr++;
		if ((*ptr == '+' || *ptr == '-') && *(ptr + 1) && ft_isdigit(*(ptr
					+ 1)))
			ptr++;
		if (ft_isdigit(*ptr))
		{
			while (ft_isdigit(*ptr))
				ptr++;
			if (*ptr == '+' || *ptr == '-')
				return (0);
		}
		else
			return (0);
		while (ft_isspace(*ptr))
			ptr++;
	}
	return (1);
}

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	handle_texture(char *str, t_game *data, t_flags *flags)
{
	char	**array;

	array = ft_split(str);
	if (array_len(array) != 2)
		print_error();
	if (!ft_strcmp(array[0], "NO"))
	{
		if (flags->NO)
			print_error();
		if (array_len(array) != 2)
			print_error();
		data->NO = ft_strdup(array[1]);
		flags->NO = 1;
	}
	else if (!ft_strcmp(array[0], "SO"))
	{
		if (flags->SO)
			print_error();
		if (array_len(array) != 2)
			print_error();
		data->SO = ft_strdup(array[1]);
		flags->SO = 1;
	}
	else if (!ft_strcmp(array[0], "WE"))
	{
		if (flags->WE)
			print_error();
		if (array_len(array) != 2)
			print_error();
		data->WE = ft_strdup(array[1]);
		flags->WE = 1;
	}
	else if (!ft_strcmp(array[0], "EA"))
	{
		if (flags->EA)
			print_error();
		if (array_len(array) != 2)
			print_error();
		data->EA = ft_strdup(array[1]);
		flags->EA = 1;
	}
}

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

void	handle_rgb(char *str, t_game *data, t_flags *flags)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 'F' && ft_isspace(str[i + 1]))
		{
			if (flags->F)
				print_error();
			i++;
			array = ft_split2(str + i, ',');
			if (array_len(array) != 3)
				print_error();
			ft_edit_array(array);
			j = 0;
			while (j < 3)
			{
				if (atoi(array[j]) < 0 || atoi(array[j]) > 255
					|| !check_num(array[j]))
					print_error();
				data->C[j] = ft_atoi(array[j]);
				j++;
			}
			flags->F = 1;
		}
		if (str[i] == 'C' && ft_isspace(str[i + 1]))
		{
			if (flags->C)
				print_error();
			i++;
			array = ft_split2(str + i, ',');
			if (array_len(array) != 3)
				print_error();
			j = 0;
			while (j < 3)
			{
				if (atoi(array[j]) < 0 || atoi(array[j]) > 255
					|| !check_num(array[j]))
					print_error();
				data->C[j] = ft_atoi(array[j]);
				j++;
			}
			flags->C = 1;
		}
		i++;
	}
}

void	check_line(char *str)
{
	char	**array;
	t_game	data;
	t_flags	flags;

	flags.EA = 0;
	flags.WE = 0;
	flags.SO = 0;
	flags.NO = 0;
	flags.F = 0;
	flags.C = 0;
	array = ft_split(str);
	if (!ft_strcmp(array[0], "WE") || !ft_strcmp(array[0], "EA")
		|| !ft_strcmp(array[0], "NO") || !ft_strcmp(array[0], "SO"))
		handle_texture(str, &data, &flags);
	else if (!ft_strcmp(array[0], "F") || !ft_strcmp(array[0], "C"))
		handle_rgb(str, &data, &flags);
	else
		print_error();
	free(array);
}
void	cube(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	while (str)
	{
		str = get_next_line(fd);
		if (!str)
			return ;
		if (check_spaces(str))
		{
			check_line(str);
		}
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	cube(av[1]);
	return (0);
}
