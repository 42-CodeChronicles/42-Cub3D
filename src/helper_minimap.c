/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:54:50 by ayaarab           #+#    #+#             */
/*   Updated: 2025/12/03 14:44:22 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	player_move1(t_config *data, double move_speed, double *new_x,
		double *new_y)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
	{
		*new_x += cos(data->map.player_pos.angle) * move_speed;
		*new_y += sin(data->map.player_pos.angle) * move_speed;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
	{
		*new_x -= cos(data->map.player_pos.angle) * move_speed;
		*new_y -= sin(data->map.player_pos.angle) * move_speed;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
	{
		*new_x += cos(data->map.player_pos.angle - M_PI / 2) * move_speed;
		*new_y += sin(data->map.player_pos.angle - M_PI / 2) * move_speed;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
	{
		*new_x += cos(data->map.player_pos.angle + M_PI / 2) * move_speed;
		*new_y += sin(data->map.player_pos.angle + M_PI / 2) * move_speed;
	}
}

static void	player_move(t_config *data, double rotation_speed,
		double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = data->map.player_pos.x;
	new_y = data->map.player_pos.y;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx_ptr);
		exit(0);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		data->map.player_pos.angle -= rotation_speed;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		data->map.player_pos.angle += rotation_speed;
	player_move1(data, move_speed, &new_x, &new_y);
	if (!check_collision(data, new_x, new_y))
	{
		data->map.player_pos.x = new_x;
		data->map.player_pos.y = new_y;
	}
}

static void	handle_key_helper(t_config *data)
{
	int	i;

	i = 0;
	while (i < data->sprite_count)
	{
		draw_sprite(data->view_3d, data, &data->sprites[i]);
		i++;
	}
}

void	handle_key(void *param)
{
	t_config		*data;
	double			move_speed;
	double			rotation_speed;
	struct timeval	tv;
	double			current_time;

	data = (t_config *)param;
	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
	update_all_sprites(data, current_time);
	update_weapon_frame(&data->weapon, current_time);
	move_speed = 5.0;
	rotation_speed = 0.05;
	player_move(data, rotation_speed, move_speed);
	normalize_angle(&data->map.player_pos.angle);
	render_3d_view(data->view_3d, data);
	handle_key_helper(data);
	draw_weapon(data->view_3d, data);
	clear_minimap(data->minimap_image);
	draw_minimap(data->minimap_image, data);
}

void	clear_minimap(mlx_image_t *minimap_image)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)minimap_image->height)
	{
		x = 0;
		while (x < (int)minimap_image->width)
		{
			mlx_put_pixel(minimap_image, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}
