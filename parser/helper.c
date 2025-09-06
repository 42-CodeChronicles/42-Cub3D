/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:19:33 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/06 18:36:33 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// void	print_array(t_config data)
// {
// 	int	i;
// 	printf("=== CONFIGURATION DATA ===\n");
// 	printf("NO: [%s]\n", data.no ? data.no : "NULL");
// 	printf("SO: [%s]\n", data.so ? data.so : "NULL");
// 	printf("WE: [%s]\n", data.we ? data.we : "NULL");
// 	printf("EA: [%s]\n", data.ea ? data.ea : "NULL");
// 	printf("F: [%d, %d, %d]\n", data.f[0], data.f[1], data.f[2]);
// 	printf("C: [%d, %d, %d]\n", data.c[0], data.c[1], data.c[2]);
// 	printf("Map dimensions: %dx%d\n", data.map.widght, data.map.height);
// 	printf("Player: pos(%d,%d) dir:%c flag:%d\n", data.map.player_pos.x,
// 		data.map.player_pos.y, data.map.player_dir, data.map.player_pos.flag);
// 	printf("Map:\n");
// 	if (data.map.array_map)
// 	{
// 		i = 0;
// 		while (i < data.map.height && data.map.array_map[i])
// 		{
// 			printf("{%s}\n",data.map.array_map[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		printf("Map is NULL\n");
// 	printf("=== END ===\n");
// }
static char	**create_map_copy(t_config *data)
{
	char	**copy;
	int		i;

	copy = malloc(data->map.height * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data->map.height)
	{
		copy[i] = ft_strdup(data->map.array_map[i]);
		i++;
	}
	return (copy);
}

static int	validate_file_extension(char *str)
{
	if (!str || ft_strlen(str) < 4)
		return (0);
	if (ft_strcmp(str + ft_strlen(str) - 4, ".cub"))
		return (0);
	return (1);
}

static void	process_map_validation(t_config *data)
{
	char	**map_copy;

	if (!validate_map(data))
		print_error();
	map_copy = create_map_copy(data);
	flood_fill(map_copy, data->map.player_pos.x, data->map.player_pos.y,
		&data->map);
	free_map_copy(map_copy, data->map.height);
}

void	cube(char *str)
{
	int			fd;
	t_config	data;

	if (!validate_file_extension(str))
	{
		printf("Error: File must have .cub extension\n");
		return ;
	}
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
	process_map_validation(&data);
	print_array(data);
	close(fd);
	free_config(&data);
}

// void	cube(char *str)
// {
// 	int			fd;
// 	t_config	data;
// 	char		**map_copy;

// 	if (!str || ft_strlen(str) < 4 || ft_strcmp(str + ft_strlen(str) - 4,
// 			".cub"))
// 	{
// 		printf("Error: File must have .cub extension\n");
// 		return ;
// 	}
// 	ft_memset(&data, 0, sizeof(t_config));
// 	fd = open(str, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return ;
// 	}
// 	if (!parse_config(fd, &data))
// 		return ;
// 	parse_map(fd, &data);
// 	if (!validate_map(&data))
// 		print_error();
// 	map_copy = create_map_copy(&data);
// 	flood_fill(map_copy, data.map.player_pos.x, data.map.player_pos.y,
// 		data.map.height, data.map.widght);
// 	free_map_copy(map_copy, data.map.height);
// 	close(fd);
// 	free_config(&data);
// }
