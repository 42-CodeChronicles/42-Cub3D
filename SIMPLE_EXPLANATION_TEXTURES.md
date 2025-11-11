# 🎨 TEXTURES - Simple Explanation for Everyone!

## What is a Texture?

Imagine you're playing with building blocks. Instead of the blocks being just one color, you can put **pictures** on them! That's what a texture is - it's like a sticker or wallpaper that makes walls look real in your game.

---

## 📂 Files that Handle Textures

### 1. **cub3D.h** - The Recipe Book
This file tells the computer what textures are and how to remember them.

```c
typedef struct s_tex_data
{
	mlx_texture_t	*texture;      // The picture we're using
	int				tex_x;         // Which column of the picture to use
	uint32_t		ceiling_color; // Color of the ceiling
	uint32_t		floor_color;   // Color of the floor
}	t_tex_data;
```

**Simple Explanation:**
- `texture` = The picture we want to put on the wall
- `tex_x` = Like choosing which vertical stripe of the picture to use
- `ceiling_color` = What color is the sky/ceiling
- `floor_color` = What color is the ground

---

### 2. **texture.c** - The Painter

This file actually draws the textures on your screen!

#### Function: `init_tex_data()` - Getting Ready to Paint

```c
static void	init_tex_data(t_tex_data *tex, t_config *data, t_wall_pos *pos)
{
	t_door	*door;
	double	door_offset;

	// Get the right picture for this wall
	tex->texture = get_texture(data, pos->map_y, pos->map_x);
	
	// Check if it's a door
	door_offset = 0.0;
	if (data->map.array_map[pos->map_y][pos->map_x] == 'D')
	{
		door = get_door_state(data, pos->map_x, pos->map_y);
		if (door)
			door_offset = door->open_amount;
	}
	
	// Adjust position if door is opening
	pos->wall_x += door_offset;
	if (pos->wall_x > 1.0)
		pos->wall_x -= 1.0;
		
	// Find which column of the texture to use
	tex->tex_x = (int)(pos->wall_x * tex->texture->width);
	
	// Set ceiling and floor colors
	tex->ceiling_color = (data->c[0] << 24) | (data->c[1] << 16)
		| (data->c[2] << 8) | 0xFF;
	tex->floor_color = (data->f[0] << 24) | (data->f[1] << 16)
		| (data->f[2] << 8) | 0xFF;
}
```

**Simple Example:**
Imagine you have a picture that's 100 pixels wide. If you hit the wall exactly in the middle, `tex_x` would be 50. This tells us to use the middle column of the picture!

---

#### Function: `draw_ceiling()` - Paint the Sky

```c
static void	draw_ceiling(mlx_image_t *img, int x, int end, uint32_t color)
{
	int	y;

	y = 0;
	while (y < end)  // Go from top to where wall starts
	{
		mlx_put_pixel(img, x, y, color);  // Paint one dot
		y++;
	}
}
```

**Simple Explanation:**
This is like coloring the sky! It starts at the very top of the screen and colors down until it reaches the wall.

---

#### Function: `draw_wall()` - Paint the Wall with Texture

```c
static void	draw_wall(mlx_image_t *img, t_draw_params *params, t_tex_data *tex)
{
	double		tex_pos;
	int			tex_y;
	uint32_t	color;
	int			y;

	y = params->wall->draw_start;  // Start at top of wall
	while (y < params->wall->draw_end)  // Until bottom of wall
	{
		// Figure out which row of the texture picture to use
		tex_pos = (y - params->wall->draw_start
				+ params->wall->tex_start_offset)
			/ (double)params->wall->line_height;
		tex_y = (int)(tex_pos * tex->texture->height);
		
		// Get the color from the texture at position (tex_x, tex_y)
		color = get_texture_color(tex->texture, tex->tex_x, tex_y);
		
		// Put that colored dot on the screen
		mlx_put_pixel(img, params->x, y, color);
		y++;
	}
}
```

**Simple Example:**
Think of it like this:
1. You have a brick wall picture (the texture)
2. You look at one vertical line of bricks (tex_x)
3. For each pixel going down your screen, you pick the matching brick color from the picture
4. You paint that color on the screen

---

#### Function: `draw_floor()` - Paint the Ground

```c
static void	draw_floor(mlx_image_t *img, int x, int start, uint32_t color)
{
	int	y;

	y = start;  // Start where wall ends
	while (y < SCREEN_HEIGHT)  // Go to bottom of screen
	{
		mlx_put_pixel(img, x, y, color);  // Paint one dot
		y++;
	}
}
```

