# 🎬 ANIMATED SPRITES - Simple Explanation for Everyone!

## What is a Sprite?

A sprite is like a character or object in your game that's NOT part of the walls! Think of it like a sticker that you can put anywhere in your game world:
- A monster
- A treasure chest
- A torch
- A plant
- Anything that stands in the world!

An **ANIMATED** sprite is even cooler - it's like a flip book! It changes pictures really fast to look like it's moving or alive!

---

## 📂 Files that Handle Sprites

### 1. **cub3D.h** - The Sprite Recipe

```c
typedef struct s_sprite
{
	double			x;              // Where is sprite? (left-right)
	double			y;              // Where is sprite? (up-down)
	mlx_texture_t	**frames;       // All the pictures for animation
	int				frame_count;    // How many pictures do we have?
	int				current_frame;  // Which picture are we showing now?
	double			frame_time;     // How long to show each picture
	double			last_update;    // When did we last change the picture?
}	t_sprite;
```

**Simple Explanation:**

- `x, y` = Where the sprite is standing in the game world
- `frames` = Like a flip book - all the pictures of the sprite
- `frame_count` = How many pictures in our flip book (example: 8 pictures)
- `current_frame` = Which picture page are we on right now? (picture 1, 2, 3...)
- `frame_time` = How fast to flip pages (0.033 seconds = 30 pictures per second!)
- `last_update` = When did we last flip to a new picture?

**Real-Life Example:**
Think of a flip book you draw:
- You draw a stick figure in 10 different positions (frame_count = 10)
- You're currently showing picture #3 (current_frame = 3)
- You flip to a new picture every 0.5 seconds (frame_time = 0.5)
- You last flipped to a new picture 0.2 seconds ago (last_update)

---

## 🎨 The Sprite Files Explained

### 2. **sprite_init.c** - Creating Sprites

#### Function: `init_sprite_fields()` - Set Up Basic Info

```c
static void	init_sprite_fields(t_sprite *sprite, double x, double y, int count)
{
	sprite->x = x;                  // Position left-right
	sprite->y = y;                  // Position up-down
	sprite->frame_count = count;    // How many pictures
	sprite->current_frame = 0;      // Start with first picture
	sprite->frame_time = 0.033;     // Change picture every 0.033 seconds
	sprite->last_update = 0;        // Haven't updated yet
}
```

**Simple Example:**
Creating a torch sprite at position (5.5, 3.2) with 4 flame pictures:
```
x = 5.5
y = 3.2
frame_count = 4 pictures
current_frame = 0 (start with picture #1)
frame_time = 0.033 seconds
```

---

#### Function: `load_sprite_frames()` - Load All Pictures

```c
static int	load_sprite_frames(t_sprite *sprite, char **frame_path, int count)
{
	int	i;

	i = 0;
	while (i < count)  // Load each picture
	{
		sprite->frames[i] = mlx_load_png(frame_path[i]);
		
		if (!sprite->frames[i])  // Couldn't load this picture!
		{
			printf("Warning: Can't load sprite frame '%s', skipping sprite\n",
				frame_path[i]);
			
			// Delete the pictures we already loaded
			while (--i >= 0)
				mlx_delete_texture(sprite->frames[i]);
			return (0);  // Failed!
		}
		i++;
	}
	return (1);  // Success!
}
```

**Simple Explanation:**
Like gathering photos for a photo album:
1. Try to open photo #1
2. Try to open photo #2
3. Try to open photo #3
4. If any photo is missing or damaged, throw away the whole album!

**Example with a Monster:**
```c
char *monster_pictures[3] = {
	"monster/frame1.png",  // Monster with mouth closed
	"monster/frame2.png",  // Monster with mouth half open
	"monster/frame3.png"   // Monster with mouth wide open!
};
```

---

#### Function: `created_sprite()` - Make a Complete Sprite

```c
t_sprite	*created_sprite(double x, double y, char **frame_path, int count)
{
	t_sprite	*sprite;

	// Make space in memory for the sprite
	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	
	// Set up basic information
	init_sprite_fields(sprite, x, y, count);
	
	// Make space for all the pictures
	sprite->frames = malloc(sizeof(mlx_texture_t *) * count);
	if (!sprite->frames)
	{
		free(sprite);
		return (NULL);
	}
	
	// Load all the pictures
	if (!load_sprite_frames(sprite, frame_path, count))
	{
		free(sprite->frames);
		free(sprite);
		return (NULL);
	}
	
	return (sprite);  // All done! Here's your sprite!
}
```

