/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:10:02 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/06 12:20:06 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
// 	while (data.map)
// 	{
// 		printf("[%s]\n", data.map->str);
// 		data.map = data.map->next;
// 	}
// }

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	cube(av[1]);
	return (0);
}
