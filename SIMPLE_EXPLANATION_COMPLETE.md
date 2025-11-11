# 🎮 HOW IT ALL WORKS TOGETHER - Complete Guide!

This file shows you how TEXTURES, DOORS, and SPRITES all work together to create your awesome 3D game!

---

## 🌟 The Big Picture

Imagine you're making a haunted house game:

1. **TEXTURES** = The walls, floor, and ceiling (make the house)
2. **DOORS** = Ways to move between rooms (can open and close)
3. **SPRITES** = Ghosts, candles, treasure (things inside the house)

Let's see how they all work together!

---

## 📖 Story Example: Walking Through Your Game

### Scene: You're in a Spooky Hallway

```
+------------------+------------------+
|  [Brick Wall]    |  [Stone Wall]   |  <- TEXTURES on walls
|                  D                  |  <- D = DOOR
|      👻          |         🕯️      |  <- SPRITES (ghost & candle)
|      You         |                  |
|       ↑          |                  |
+------------------+------------------+
   [Wood Floor]                          <- TEXTURE on floor
```

Let's see what happens when the game draws this scene!

---

## 🎬 Frame-by-Frame: What the Computer Does

### Frame 1: Drawing Everything (happens 60 times per second!)

#### Step 1: TEXTURES - Draw the Room

```c
// Code from 3d.c and texture.c

// For each vertical line on your screen (0 to 1280):
for (x = 0; x < SCREEN_WIDTH; x++)
{
    // 1. Shoot a ray to see what it hits
    ray_angle = calculate_ray_angle(x);
    distance = cast_ray(data, ray_angle);
    
    // 2. Did we hit a wall or door?
    if (hit_wall)
    {
        // Get the right texture (north wall? south wall? door?)
        texture = get_texture(data, map_y, map_x);
        
        // 3. Draw ceiling (top part)
        draw_ceiling(img, x, ceiling_color);
        
        // 4. Draw wall with texture
        draw_wall_with_texture(img, x, texture);
        
        // 5. Draw floor (bottom part)
        draw_floor(img, x, floor_color);
    }
}
```

**What you see after Step 1:**
```
+------------------+
| ☁️ ☁️ ☁️ ☁️ ☁️   |  <- Ceiling (colored)
| 🧱🧱🧱🧱🧱🧱🧱🧱  |  <- Brick wall texture
| 🧱🧱🧱🧱🧱🧱🧱🧱  |
| 🟫🟫🟫🟫🟫🟫🟫🟫  |  <- Wood floor texture
+------------------+
```

---

#### Step 2: DOORS - Open/Close Animation

```c
// Code from doors.c

// Check if there's a door where the ray hit
if (map[y][x] == 'D')
{
    // Find this specific door
    door = get_door_state(data, x, y);
    
    // If player pressed space, start opening!
    if (player_pressed_space)
    {
        door->is_open = 1;
        door->open_amount = 0.0;  // Start closed
    }
    
    // Animate the door opening
    if (door->is_open)
    {
        door->open_amount += 0.05;  // Open a little bit each frame
        if (door->open_amount >= 1.0)
        {
            door->open_amount = 1.0;  // Fully open!
        }
    }
    
    // Shift the texture based on how open the door is
    wall_x += door->open_amount;
    
    // Draw the door with shifted texture
    draw_wall_with_texture(img, x, door_texture);
}
```

**Animation Over Time:**
```
Frame 1:  🚪 (closed - open_amount = 0.0)
Frame 2:  🚪| (opening - open_amount = 0.2)
Frame 5:  🚪  | (halfway - open_amount = 0.5)
Frame 10: 🚪    | (almost - open_amount = 0.8)
Frame 15: 🚪      | (open! - open_amount = 1.0)
```

---

#### Step 3: SPRITES - Draw Animated Objects

```c
// Code from sprite_render.c and sprite_animation.c

// Update all sprite animations
current_time = get_current_time();
for (i = 0; i < sprite_count; i++)
{
    // Change to next animation frame if enough time passed
    if (current_time - sprite->last_update >= 0.033)  // 30 FPS
    {
        sprite->current_frame++;
        if (sprite->current_frame >= sprite->frame_count)
            sprite->current_frame = 0;  // Loop back to start
        sprite->last_update = current_time;
    }
}

// Draw each sprite
for (i = 0; i < sprite_count; i++)
{
    // Calculate where sprite is
    distance = get_sprite_distance(data, sprite);
    angle = get_angle_to_sprite(data, sprite);
    
    // Can we see it?
    if (sprite_is_visible(angle, distance))
    {
        // Calculate screen position
        screen_x = convert_angle_to_screen_x(angle);
        height = calculate_sprite_height(distance);
        
        // Get current animation frame
        texture = sprite->frames[sprite->current_frame];
        
        // Draw sprite on screen
        draw_sprite(img, texture, screen_x, height);
    }
}
```