**Step-by-Step Example:**

Creating a dancing bear sprite:

```c
// Step 1: Get pictures of dancing bear
char *bear_dance[4] = {
	"bear/dance1.png",  // Left paw up
	"bear/dance2.png",  // Both paws down
	"bear/dance3.png",  // Right paw up
	"bear/dance4.png"   // Both paws down
};

// Step 2: Create the sprite at position (10, 15)
t_sprite *bear = created_sprite(10.0, 15.0, bear_dance, 4);

// Now the bear will dance! (flip through all 4 pictures)
```

---

#### Function: `sprite_init()` - Initialize Sprite System

```c
void	sprite_init(t_config *data)
{
	data->sprite_count = 0;    // No sprites yet
	data->sprites = NULL;      // No sprite list yet
}
```

**Simple Explanation:**
This is like saying: "We're starting fresh. No sprites in the game yet!"

---

### 3. **sprite_animation.c** - Making Sprites Move!

#### Function: `update_sprite_frame()` - Change to Next Picture

```c
void	update_sprite_frame(t_sprite *sprite, double current_time)
{
	// Has enough time passed to show the next picture?
	if (current_time - sprite->last_update >= sprite->frame_time)
	{
		sprite->current_frame++;  // Go to next picture
		
		// If we've shown all pictures, start over from first picture
		if (sprite->current_frame >= sprite->frame_count)
			sprite->current_frame = 0;
		
		sprite->last_update = current_time;  // Remember when we changed
	}
}
```

**Simple Example:**

Imagine a fire animation with 3 pictures:

```
Time 0.000s: Show picture 0 (small flame)
Time 0.033s: Show picture 1 (medium flame)
Time 0.066s: Show picture 2 (big flame)
Time 0.099s: Show picture 0 (small flame again - loop!)
Time 0.132s: Show picture 1 (medium flame)
...and so on forever!
```

**Visual Example:**
```
Frame 0:    Frame 1:    Frame 2:    Frame 0 (repeat):
   🔥          🔥🔥         🔥🔥🔥         🔥
```

---

#### Function: `update_all_sprites()` - Update Every Sprite

```c
void	update_all_sprites(t_config *data, double current_time)
{
	int	i;

	i = 0;
	while (i < data->sprite_count)  // Go through each sprite
	{
		update_sprite_frame(&data->sprites[i], current_time);
		i++;
	}
}
```

**Simple Explanation:**
If you have 5 animated sprites in your game:
1. Update torch animation
2. Update monster animation
3. Update treasure chest animation
4. Update plant animation
5. Update flag animation

Each one flips to its next picture if enough time has passed!

---

### 4. **sprite_render.c** - Drawing Sprites on Screen

#### Helper Structure:

```c
typedef struct s_sprite_params
{
	double	dx;                 // Distance left-right from player
	double	dy;                 // Distance up-down from player
	double	distance;           // Total distance from player
	double	angle_to_sprite;    // What angle to look at sprite
	double	sprite_angle;       // Angle relative to where player is looking
	int		screen_x;           // Where to draw on screen (left-right)
	double	sprite_height;      // How tall to draw sprite
	double	sprite_width;       // How wide to draw sprite
	int		start_y;            // Where to start drawing (top)
	int		start_x;            // Where to start drawing (left)
	int		end_x;              // Where to stop drawing (right)
}	t_sprite_params;
```

---

#### Function: `get_sprite_distance()` - How Far Away?

```c
double	get_sprite_distance(t_config *data, t_sprite *sprite)
{
	double	dx;
	double	dy;

	// How far left/right?
	dx = sprite->x - (data->map.player_pos.x / TILE_SIZE);
	
	// How far up/down?
	dy = sprite->y - (data->map.player_pos.y / TILE_SIZE);
	
	// Use Pythagoras: distance = √(dx² + dy²)
	return (sqrt(dx * dx + dy * dy));
}
```

