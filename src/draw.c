/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:41:04 by aychikhi          #+#    #+#             */
/*   Updated: 2025/11/03 09:53:06 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	init_texture_data(t_config *data, t_ray *ray, t_tex_data *tex)
{
	double	wall_hit_x;

	tex->texture = get_wall_texture(data, ray);
	if (ray->hit_vertical)
		wall_hit_x = fmod(data->map.player_pos.y + ray->distance
				* sin(ray->angle), TILE_SIZE);
	else
		wall_hit_x = fmod(data->map.player_pos.x + ray->distance
				* cos(ray->angle), TILE_SIZE);
	tex->tex_x = (int)((wall_hit_x / TILE_SIZE) * tex->texture->width);
	if ((ray->hit_vertical && tex->texture == data->e_texture)
		|| (!ray->hit_vertical && tex->texture == data->n_texture))
		tex->tex_x = tex->texture->width - 1 - tex->tex_x;
	tex->tex_step = (double)tex->texture->height / ray->wall.line_height;
	tex->tex_pos = (ray->wall.draw_start - (SCREEN_HEIGHT / 2)
			+ (ray->wall.line_height / 2)) * tex->tex_step;
}

static void	draw_ceiling(mlx_image_t *img, t_wall *wall, int x, uint32_t color)
{
	int	y;

	y = 0;
	while (y < wall->draw_start)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

static void	draw_floor(mlx_image_t *img, t_wall *wall, int x, uint32_t color)
{
	int	y;

	y = wall->draw_end;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

static void	draw_textured_wall(mlx_image_t *img, t_wall *wall, t_tex_data *tex,
		int x)
{
	int			y;
	int			tex_y;
	uint32_t	color;

	y = wall->draw_start;
	while (y < wall->draw_end)
	{
		tex_y = (int)tex->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)tex->texture->height)
			tex_y = tex->texture->height - 1;
		color = get_pixel_color(tex->texture, tex->tex_x, tex_y);
		mlx_put_pixel(img, x, y, color);
		tex->tex_pos += tex->tex_step;
		y++;
	}
}

void	draw_wall_slice(t_config *data, mlx_image_t *img, t_ray *ray, int x)
{
	t_tex_data	tex;

	init_texture_data(data, ray, &tex);
	draw_ceiling(img, &ray->wall, x, 0x87CEEBFF);
	draw_textured_wall(img, &ray->wall, &tex, x);
	draw_floor(img, &ray->wall, x, 0x6A2E8BFF);
}
