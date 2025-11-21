/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:51 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/21 15:31:19 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	setup_ray_steps(t_rayscast *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = ((ray->x / TILE_SIZE) - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - (ray->x / TILE_SIZE))
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = ((ray->y / TILE_SIZE) - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - (ray->y / TILE_SIZE))
			* ray->delta_dist_y;
	}
}

int	perform_dda(t_rayscast *ray, t_config *data)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= data->map.width || ray->map_y < 0
			|| ray->map_y >= data->map.height)
			break ;
		if (data->map.array_map[ray->map_y][ray->map_x] == '1'
			|| data->map.array_map[ray->map_y][ray->map_x] == 'D')
			hit = 1;
	}
	return (side);
}

double	calculate_distance(t_rayscast *ray, int side)
{
	double	distance;

	if (side == 0)
		distance = (ray->map_x - ray->x / TILE_SIZE + (1 - ray->step_x) / 2)
			/ ray->dir_x;
	else
		distance = (ray->map_y - ray->y / TILE_SIZE + (1 - ray->step_y) / 2)
			/ ray->dir_y;
	return (distance * TILE_SIZE);
}

double	cast_ray(t_config *data, double ray_angle, int *hit_vertical,
		double *wall_x, int *map_x, int *map_y)
{
	t_rayscast	ray;
	int			side;
	double		distance;
	double		hit_pos;

	init_ray(&ray, data, ray_angle);
	setup_ray_steps(&ray);
	side = perform_dda(&ray, data);
	distance = calculate_distance(&ray, side);
	if (side == 0)
	{
		*hit_vertical = 1;
		hit_pos = ray.y + distance * ray.dir_y;
	}
	else
	{
		*hit_vertical = 0;
		hit_pos = ray.x + distance * ray.dir_x;
	}
	*wall_x = hit_pos / TILE_SIZE;
	*wall_x = *wall_x - floor(*wall_x);
	data->wall_side = get_wall_side(&ray, side);
	if (data->wall_side == 1 || data->wall_side == 3)
		*wall_x = 1.0 - *wall_x;
	*map_x = ray.map_x;
	*map_y = ray.map_y;
	return (distance);
}
