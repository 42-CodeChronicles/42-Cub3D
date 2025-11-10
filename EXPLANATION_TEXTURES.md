# 🎨 TEXTURES EXPLAINED (For 10 Year Olds!)

## What is a Texture?

Imagine you're playing with stickers! A **texture** is like a sticker that you put on walls in your game to make them look pretty instead of just plain colors.

---

## 📁 Files About Textures

### 1. **texture.c** - The Main Texture Painter

Think of this file like a painter who colors your screen!

#### What it does:
```
When you look at a wall in the game, this code:
1. Picks the right sticker (texture) for that wall
2. Colors the ceiling (like the sky)
3. Colors the wall (with the sticker)
4. Colors the floor (like the ground)
```

#### The Main Functions:

**`init_tex_data()`** - Gets Ready to Paint
- Picks which sticker to use (North wall? South wall? Door?)
- Figures out where on the sticker to look
- Picks colors for ceiling and floor

**Example:**
```
You're standing in front of a wall.
This function says: "This is the NORTH wall, so I'll use the NORTH sticker!"
```

**`draw_ceiling()`** - Paints the Top Part
- Colors all the pixels from top of screen to where the wall starts
- Makes it one solid color (like blue for sky)

**`draw_wall()`** - Puts the Sticker on the Wall
- Goes down the wall pixel by pixel
- For each pixel, it looks at the texture and picks the right color
- It's like tracing a picture!

**`draw_floor()`** - Paints the Bottom Part
- Colors all the pixels from where the wall ends to the bottom
- Makes it one solid color (like brown for ground)

**`draw_wall_slice_texture()`** - The Boss Function
- Calls all the other functions in order:
  1. Paint ceiling ☁️
  2. Paint wall 🧱
  3. Paint floor 🟫

---

### 2. **texture_helper.c** - The Helper Functions

These are like little assistants that help the painter!

#### The Functions:

**`get_texture()`** - Picks the Right Sticker
```
Questions it asks:
- Is this a door? → Use door sticker
- Are you looking North? → Use North wall sticker
- Are you looking South? → Use South wall sticker
- Are you looking East? → Use East wall sticker
- Are you looking West? → Use West wall sticker
```

**Example:**
```
You turn to face North.
This function says: "Oh! You're looking North! Here's the North wall sticker!"
```

**`get_door_state()`** - Checks Door Information
- Looks through all the doors in the map
- Finds the door at position (x, y)
- Returns information about that door

**`get_texture_color()`** - Gets One Pixel Color
- A texture is made of thousands of tiny colored squares (pixels)
- This function picks ONE pixel from the texture
- Returns what color that pixel is

**How it works:**
```
Texture is like a grid:
  Column 0  Column 1  Column 2
Row 0:  🔴       🟢       🔵
Row 1:  🟡       🟣       🟠
Row 2:  ⚫       ⚪       🟤

If you ask for (Column 1, Row 1) → You get 🟣 (purple)
```

---

## 🎯 Real Example - How Textures Work Together

### Scenario: You're Walking in the Game

**Step 1:** Game asks: "What do I see in front of me?"

**Step 2:** `get_texture()` says: "You're looking at a NORTH wall! Here's the brick texture!"

**Step 3:** For each vertical line on your screen:
   - `draw_ceiling()` paints sky color at the top
   - `draw_wall()` puts the brick texture in the middle
     - For EACH pixel, it asks `get_texture_color()`: "What color should this pixel be?"
     - `get_texture_color()` looks at the brick picture and says: "This pixel should be RED!"
   - `draw_floor()` paints ground color at the bottom

**Result:** You see a brick wall with sky above and ground below! 🏰

---

## 📝 Important Variables

### In `t_tex_data` (Texture Data):
```c
texture          // The sticker image to use
tex_x            // Which column of the sticker to look at
ceiling_color    // What color is the ceiling? (like blue sky)
floor_color      // What color is the floor? (like brown dirt)
```

### Colors are stored as numbers:
```
Red   = 255,   0,   0  → Bright red
Green =   0, 255,   0  → Bright green
Blue  =   0,   0, 255  → Bright blue
```

---

## 🎮 Where Are the Texture Images?

Your texture images are PNG files, probably like:
- `north_wall.png` - For North walls
- `south_wall.png` - For South walls
- `east_wall.png` - For East walls
- `west_wall.png` - For West walls
- `door.png` - For doors

These get loaded when the game starts!

---

## 🌟 Summary in Simple Words

**Textures are pictures that make your game walls look cool!**

Instead of boring colored walls, you can have:
- 🧱 Brick walls
- 🪨 Stone walls
- 🪵 Wood walls
- 🚪 Cool doors

The texture code is like a painter who:
1. Picks the right picture (texture)
2. Looks at each tiny dot (pixel) in the picture
3. Colors your screen to match that picture
4. Also adds ceiling and floor colors

That's it! Now walls look AWESOME instead of boring! 🎨✨
