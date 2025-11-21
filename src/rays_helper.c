/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:30:03 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/21 15:31:10 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_wall_side(t_rayscast *ray, int side)
{
	if (side == 0)
	{
		if (ray->step_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray->step_y > 0)
			return (1);
		else
			return (0);
	}
}
