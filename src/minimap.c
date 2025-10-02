#include "../cub3D.h"


static void draw_tile(mlx_image_t *img, int x, int y, uint32_t color)
{
    for (int i = 0; i < TILE_SIZE; i++)
        for (int j = 0; j < TILE_SIZE; j++)
            mlx_put_pixel(img, x + i, y + j, color);
}


static void draw_player_dot(mlx_image_t *img, int x, int y)
{
    int center_x = x + TILE_SIZE / 4;
    int center_y = y + TILE_SIZE / 4;
    int dot_size = 3;
    
    for (int i = -dot_size; i <= dot_size; i++)
        for (int j = -dot_size; j <= dot_size; j++)
            mlx_put_pixel(img, center_x + i, center_y + j, 0xFF0000FF);
}


static int is_valid_pos(t_config *data, int x, int y)
{
    if(x >= 0 && x < data->map.width && 
       y >= 0 && y < data->map.height)
        return 1;
    return 0;
}


static void clear_minimap(mlx_image_t *img)
{
    for (int x = 0; x < MINIMAP_SIZE; x++)
        for (int y = 0; y < MINIMAP_SIZE; y++)
            mlx_put_pixel(img, x, y, 0xFFFFFFFF);
}


static void draw_minimap(mlx_image_t *minimap_image, t_config *data)
{
    clear_minimap(minimap_image);
    int radius = MINIMAP_TILES / 2;
    float px = data->map.player_pos.x;
    float py = data->map.player_pos.y;

    for (int dx = -radius; dx <= radius; dx++)
    {
        for (int dy = -radius; dy <= radius; dy++)
        {
            int map_x = (int)px + dx;               
            int map_y = (int)py + dy;
            int screen_x = (dx + radius) * TILE_SIZE;  
            int screen_y = (dy + radius) * TILE_SIZE;

            if (!is_valid_pos(data, map_x, map_y))
                continue;
            if (data->map.array_map[map_y][map_x] == '1')
                draw_tile(minimap_image, screen_x, screen_y, 0x000000FF);
        }
    }
    
    int player_screen_x = radius * TILE_SIZE + (px - (int)px) * TILE_SIZE;
    int player_screen_y = radius * TILE_SIZE + (py - (int)py) * TILE_SIZE;
    draw_player_dot(minimap_image, player_screen_x - TILE_SIZE/2, player_screen_y - TILE_SIZE/2);
}

static void handle_key(mlx_key_data_t keydata, void *param)
{
    t_config *data = (t_config *)param;
    float move_speed = 0.1f;
    float new_x = data->map.player_pos.x;
    float new_y = data->map.player_pos.y;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        exit(0);
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
        new_y -= move_speed;
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
        new_y += move_speed;
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
        new_x -= move_speed;
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
        new_x += move_speed;
    
    if (data->map.array_map[(int)new_y][(int)new_x] != '1') 
    {
        data->map.player_pos.x = new_x;
        data->map.player_pos.y = new_y;
    }

    draw_minimap(data->minimap_image, data);
}

void init_minimap(t_config data)
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
    data.minimap_image = minimap_image;

    draw_minimap(minimap_image, &data);
    mlx_image_to_window(mlx_ptr, minimap_image, 200, 200);
    
    mlx_key_hook(mlx_ptr, &handle_key, &data);
    mlx_loop(mlx_ptr);
    mlx_terminate(mlx_ptr);
}
