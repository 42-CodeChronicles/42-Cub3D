/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:37:20 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/30 15:58:31 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	new_str(char *tmp, char *str, int len)
{
	int	i;

	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	while (i < len)
	{
		tmp[i] = ' ';
		i++;
	}
	tmp[i] = '\0';
}

static void	finish_map(t_config **data)
{
	int		i;
	int		max;
	char	*tmp;

	i = 0;
	max = (*data)->map.width;
	while ((*data)->map.array_map[i])
	{
		if (ft_strlen((*data)->map.array_map[i]) < (size_t)max)
		{
			tmp = malloc(max + 1);
			new_str(tmp, (*data)->map.array_map[i], max);
			free((*data)->map.array_map[i]);
			(*data)->map.array_map[i] = tmp;
		}
		i++;
	}
}

static int	check_dir(char *str, char *player_dir, t_point *player_pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'E' || str[i] == 'S')
		{
			if (*player_dir != '\0')
				print_error_map();
			*player_dir = str[i];
			player_pos->x = i;
			player_pos->flag = 1;
			j++;
		}
		i++;
	}
	return (j);
}

static void	get_dir(t_list *map, t_point *player_pos, char *player_dir)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map)
	{
		count = check_dir(map->str, player_dir, player_pos);
		if (count > 1)
			print_error_map();
		if (player_pos->flag)
		{
			player_pos->y = i;
			player_pos->flag = 0;
		}
		i++;
		map = map->next;
	}
	if (!*player_dir)
		print_error_map();
}

void	lst_to_2d(t_config **data, t_list *map)
{
	int	len;
	int	i;

	len = ft_lstsize(map);
	(*data)->map.array_map = malloc((len + 1) * sizeof(char *));
	if (!(*data)->map.array_map)
		return ;
	i = 0;
	(*data)->map.height = len;
	get_dir(map, &(*data)->map.player_pos, &(*data)->map.player_dir);
	while (i < len)
	{
		(*data)->map.array_map[i] = ft_strdup(map->str);
		if (ft_strlen(map->str) > (size_t)(*data)->map.width)
			(*data)->map.width = ft_strlen(map->str);
		map = map->next;
		i++;
	}
	(*data)->map.array_map[i] = NULL;
	finish_map(data);
}
