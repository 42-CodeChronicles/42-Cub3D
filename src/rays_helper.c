/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:30:03 by ayaarab           #+#    #+#             */
/*   Updated: 2025/12/03 19:49:14 by ayaarab          ###   ########.fr       */
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

void	set_hit_info(t_config *data, t_rayscast *ray, t_ray_hit *hit)
{
	double	hit_pos;

	if (hit->side == 0)
	{
		*hit->hit_vertical = 1;
		hit_pos = ray->y + hit->distance * ray->dir_y;
	}
	else
	{
		*hit->hit_vertical = 0;
		hit_pos = ray->x + hit->distance * ray->dir_x;
	}
	hit->pos->wall_x = hit_pos / TILE_SIZE;
	hit->pos->wall_x = hit->pos->wall_x - floor(hit->pos->wall_x);
	data->wall_side = get_wall_side(ray, hit->side);
	if (data->wall_side == 1 || data->wall_side == 3)
		hit->pos->wall_x = 1.0 - hit->pos->wall_x;
	hit->pos->map_x = ray->map_x;
	hit->pos->map_y = ray->map_y;
}
