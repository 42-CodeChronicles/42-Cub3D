# Flame Weapon/Punch Animation

## What Changed

Your flame sprite is now rendered as a **first-person weapon/punch** (like classic FPS games such as DOOM, Wolfenstein, etc.)

### Before vs After

#### BEFORE (World Sprite):
```
┌─────────────────────────────┐
│         3D View             │
│                             │
│     [Wall]  🔥  [Wall]     │  ← Flame was in the 3D world
│                             │     at position (5.5, 5.5)
│                             │
└─────────────────────────────┘
```

#### AFTER (HUD Weapon):
```
┌─────────────────────────────┐
│         3D View             │
│                             │
│     [Wall]     [Wall]       │
│                             │
│           🔥🔥🔥            │  ← Flame punch is at bottom-center
│          🔥🔥🔥🔥           │     like holding a weapon
└─────────────────────────────┘
     (Always visible at bottom)
```

## Technical Details

### Sprite Positioning
- **Size**: 60% of screen height
- **Position**: Bottom-center of screen
- **Behavior**: Always visible, follows player (like holding a weapon)

### Animation
- **Frames**: 41 flame animation frames (00.png to 40.png)
- **Speed**: ~30 FPS (0.033 seconds per frame)
- **Loop Time**: ~1.37 seconds for full animation cycle

### Rendering Order
1. Draw 3D walls
2. Draw weapon sprite on top (HUD layer)

## Customization Options

You can adjust the weapon appearance by modifying these values in `sprite_render.c`:

```c
int weapon_height = SCREEN_HEIGHT * 0.6;  // Change 0.6 to make it bigger/smaller
                                           // 0.5 = 50%, 0.7 = 70%, etc.

int start_x = (SCREEN_WIDTH - weapon_width) / 2;  // Center position
int start_y = SCREEN_HEIGHT - weapon_height;      // Bottom position
```

### Position Examples:

**Bottom-Right Corner:**
```c
int start_x = SCREEN_WIDTH - weapon_width;
int start_y = SCREEN_HEIGHT - weapon_height;
```

**Bottom-Left Corner:**
```c
int start_x = 0;
int start_y = SCREEN_HEIGHT - weapon_height;
```

**Lower Position (more screen visible):**
```c
int start_y = SCREEN_HEIGHT - (weapon_height * 0.8);  // Only show 80% of sprite
```

## Test Your Changes

Run the game and you should see the flame animation at the bottom of your screen, animating continuously like a punch/weapon!

```bash
./cub3D maps/map3.cub
```