**What you see (ghost animating):**
```
Frame 1:  👻  (frame 0 - normal)
Frame 2:  😱  (frame 1 - scary face)
Frame 3:  👻  (frame 2 - normal again)
Frame 4:  😱  (frame 3 - scary face)
(Repeats forever!)
```

---

## 🎯 Complete Example: Walking Through a Door

### Situation: You're in a room with a ghost and want to go through the door!

#### Phase 1: Before Opening Door

```
Your View:
+------------------------+
|     [Ceiling]          |
|                        |
|   🧱🧱🚪🧱🧱   👻      |  <- Brick walls, closed door, ghost
|                        |
|     [Floor]            |
+------------------------+

What's happening in code:
- Textures: Drawing brick walls, door, floor, ceiling
- Door: is_open = 0, open_amount = 0.0 (closed)
- Sprite (ghost): Animating through frames, visible
```

#### Phase 2: You Press Space to Open Door

```c
// In your key handler
if (key == SPACE && door_in_front)
{
    door->is_open = 1;  // Start opening!
}
```

#### Phase 3: Door Opening (20 frames, 0.33 seconds)

```
Frame 1 (open_amount = 0.05):
+------------------------+
|   🧱🧱🚪|🧱🧱   👻      |  <- Door starting to slide
+------------------------+

Frame 5 (open_amount = 0.25):
+------------------------+
|   🧱🧱🚪  |🧱🧱   👻    |  <- Door quarter open
+------------------------+

Frame 10 (open_amount = 0.50):
+------------------------+
|   🧱🧱🚪    |🧱🧱   👻  |  <- Door halfway open
+------------------------+

Frame 20 (open_amount = 1.00):
+------------------------+
|   🧱🧱      |🧱🧱   👻  |  <- Door fully open! You can walk through!
+------------------------+

Meanwhile, the ghost is STILL animating its scary faces! 😱👻😱
```

#### Phase 4: Walking Through

```c
// Player can now move through because door is open
if (door->open_amount >= 0.8)  // Almost fully open
{
    player_can_walk_through = true;
}
```

---

## 🔄 The Game Loop - Every Single Frame!

This happens 60 times per second:

```c
void game_loop(t_config *data)
{
    while (game_is_running)
    {
        // 1. HANDLE INPUT
        if (key_pressed == SPACE)
            try_to_open_door(data);
        if (key_pressed == W)
            move_player_forward(data);
        
        // 2. UPDATE ANIMATIONS
        current_time = get_current_time();
        
        // Update all sprite animations
        update_all_sprites(data, current_time);
        
        // Update door opening/closing
        update_all_doors(data, current_time);
        
        // Update weapon animation if shooting
        update_weapon_frame(&data->weapon, current_time);
        
        // 3. CLEAR SCREEN
        clear_image(data->view_3d);
        
        // 4. DRAW EVERYTHING
        
        // Draw 3D view (walls with textures, doors)
        render_3d_view(data->view_3d, data);
        
        // Draw sprites on top of walls
        for (i = 0; i < data->sprite_count; i++)
            draw_sprite(data->view_3d, data, &data->sprites[i]);
        
        // Draw weapon on top of everything
        draw_weapon(data->view_3d, data);
        
        // Draw minimap
        draw_minimap(data->minimap_image, data);
        
        // 5. SHOW ON SCREEN
        // (MLX42 handles this automatically)
    }
}
```

---

## 📊 Render Order (What Gets Drawn First)

This is VERY important! Things drawn later appear on top:

```
Layer 1: CEILING (background color)
   ↓
Layer 2: WALLS (with textures)
   ↓
Layer 3: DOORS (special walls that can open)
   ↓
Layer 4: FLOOR (background color)
   ↓
Layer 5: SPRITES (sorted by distance - far ones first)
   ↓
Layer 6: WEAPON (always in front)
   ↓
Layer 7: UI (minimap, crosshair)
```

**Why this order?**
- Walls are the foundation
- Sprites appear in front of walls (ghost floats in the room)
- Weapon is always visible (in your hand)
- UI is always on top (so you can see it)

---

## 🎨 Visual Example: Complete Frame

```
+----------------------------------------+
|          🌙    [Score: 100]          |  <- UI Layer
|                                       |
|                                       |
|    🧱🧱🧱    🚪|    🧱🧱🧱            |  <- Walls & Door
|         \      |      /               |
|          \     |     /                |
|           \    |    /                 |
|         👻  \  |  /  🕯️               |  <- Sprites
|              \ | /                    |
|               \|/                     |
|                                       |
|           🔫                          |  <- Weapon
|       🟫🟫🟫🟫🟫🟫🟫🟫               |  <- Floor
|                                       |
| [Minimap] ⬜⬜⬜                      |  <- Minimap UI
| [Minimap] ⬜●⬜                      |  <- You (●)
| [Minimap] ⬜⬜⬜                      |
+----------------------------------------+
```