**Simple Example:**
You are at position (3, 4), sprite is at (6, 8)

```
dx = 6 - 3 = 3 (3 units to the right)
dy = 8 - 4 = 4 (4 units up)

distance = √(3² + 4²)
         = √(9 + 16)
         = √25
         = 5 units away!
```

**Visual:**
```
      Sprite (6,8)
          *
          |
          |4
          |
You (3,4) +-----
            3
```

---

#### Function: `init_sprite_params()` - Calculate Sprite Position

```c
static void	init_sprite_params(t_sprite_params *p, t_config *data,
		t_sprite *sprite)
{
	// Calculate distance from player
	p->dx = sprite->x - (data->map.player_pos.x / TILE_SIZE);
	p->dy = sprite->y - (data->map.player_pos.y / TILE_SIZE);
	p->distance = sqrt(p->dx * p->dx + p->dy * p->dy);
	
	// Calculate angle to sprite
	p->angle_to_sprite = atan2(p->dy, p->dx);
	
	// Calculate angle relative to where player is looking
	p->sprite_angle = p->angle_to_sprite - data->map.player_pos.angle;
	
	// Normalize angle to be between -π and π
	while (p->sprite_angle > M_PI)
		p->sprite_angle -= 2 * M_PI;
	while (p->sprite_angle < -M_PI)
		p->sprite_angle += 2 * M_PI;
}
```

**Simple Example:**

