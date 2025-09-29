#include "../cub3D.h"

void init_minimap(void)
{
	mlx_t *mlx_ptr;
	mlx_image_t *minimap_image;

	mlx_ptr = mlx_init(W_WIDTH, W_HEIGHT, "Cub3D", true);
	if (!mlx_ptr)
	{
		printf("Error initializing MLX\n");
		exit(1);
	}
	minimap_image = mlx_new_image(mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!minimap_image)
	{
		printf("Error creating minimap image\n");
		mlx_terminate(mlx_ptr);
		exit(1);
	}
	mlx_loop(mlx_ptr);
	mlx_terminate(mlx_ptr);
}
