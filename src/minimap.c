/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:48 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/08 10:16:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	handle_key(void *param)
{
	t_config	*data;
	double		move_speed;
	double		rotation_speed;
	double		new_x;
	double		new_y;
	struct		timeval tv;
	double 		current_time;
	
	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec / 1000000.0;
	update_all_sprites(data, current_time);
	render_3d_view(data->view_3d, data);
	for(int i = 0; i < data->sprite_count; i++)
		draw_sprite(data->view_3d, data, &data->sprites[i]);
	data = (t_config *)param;
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
	render_3d_view(data->view_3d, data);
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

void	init_minimap(t_config data)
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*view_3d;
	mlx_image_t	*minimap_image;

	mlx_ptr = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D - 3D View", true);
	if (!mlx_ptr)
	{
		printf("Error initializing MLX\n");
		exit(1);
	}
	view_3d = mlx_new_image(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!view_3d)
	{
		printf("Error creating 3D view image\n");
		mlx_terminate(mlx_ptr);
		exit(1);
	}
	minimap_image = mlx_new_image(mlx_ptr, data.map.width * TILE_SIZE,
			data.map.height * TILE_SIZE);
	if (!minimap_image)
	{
		printf("Error creating minimap image\n");
		mlx_terminate(mlx_ptr);
		exit(1);
	}
	data.view_3d = view_3d;
	data.minimap_image = minimap_image;
	data.mlx_ptr = mlx_ptr;
	load_texture(&data);
	init_values(&data);
	init_angle(&data);
	render_3d_view(view_3d, &data);
	// draw_minimap(minimap_image, &data);
	mlx_image_to_window(mlx_ptr, view_3d, 0, 0);
	mlx_image_to_window(mlx_ptr, minimap_image, 10, 10);
	mlx_loop_hook(mlx_ptr, &handle_key, &data);
	mlx_loop(mlx_ptr);
	mlx_terminate(mlx_ptr);
}
