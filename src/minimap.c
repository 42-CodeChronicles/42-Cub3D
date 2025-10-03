#include "../cub3D.h"


static void draw_tile(mlx_image_t *img, int x, int y, uint32_t color)
{
    for (int i = 0; i < TILE_SIZE; i++)
        for (int j = 0; j < TILE_SIZE; j++)
        {
            mlx_put_pixel(img, x + i, y + j, color);
        }
}


static void draw_player_dot(mlx_image_t *img, int x, int y)
{
    int dot_size = TILE_SIZE / 4;

    for (int i = 0; i < dot_size; i++)
        for (int j = 0; j < dot_size; j++)
        {
            printf("Drawing player dot at (%d, %d)\n", x + i, y + j);
            mlx_put_pixel(img, x + i - dot_size / 2, y + j - dot_size / 2, 0xFF0000FF); // Red color
        }
    
}


static int is_valid_pos(t_config *data, int x, int y)
{
    if(x >= 0 && x < data->map.width && 
       y >= 0 && y < data->map.height)
        return 1;
    return 0;
}


// static void clear_minimap(mlx_image_t *img)
// {
//     for (int x = 0; x < MINIMAP_SIZE; x++)
//         for (int y = 0; y < MINIMAP_SIZE; y++)
//             mlx_put_pixel(img, x, y, 0xFFFFFFFF);
// }


static void draw_minimap(mlx_image_t *minimap_image, t_config *data)
{
    for (int y = 0; y < data->map.height; y++)
    {
        for (int x = 0; x < data->map.width; x++)
        {
            if(!is_valid_pos(data, x, y))
                continue;
            if (data->map.array_map[y][x] == '1')
                draw_tile(minimap_image, x * TILE_SIZE, y * TILE_SIZE, 0x000000FF);
            else
                draw_tile(minimap_image, x * TILE_SIZE, y * TILE_SIZE, 0xFFFFFFFF);
        }
    }

    draw_player_dot(minimap_image, data->map.player_pos.x, data->map.player_pos.y);
}

static void handle_key(void *param)
{
    t_config *data = (t_config *)param;
    int move_speed = 1;
    int new_x = data->map.player_pos.x;
    int new_y = data->map.player_pos.y;

    if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
    {
        mlx_close_window(data->mlx_ptr);
        exit(0);
    }
    if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
        new_y -= move_speed;
    if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
        new_y += move_speed;
    if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
        new_x -= move_speed;
    if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
        new_x += move_speed;

    if (data->map.array_map[new_y / TILE_SIZE][new_x / TILE_SIZE] != '1')
    {
        data->map.player_pos.x = new_x;
        data->map.player_pos.y = new_y;
        draw_minimap(data->minimap_image, data);
    }

}

static void init_values(t_config *data)
{
    data->map.player_pos.x *= TILE_SIZE;
    data->map.player_pos.y *= TILE_SIZE;
    data->map.player_pos.x += TILE_SIZE / 2;
    data->map.player_pos.y += TILE_SIZE / 2;
}

void init_minimap(t_config data)
{
    mlx_t *mlx_ptr;
    mlx_image_t *minimap_image;

    mlx_ptr = mlx_init(data.map.width * TILE_SIZE, data.map.height * TILE_SIZE, "Cub3D", true);
    printf("Map Width: %d, Map Height: %d\n", data.map.width * TILE_SIZE, data.map.height * TILE_SIZE);
    if (!mlx_ptr)
    {
        printf("Error initializing MLX\n");
        exit(1);
    }
    minimap_image = mlx_new_image(mlx_ptr, data.map.width * TILE_SIZE, data.map.height * TILE_SIZE);
    if (!minimap_image)
    {
        printf("Error creating minimap image\n");
        mlx_terminate(mlx_ptr);
        exit(1);
    }
    data.minimap_image = minimap_image;
    data.mlx_ptr = mlx_ptr;

    init_values(&data);
    draw_minimap(minimap_image, &data);
    mlx_image_to_window(mlx_ptr, minimap_image, 0, 0);

    mlx_loop_hook(mlx_ptr, &handle_key, &data);
    // mlx_key_hook(mlx_ptr, &handle_key, &data);
    mlx_loop(mlx_ptr);
    mlx_terminate(mlx_ptr);
}
