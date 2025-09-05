/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:10:02 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/05 18:33:22 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_line(char *str, t_config *data, t_flags *flags)
{
	char	**array;

	array = ft_split(str);
	if (!ft_strcmp(array[0], "WE") || !ft_strcmp(array[0], "EA")
		|| !ft_strcmp(array[0], "NO") || !ft_strcmp(array[0], "SO"))
		handle_texture(str, data, flags);
	else if (!ft_strcmp(array[0], "F") || !ft_strcmp(array[0], "C"))
		handle_rgb(str, data, flags);
	else
		print_error();
	free_array(array);
}

// void	print_array(t_config data)
// {
// 	int	i;

// 	printf("EA : [%s]\n", data.ea);
// 	printf("WE : [%s]\n", data.we);
// 	printf("SO : [%s]\n", data.so);
// 	printf("NO : [%s]\n", data.no);
// 	i = 0;
// 	while (i < 6)
// 	{
// 		printf("[%d]\n", data.f[i]);
// 		i++;
// 	}
// }

void	cube(char *str)
{
	int			fd;
	t_config	data;
	t_flags		flags;

	ft_memset(&data, 0, sizeof(t_config));
	ft_memset(&flags, 0, sizeof(t_flags));
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
		{
			free_config(&data);
			return ;
		}
		if (check_spaces(str))
			check_line(str, &data, &flags);
		free(str);
	}
}
// void	ll(void)
// {
// 	system("leaks cub3D");
// }

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	cube(av[1]);
	return (0);
}