Imagine you're looking straight ahead (north):
- Sprite directly in front: angle = 0° (you see it!)
- Sprite to your right: angle = 90° (turn right to see it)
- Sprite behind you: angle = 180° (can't see it)
- Sprite to your left: angle = -90° (turn left to see it)

---

#### Function: `calc_screen_pos()` - Where to Draw Sprite

```c
static int	calc_screen_pos(t_sprite_params *p, mlx_texture_t *texture)
{
	double	fov_rad;

	// Too close or too far? Don't draw it!
	if (p->distance < 0.5 || p->distance > 20.0)
		return (0);
	
	// Calculate field of view
	fov_rad = (FOV * M_PI / 180.0) / 2.0;
	
	// Is sprite outside our view? Don't draw it!
	if (fabs(p->sprite_angle) > fov_rad + 0.3)
		return (0);
	
	// Calculate where on screen to draw (left-right position)
	p->screen_x = (int)((SCREEN_WIDTH / 2) * (1.0 + tan(p->sprite_angle)
				/ tan(fov_rad)));
	
	// Calculate how big to draw the sprite
	p->sprite_height = (SCREEN_HEIGHT / p->distance) * 0.8;
	p->sprite_width = (texture->width * p->sprite_height) / texture->height;
	
	// Calculate where to start drawing
	p->start_y = (SCREEN_HEIGHT - p->sprite_height) / 2;
	p->start_x = p->screen_x - (p->sprite_width / 2);
	p->end_x = p->start_x + p->sprite_width;
	
	return (1);  // Yes, we should draw this sprite!
}
```

**Simple Explanation:**

This function answers three questions:

1. **Can I see it?**
   - Too close or too far? No!
   - Outside my field of view? No!
   - Otherwise: Yes!

2. **Where on screen?**
   - Center of screen if directly in front
   - Left side if sprite is to my left
   - Right side if sprite is to my right

3. **How big?**
   - Far away = Small
   - Close up = BIG!

**Visual Example:**
```
Your Screen:
+------------------+
|                  |
|    small 🎃      |  <- Far away
|                  |
|      🎃          |  <- Medium distance
|                  |
|        🎃🎃      |  <- Close up!
|        🎃🎃      |
+------------------+
```

---

#### Function: `draw_sprite_column()` - Draw One Vertical Line

```c
static void	draw_sprite_column(mlx_image_t *img, t_sprite_params *p,
		mlx_texture_t *tex, int x)
{
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	if (x >= 0 && x < SCREEN_WIDTH)  // Is this on screen?
	{
		y = p->start_y;
		while (y < p->start_y + p->sprite_height)  // Draw each pixel
		{
			if (y >= 0 && y < SCREEN_HEIGHT)
			{
				// Find which part of sprite picture to use
				tex_x = ((x - p->start_x) * tex->width) / p->sprite_width;
				tex_y = ((y - p->start_y) * tex->height) / p->sprite_height;
				
				// Get the color from the sprite picture
				if (tex_x >= 0 && tex_x < (int)tex->width && tex_y >= 0
					&& tex_y < (int)tex->height)
				{
					color = get_texture_color(tex, tex_x, tex_y);
					
					// Only draw if pixel is not transparent
					if ((color & 0xFF) > 0)
						mlx_put_pixel(img, x, y, color);
				}
			}
			y++;
		}
	}
}
```

**Simple Explanation:**

Like painting a vertical stripe of the sprite:
1. Find which column of the sprite picture to use
2. For each pixel going down:
   - Find the matching row in the sprite picture
   - Get that color
   - If it's not transparent (invisible), paint it!

---

#### Function: `draw_sprite()` - Complete Drawing

```c
void	draw_sprite(mlx_image_t *img, t_config *data, t_sprite *sprite)
{
	t_sprite_params	p;
	mlx_texture_t	*texture;
	int				x;

	// Get the current animation frame
	texture = sprite->frames[sprite->current_frame];
	
	// Calculate where and how big to draw
	init_sprite_params(&p, data, sprite);
	if (!calc_screen_pos(&p, texture))
		return ;  // Can't see sprite, don't draw
	
	// Draw the sprite column by column
	x = p.start_x;
	while (x < p.end_x)
	{
		draw_sprite_column(img, &p, texture, x);
		x++;
	}
}
```

**Step-by-Step:**
1. Get the right animation picture (current frame)
2. Figure out where sprite is and if we can see it
3. Draw it column by column from left to right

---

## 🎮 How Everything Works Together

### Complete Animation Example:

```c
// STEP 1: CREATE A SPRITE
char *torch_frames[4] = {
	"torch/flame1.png",  // Flame flickers
	"torch/flame2.png",
	"torch/flame3.png",
	"torch/flame4.png"
};
t_sprite *torch = created_sprite(5.5, 8.2, torch_frames, 4);

// STEP 2: GAME LOOP (repeats every frame)
while (game_running)
{
	// Update animation (change to next picture if time is up)
	double current_time = get_current_time();
	update_sprite_frame(torch, current_time);
	
	// Draw the sprite
	draw_sprite(screen, game_data, torch);
}
```

### What You See:

```
Time 0.00s: 🔥    (frame 0 - small flame)
Time 0.03s: 🔥🔥   (frame 1 - bigger)
Time 0.06s: 🔥🔥🔥  (frame 2 - even bigger)
Time 0.09s: 🔥    (frame 3 - back to small)
Time 0.12s: 🔥🔥   (frame 0 again - loop!)
```

---

## 🎨 Real-Life Comparison

### Flip Book:
1. **Draw multiple pictures** (create sprite frames)
2. **Number each page** (frame 0, 1, 2, 3...)
3. **Flip through pages quickly** (update_sprite_frame)
4. **When you reach the end, start over** (loop animation)

### Your Game:
1. **Load sprite pictures** (load_sprite_frames)
2. **Track which picture to show** (current_frame)
3. **Change pictures over time** (update_sprite_frame)
4. **Draw current picture on screen** (draw_sprite)
5. **Repeat forever!** (animation loops)

---

## 🔑 Important Terms

- **Sprite:** An object in the game (not a wall)
- **Frame:** One picture in the animation
- **frame_count:** Total number of pictures
- **current_frame:** Which picture we're showing now
- **frame_time:** How long to show each picture (in seconds)
- **Animation:** Changing pictures quickly to create movement
- **Loop:** When animation reaches the end, start over from the beginning

---

## 🌟 Summary

Animated sprites bring your game to life! Here's how:

1. **Create:** Make a sprite with multiple pictures (frames)
2. **Animate:** Flip through pictures like a flip book
3. **Calculate:** Figure out where sprite is and how to draw it
4. **Draw:** Put the current picture on the screen
5. **Repeat:** Do this every frame to create smooth animation!

Think of it like a cartoon on TV - it's just lots of pictures shown really fast to make things look like they're moving! 🎬✨

Your game does this automatically, creating living, breathing objects in the world!
