/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:25:16 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/21 15:25:26 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	mouse_click_handler(mouse_key_t button, action_t action,
		modifier_key_t mods, void *param)
{
	t_config	*data;

	(void)mods;
	data = (t_config *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		if (!data->weapon.is_shooting)
		{
			data->weapon.is_shooting = 1;
			data->weapon.current_frame = 0;
		}
	}
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		open_door_in_front((t_config *)param);
}

void	open_door_in_front(t_config *data)
{
	int		tx;
	int		ty;
	double	reach;

	reach = TILE_SIZE * 1.5;
	tx = (int)((data->map.player_pos.x + cos(data->map.player_pos.angle)
				* reach) / TILE_SIZE);
	ty = (int)((data->map.player_pos.y + sin(data->map.player_pos.angle)
				* reach) / TILE_SIZE);
	if (!is_valid_pos(data, tx, ty))
		return ;
	if (data->map.array_map[ty][tx] == 'D')
	{
		data->map.array_map[ty][tx] = '0';
		data->doors->is_open = 1;
	}
	else if (data->map.array_map[ty][tx] == '0' && data->doors->is_open == 1
		&& data->doors->is_open == 1)
	{
		data->map.array_map[ty][tx] = 'D';
		data->doors->is_open = 0;
	}
}

void	mouse_move_handler(double xpos, double ypos, void *param)
{
	t_config	*data;
	double		center_x;
	double		center_y;
	double		dx;
	double		sensitivity;

	data = (t_config *)param;
	center_x = (double)(SCREEN_WIDTH / 2);
	center_y = (double)(SCREEN_HEIGHT / 2);
	sensitivity = 0.0025;
	dx = xpos - center_x;
	data->map.player_pos.angle += dx * sensitivity;
	normalize_angle(&data->map.player_pos.angle);
	mlx_set_mouse_pos(data->mlx_ptr, (int)center_x, (int)center_y);
}
