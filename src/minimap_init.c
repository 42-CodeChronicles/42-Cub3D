/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:43 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/21 15:31:01 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_angle(t_config *data)
{
	if (data->map.player_dir == 'N')
		data->map.player_pos.angle = 3 * M_PI / 2.0;
	else if (data->map.player_dir == 'S')
		data->map.player_pos.angle = M_PI / 2.0;
	else if (data->map.player_dir == 'E')
		data->map.player_pos.angle = 0.0;
	else if (data->map.player_dir == 'W')
		data->map.player_pos.angle = M_PI;
	else
		data->map.player_pos.angle = 0.0;
}

void	init_values(t_config *data)
{
	data->map.player_pos.x *= TILE_SIZE;
	data->map.player_pos.y *= TILE_SIZE;
	data->map.player_pos.x += TILE_SIZE / 2;
	data->map.player_pos.y += TILE_SIZE / 2;
}

void	init_ray(t_rayscast *ray, t_config *data, double angle)
{
	ray->x = data->map.player_pos.x;
	ray->y = data->map.player_pos.y;
	ray->dir_x = cos(angle);
	ray->dir_y = sin(angle);
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->map_x = (int)(ray->x / TILE_SIZE);
	ray->map_y = (int)(ray->y / TILE_SIZE);
}
