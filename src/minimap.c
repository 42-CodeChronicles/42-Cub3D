/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:48 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/12 12:50:29 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void mouse_click_handler(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
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

void open_door_in_front(t_config *data)
{
	int tx;
	int ty;
	double reach;
	// int is_open;

	reach = TILE_SIZE * 1.5;
	tx = (int)((data->map.player_pos.x + cos(data->map.player_pos.angle) * reach) / TILE_SIZE);
	ty = (int)((data->map.player_pos.y + sin(data->map.player_pos.angle) * reach) / TILE_SIZE);

	if (!is_valid_pos(data, tx, ty))
		return ;
	if (data->map.array_map[ty][tx] == 'D')
	{
		data->map.array_map[ty][tx] = '0';
		// is_open = 1;
	}
	// else if (data->map.array_map[ty][tx] == '0' && is_open == 1)
	// {
	// 	data->map.array_map[ty][tx] = 'D';
	// 	is_open = 0;
	// }
	
}

void mouse_move_handler(double xpos, double ypos, void *param)
{
	t_config *data = (t_config *)param;
	double center_x = (double)(SCREEN_WIDTH / 2);
	double center_y = (double)(SCREEN_HEIGHT / 2);
	double dx;
	double sensitivity = 0.0025;
	dx = xpos - center_x;

	data->map.player_pos.angle += dx * sensitivity;
	normalize_angle(&data->map.player_pos.angle);
	mlx_set_mouse_pos(data->mlx_ptr, (int)center_x, (int)center_y);
}

void	handle_key(void *param)
{
	t_config	*data;
	double		move_speed;
	double		rotation_speed;
	double		new_x;
	double		new_y;
	struct		timeval tv;
	double 		current_time;
	
	data = (t_config *)param;
	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
	update_all_sprites(data, current_time);
	update_weapon_frame(&data->weapon, current_time);
	move_speed = 2.0;
	rotation_speed = 0.05;
	new_x = data->map.player_pos.x;
	new_y = data->map.player_pos.y;
	normalize_angle(&data->map.player_pos.angle);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx_ptr);
		exit(0);
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		data->map.player_pos.angle -= rotation_speed;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		data->map.player_pos.angle += rotation_speed;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
	{
		new_x += cos(data->map.player_pos.angle) * move_speed;
		new_y += sin(data->map.player_pos.angle) * move_speed;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
	{
		new_x -= cos(data->map.player_pos.angle) * move_speed;
		new_y -= sin(data->map.player_pos.angle) * move_speed;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
	{
		new_x += cos(data->map.player_pos.angle - M_PI / 2) * move_speed;
		new_y += sin(data->map.player_pos.angle - M_PI / 2) * move_speed;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
	{
		new_x += cos(data->map.player_pos.angle + M_PI / 2) * move_speed;
		new_y += sin(data->map.player_pos.angle + M_PI / 2) * move_speed;
	}
	if (!check_collision(data, new_x, new_y))
	{
		data->map.player_pos.x = new_x;
		data->map.player_pos.y = new_y;
	}
	// Render 3D view with walls first
	render_3d_view(data->view_3d, data);
	// Then draw sprites on top
	for(int i = 0; i < data->sprite_count; i++)
		draw_sprite(data->view_3d, data, &data->sprites[i]);
	// Draw weapon HUD on top of everything
	draw_weapon(data->view_3d, data);
	// draw_minimap(data->minimap_image, data);
}

void load_texture(t_config *data)
{
	data->no_texture = mlx_load_png(data->no);
	data->so_texture = mlx_load_png(data->so);
	data->we_texture = mlx_load_png(data->we);
	data->ea_texture = mlx_load_png(data->ea);
	if (!data->no_texture || !data->so_texture || !data->we_texture || !data->ea_texture)
	{
		printf("Error loading textures!\n");
		exit(1);
	}
}

static int	setup_mlx(mlx_t **mlx_ptr, mlx_image_t **view_3d,
			mlx_image_t **minimap_image, t_config *data)
{
	*mlx_ptr = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D - 3D View", true);
	if (!*mlx_ptr)
	{
		printf("Error initializing MLX\n");
		return (0);
	}
	*view_3d = mlx_new_image(*mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!*view_3d)
	{
		printf("Error creating 3D view image\n");
		mlx_terminate(*mlx_ptr);
		return (0);
	}
	*minimap_image = mlx_new_image(*mlx_ptr, data->map.width * TILE_SIZE,
			data->map.height * TILE_SIZE);
	if (!*minimap_image)
	{
		printf("Error creating minimap image\n");
		mlx_terminate(*mlx_ptr);
		return (0);
	}
	return (1);
}

void	init_minimap(t_config *data)
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*view_3d;
	mlx_image_t	*minimap_image;

	if (!setup_mlx(&mlx_ptr, &view_3d, &minimap_image, data))
		exit(1);
	data->view_3d = view_3d;
	data->minimap_image = minimap_image;
	data->mlx_ptr = mlx_ptr;
	load_texture(data);
	weapon_init(data);
	init_values(data);
	init_angle(data);
	render_3d_view(view_3d, data);
	// draw_minimap(minimap_image, data);
	mlx_image_to_window(mlx_ptr, view_3d, 0, 0);
	mlx_image_to_window(mlx_ptr, minimap_image, 10, 10);
	// mouse click (shoot / interact)
	mlx_mouse_hook(mlx_ptr, &mouse_click_handler, data);
	// cursor movement for smooth look around
	mlx_cursor_hook(mlx_ptr, &mouse_move_handler, data);
	// center the mouse once at start
	mlx_set_mouse_pos(mlx_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_loop_hook(mlx_ptr, &handle_key, data);
	mlx_loop(mlx_ptr);
	mlx_terminate(mlx_ptr);
}