**Simple Explanation:**
Just like the ceiling, but this colors the ground from where the wall ends to the bottom of the screen!

---

#### Function: `draw_wall_slice_texture()` - The Complete Painter

```c
void	draw_wall_slice_texture(mlx_image_t *img, t_draw_params *params)
{
	t_tex_data	tex;

	init_tex_data(&tex, params->data, params->pos);  // Get ready
	
	// Paint in order:
	draw_ceiling(img, params->x, params->wall->draw_start, tex.ceiling_color);
	draw_wall(img, params, &tex);
	draw_floor(img, params->x, params->wall->draw_end, tex.floor_color);
}
```

**Simple Explanation:**
This is the boss function! It paints one vertical line on your screen:
1. First, paint the ceiling (sky)
2. Then, paint the wall with its texture
3. Finally, paint the floor (ground)

---

### 3. **texture_helper.c** - The Helper Tools

#### Function: `get_texture()` - Choose the Right Picture

```c
mlx_texture_t	*get_texture(t_config *data, int y, int x)
{
	// If it's a door, use door picture
	if (data->map.array_map[y][x] == 'D')
		return (data->door_texture);
		
	// Otherwise, check which direction wall is facing:
	if (data->wall_side == 0)
		return (data->no_texture);      // North wall
	else if (data->wall_side == 1)
		return (data->so_texture);      // South wall
	else if (data->wall_side == 2)
		return (data->ea_texture);      // East wall
	else
		return (data->we_texture);      // West wall
}
```

**Simple Example:**
Think of your room:
- The wall facing north might be painted blue
- The wall facing south might be painted red
- East wall might be green
- West wall might be yellow

This function picks which "paint color" (texture) to use!

---

#### Function: `get_texture_color()` - Get One Dot's Color

```c
uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	int		index;
	uint8_t	r;  // Red
	uint8_t	g;  // Green
	uint8_t	b;  // Blue
	uint8_t	a;  // Alpha (transparency)

	// Make sure we don't go outside the picture
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)texture->height)
		tex_y = texture->height - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	
	// Find where this pixel is in the picture data
	index = (tex_y * texture->width + tex_x) * 4;
	
	// Get the red, green, blue, and alpha values
	r = texture->pixels[index + 0];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = texture->pixels[index + 3];
	
	// Combine them into one color
	return (r << 24 | g << 16 | b << 8 | a);
}
```

**Simple Example:**
Imagine you have a coloring book picture. This function:
1. Finds the exact spot you're looking at (x and y position)
2. Looks at what colors are used there (red, green, blue)
3. Tells you exactly what color that dot is!

Every color on a computer is made by mixing red, green, and blue - just like mixing paint!

---

## 🎮 How Textures Work in Your Game

### Step-by-Step:

1. **You Look Around:** Your character looks at the game world
2. **Ray Hits Wall:** The game shoots invisible "rays" and finds where they hit walls
3. **Pick Texture:** The game says "This is a north wall, so use the north wall picture!"
4. **Pick Column:** It figures out which vertical stripe of the picture to use
5. **Draw Line:** For each pixel going down:
   - Find the matching row in the picture
   - Get that color
   - Put it on your screen
6. **Repeat:** Do this for every vertical line on your screen!

---

## 🌈 Real-Life Example

Imagine you're taking a photo of a brick wall:

1. **The Wall Picture (Texture):** You have a photo of bricks
2. **One Vertical Line (Column):** You look at just one vertical line of bricks in the photo
3. **Stretching:** If you're close to the wall, the bricks look BIG. If far away, they look small
4. **Screen:** You copy those bricks onto your computer screen

That's exactly what the texture code does - it takes pictures of walls and "wraps" them around the game world!

---

## 🔑 Important Terms

- **Texture:** A picture used to make walls look real
- **Pixel:** One tiny dot on the screen
- **tex_x:** Which column (vertical line) of the picture to use
- **tex_y:** Which row (horizontal line) of the picture to use
- **Color:** Made from Red, Green, Blue mixed together
- **Wall_side:** Which direction the wall faces (North, South, East, West)

---

## 🎨 Summary

Textures make your game look cool! Instead of boring colored walls, you can have:
- Brick walls
- Stone walls
- Wood walls
- Metal doors
- Anything you can imagine!

The code figures out which picture to use, which part of the picture to show, and paints it on your screen - one vertical line at a time, creating a 3D world from 2D pictures!
