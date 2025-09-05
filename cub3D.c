/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:10:02 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/04 17:16:16 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void print_error(void)
{
	printf("Invalid Map\n");
	exit(1);
}

int check_array(char *array)
{
	if (ft_strcmp(array, "NO") && ft_strcmp(array, "SO") && ft_strcmp(array, "WE" ) && ft_strcmp(array, "EA"))
		return 0;
	return 1;
}

void cube(char *str)
{
	char **array;
	int fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
        return;
	}	
	while (str)
	{
		str = get_next_line(fd);
		array = ft_split(str, ' ');
		if (!array)
			return;
		if (!check_array(array[0]))
		{
			// printf("%s\n", array[0]);
			print_error();
		}
		free(array);
		// array = NULL;
		// printf("%s", str);
	}
	
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	cube(av[1]);
	return 0;
}