**What's happening:**
1. Ceiling drawn (top part)
2. Walls drawn with brick texture
3. Door drawn (slightly open)
4. Floor drawn (bottom part)
5. Ghost sprite drawn (animating)
6. Candle sprite drawn (flickering)
7. Weapon drawn (in front)
8. Minimap drawn (corner)

---

## 🔧 How They Connect: Code Flow

### When a Ray Hits Something:

```c
// In rays.c
double distance = cast_ray(data, angle, &hit_vertical, &wall_x, &map_x, &map_y);

// What did we hit?
char tile = data->map.array_map[map_y][map_x];

if (tile == '1')
{
    // It's a wall! Get wall texture
    texture = get_texture(data, map_y, map_x);  // texture_helper.c
    draw_wall_slice_texture(img, params);       // texture.c
}
else if (tile == 'D')
{
    // It's a door! Get door state
    door = get_door_state(data, map_x, map_y);  // texture_helper.c
    
    // Adjust texture based on how open it is
    wall_x += door->open_amount;
    
    // Draw with door texture
    texture = data->door_texture;
    draw_wall_slice_texture(img, params);       // texture.c
}

// After all walls, draw sprites
for (each sprite)
{
    if (sprite_visible)
    {
        draw_sprite(img, data, sprite);         // sprite_render.c
    }
}
```

---

## 🎯 Memory & Performance

### What the Computer Remembers:

```c
t_config data = {
    // TEXTURES
    .no_texture = [Image: brick.png],
    .so_texture = [Image: stone.png],
    .ea_texture = [Image: wood.png],
    .we_texture = [Image: metal.png],
    .door_texture = [Image: door.png],
    
    // DOORS (array of all doors in game)
    .doors = [
        { x: 5, y: 3, is_open: 1, open_amount: 0.7 },
        { x: 8, y: 7, is_open: 0, open_amount: 0.0 },
    ],
    .door_count = 2,
    
    // SPRITES (array of all sprites in game)
    .sprites = [
        { x: 4.5, y: 6.2, frames: [ghost1, ghost2], current_frame: 0 },
        { x: 7.8, y: 3.1, frames: [candle1, candle2, candle3], current_frame: 1 },
    ],
    .sprite_count = 2,
    
    // PLAYER
    .player_pos = { x: 256, y: 384, angle: 1.57 },
    
    // IMAGES
    .view_3d = [1280x720 pixels],
    .minimap = [544x544 pixels],
};
```

---

## 🎓 Learning Summary

### For TEXTURES:
- **What:** Pictures on walls, floor, ceiling
- **When:** Drawn first (background)
- **How:** Ray hits wall → Get texture → Draw vertical slice

### For DOORS:
- **What:** Special walls that open
- **When:** Drawn with walls (same time)
- **How:** Texture slides based on open_amount (0.0 to 1.0)

### For SPRITES:
- **What:** Objects in the world (not walls)
- **When:** Drawn after walls (on top)
- **How:** Calculate position → Draw if visible → Animate frames

### All Together:
1. Draw background (ceiling/floor)
2. Draw walls with textures
3. Draw doors (using door texture + animation)
4. Draw sprites (sorted by distance)
5. Draw weapon
6. Draw UI
7. Repeat 60 times per second!

---

## 🌟 Final Example: Complete Scene

```
You're standing in a dungeon looking at a treasure room!

Walls: Stone texture (TEXTURES)
Door: Slowly opening (DOORS - open_amount increasing)
Torch: Flickering animation (SPRITES - changing frames)
Treasure: Glowing animation (SPRITES - changing frames)
Your Sword: Ready in your hand (WEAPON)

Every frame (1/60th of a second):
1. ✅ Draw stone walls with texture
2. ✅ Draw opening door (shifting texture)
3. ✅ Update torch animation (next flame frame)
4. ✅ Update treasure animation (next glow frame)
5. ✅ Draw torch sprite
6. ✅ Draw treasure sprite
7. ✅ Draw your sword
8. ✅ Show everything on screen!

Result: A living, breathing 3D world! 🏰✨
```

---

## 🎮 You Did It!

Now you understand how your game creates a 3D world using:
- **TEXTURES** for walls
- **DOORS** that open and close
- **SPRITES** that animate and move

They all work together like a team to make an awesome game! 🎉

Keep exploring and have fun coding! 👨‍💻👩‍💻
