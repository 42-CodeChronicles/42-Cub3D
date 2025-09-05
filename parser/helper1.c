/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:11:26 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/05 15:44:46 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
