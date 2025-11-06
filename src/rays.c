/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:51 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/06 09:42:36 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

typedef struct s_rayscast
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;	
	double	side_dist_x;
	double	side_dist_y;
}			t_rayscast;

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
		if (data->map.array_map[ray->map_y][ray->map_x] == '1')
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

void	cast_all_rays(mlx_image_t *img, t_config *data)
{
	double	fov_rad;
	double	angle_step;
	double	start_angle;
	double	ray_angle;
	int		hit_vertical;
	double	distance;

	fov_rad = (FOV * M_PI) / 180.0;
	angle_step = fov_rad / NUM_RAYS;
	start_angle = data->map.player_pos.angle - (fov_rad / 2);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		double wall_x;
		int map_x, map_y;
		ray_angle = start_angle + (i * angle_step);
		distance = cast_ray(data, ray_angle, &hit_vertical , &wall_x, &map_x, &map_y);
		draw_line_dda(img, data, ray_angle, distance, 0xF0FF);
	}
}
