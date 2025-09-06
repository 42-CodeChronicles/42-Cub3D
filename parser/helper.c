/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:19:33 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/06 15:40:05 by aychikhi         ###   ########.fr       */
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
// 	printf("Flags - no:%d so:%d we:%d ea:%d f:%d c:%d in_map:%d\n",
// 		data.flags.no, data.flags.so, data.flags.we, data.flags.ea,
// 		data.flags.f, data.flags.c, data.flags.in_map);
// 	printf("Map dimensions: %dx%d\n", data.map.weight, data.map.height);
// 	printf("Player: pos(%d,%d) dir:%c flag:%d\n", data.map.player_pos.x,
// 		data.map.player_pos.y, data.map.player_dir, data.map.player_pos.flag);
// 	printf("Map:\n");
// 	if (data.map.array_map)
// 	{
// 		i = 0;
// 		while (i < data.map.height && data.map.array_map[i])
// 		{
// 			printf("[%d] {%s}\n", i, data.map.array_map[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		printf("Map is NULL\n");
// 	printf("=== END ===\n");
// }
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
// print_array(data);
