/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:42:48 by ayaarab           #+#    #+#             */
/*   Updated: 2025/11/21 15:25:09 by ayaarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	load_texture(t_config *data)
{
	data->no_texture = mlx_load_png(data->no);
	data->so_texture = mlx_load_png(data->so);
	data->we_texture = mlx_load_png(data->we);
	data->ea_texture = mlx_load_png(data->ea);
	if (!data->no_texture || !data->so_texture || !data->we_texture
		|| !data->ea_texture)
	{
		printf("Error loading textures!\n");
		exit(1);
	}
}

static int	setup_mlx(mlx_t **mlx_ptr, mlx_image_t **view_3d,
		mlx_image_t **minimap_image, t_config *data)
{
	int	minimap_size;

	minimap_size = 300;
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
	*minimap_image = mlx_new_image(*mlx_ptr, minimap_size, minimap_size);
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
	mlx_image_to_window(mlx_ptr, view_3d, 0, 0);
	mlx_image_to_window(mlx_ptr, minimap_image, SCREEN_WIDTH - 300, 10);
	mlx_mouse_hook(mlx_ptr, &mouse_click_handler, data);
	mlx_cursor_hook(mlx_ptr, &mouse_move_handler, data);
	mlx_set_mouse_pos(mlx_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_loop_hook(mlx_ptr, &handle_key, data);
	mlx_loop(mlx_ptr);
	mlx_terminate(mlx_ptr);
}
