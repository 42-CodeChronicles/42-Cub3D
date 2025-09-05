/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:10:02 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/05 15:24:31 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_line(char *str)
{
	char		**array;
	t_config	data;
	t_flags		flags;

	ft_memset(&data, 0, sizeof(t_config));
	ft_memset(&flags, 0, sizeof(t_flags));
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
