/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:25:03 by aychikhi          #+#    #+#             */
/*   Updated: 2025/09/04 13:21:09 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_strcpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	if (!src)
		return ;
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}
