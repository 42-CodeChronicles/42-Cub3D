#include "../cub3D.h"

static void draw_square( mlx_image_t *minimap_image , t_config data)
{
	printf("%s\n" , data.map.array_map[0]);
	printf("%d\n" , data.map.height);
	printf("%d\n" , data.map.width);
	printf("%d\n" , data.map.player_pos.x);
	printf("%d\n" , data.map.player_pos.y);
	printf("%c\n" , data.map.player_dir);

	for (int y = 0; y < data.map.height * 10; y++)
	{
		for (int x = 0; x < data.map.width * 10; x++)
		{
			int map_x = x / 10;
			int map_y = y / 10;
			if (map_x >= data.map.width || map_y >= data.map.height)
				continue;
			if (data.map.array_map[map_y][map_x] == '1')
				mlx_put_pixel(minimap_image, x , y , 0xFFFFFFFF);
			else if (data.map.player_pos.x == map_x && data.map.player_pos.y == map_y)
				mlx_put_pixel(minimap_image, x , y , 0xFF0000FF);
			else
				mlx_put_pixel(minimap_image, x , y , 0x00000000);
		}
	}
}
void init_minimap(t_config data)
{
	mlx_t *mlx_ptr;
	mlx_image_t *minimap_image;

	mlx_ptr = mlx_init(data.map.width *10, data.map.height * 10, "Cub3D", true);
	if (!mlx_ptr)
	{
		printf("Error initializing MLX\n");
		exit(1);
	}
	minimap_image = mlx_new_image(mlx_ptr, data.map.width *10, data.map.height * 10);
	if (!minimap_image)
	{
		printf("Error creating minimap image\n");
		mlx_terminate(mlx_ptr);
		exit(1);
	}
	draw_square(minimap_image , data);
	mlx_image_to_window(mlx_ptr, minimap_image, 0, 0);
	mlx_loop(mlx_ptr);
	mlx_terminate(mlx_ptr);
}
