#include "../cub3D.h"

void	handle_key(void *param)
{
	t_config	*data;
	double		move_speed;
	double		rotation_speed;
	double		new_x;
	double		new_y;

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
	draw_minimap(data->minimap_image, data);
}

void	init_minimap(t_config data)
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*minimap_image;

	mlx_ptr = mlx_init(data.map.width * TILE_SIZE, data.map.height * TILE_SIZE,
			"Cub3D", true);
	if (!mlx_ptr)
	{
		printf("Error initializing MLX\n");
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
	data.minimap_image = minimap_image;
	data.mlx_ptr = mlx_ptr;
	init_values(&data);
	init_angle(&data);
	draw_minimap(minimap_image, &data);
	mlx_image_to_window(mlx_ptr, minimap_image, 0, 0);
	mlx_loop_hook(mlx_ptr, &handle_key, &data);
	mlx_loop(mlx_ptr);
	mlx_terminate(mlx_ptr);
}
