# 🔫 WEAPON ANIMATION EXPLAINED (For 10 Year Olds!)

## What is a Weapon in the Game?

A **weapon** is what you see at the bottom-right of your screen! It's like your character is holding a gun or sword, and when you shoot/attack, it animates (moves)!

Think of it like this:
```
Your screen:
┌─────────────────────────────┐
│         GAME VIEW           │
│                             │
│                             │
│                             │
│                        🔫   │ ← Your weapon here!
└─────────────────────────────┘
```

---

## 🎬 How Weapon Animation Works

Just like sprites, weapons use the **flipbook technique**!

When you press the shoot button:
```
Frame 0: 🔫      (ready)
Frame 1: 🔫💥    (shooting - bullet comes out!)
Frame 2: 🔫      (recoil - gun moves back)
Frame 3: 🔫      (returning)
Frame 4: 🔫      (almost back)
Frame 5: 🔫      (ready again)

Show these fast → Looks like shooting animation!
```

---

## 📁 Files About Weapon

### 1. **weapon.c** - Main Weapon Code
### 2. **weapon_helper.c** - Helper Functions

---

## 🎯 Functions in weapon.c

### **`init_weapon_fields()`** - Sets Up Basic Weapon Info

**What it does:**
Fills in the weapon's starting information.

**Information:**
```c
frame_count = 6         // Weapon has 6 animation pictures
current_frame = 0       // Start at picture 0 (ready position)
is_shooting = 0         // Not shooting right now (0 = No)
frame_time = 0.05       // Show each frame for 0.05 seconds
last_update = 0         // Last time we changed frames
```

**Example:**
```
Your pistol starts:
  - Ready position (frame 0)
  - Not shooting
  - Has 6 frames total for the shooting animation
```

---

### **`load_weapon_frames()`** - Loads All Weapon Pictures

**What it does:**
Loads all 6 pictures of the weapon animation from files.

**Files it loads:**
```
weapon/0.png → Frame 0 (ready)
weapon/1.png → Frame 1 (start shooting)
weapon/2.png → Frame 2 (bang!)
weapon/3.png → Frame 3 (recoil)
weapon/4.png → Frame 4 (recovering)
weapon/5.png → Frame 5 (back to ready)
```

**How it works:**
```
For each of the 6 frames:
  Try to load the PNG file
  Success? → Great! Save it!
  Failed? → ERROR! Can't continue!
```

**Example:**
```
Loading weapon animation...
  0.png ✅ Ready position loaded!
  1.png ✅ Shooting frame 1 loaded!
  2.png ✅ Shooting frame 2 loaded!
  3.png ✅ Recoil loaded!
  4.png ✅ Recovery loaded!
  5.png ✅ Final frame loaded!
Weapon ready to use! 🔫
```

---

### **`weapon_init()`** - The Boss Function That Sets Up Weapon

**What it does:**
Completely sets up the weapon when the game starts.

**Steps:**

1. **Create list of frame files**
   ```
   "I need these 6 pictures: 0.png, 1.png, 2.png, ..."
   ```

2. **Initialize weapon fields**
   ```
   "Set frame count to 6, current frame to 0, not shooting"
   ```

3. **Make space for frames**
   ```
   "I need memory to hold 6 pictures"
   ```

4. **Load all frames**
   ```
   "Load all 6 pictures from the weapon folder"
   ```

5. **Done!**
   ```
   "Weapon is ready! You can shoot now!"
   ```

---

### **`draw_weapon_pixel()`** - Draws One Pixel of the Weapon

**What it does:**
Draws ONE tiny colored dot (pixel) of the weapon on screen.

**For each pixel:**
1. Figure out which pixel from the weapon image to use
2. Get that pixel's color
3. If it's transparent → Skip it! (don't draw)
4. If it has color → Put it on screen!

**Why skip transparent pixels?**
```
Without transparency:
┌────────┐
│ 🔫     │ ← Draws a rectangle with the gun
└────────┘

With transparency:
   🔫      ← Draws only the gun, you can see the game behind it!
```

---

### **`draw_weapon()`** - The Boss Function That Draws the Whole Weapon

**What it does:**
Draws the complete weapon on your screen!

**Steps:**

1. **Get current frame**
   ```
   "We're on frame 3 of the shooting animation"
   ```

2. **Calculate weapon size**
   ```
   "Make it 40% of the original image size"
   ```

3. **Calculate weapon position**
   ```
   "Put it at bottom-right corner of screen"
   ```

4. **Draw every pixel**
   ```
   For each row (y):
     For each column (x):
       Draw that pixel (if not transparent)
   ```

**Visual:**
```
Screen (simplified):
    X=0                    X=1280
Y=0  ┌──────────────────────────┐
     │ GAME  VIEW  HERE         │
     │                          │
Y=720│                      🔫  │ ← Weapon here!
     └──────────────────────────┘

Weapon position: Bottom-right, with some padding
```

---

## 🎯 Functions in weapon_helper.c

### **`get_weapon_dimensions()`** - Calculates Weapon Size

**What it does:**
Figures out how big the weapon should be on screen.

**Formula:**
```
weapon_width = original_width × 0.4   (40% of original)
weapon_height = original_height × 0.4  (40% of original)
```

**Example:**
```
Original weapon image:
  Width: 500 pixels
  Height: 400 pixels

On screen:
  Width: 500 × 0.4 = 200 pixels
  Height: 400 × 0.4 = 160 pixels

So the weapon looks smaller and fits nicely on screen!
```

---

### **`get_weapon_position()`** - Figures Out Where to Put the Weapon

**What it does:**
Calculates the X and Y position for the weapon on screen.

**Formula:**
```
start_x = SCREEN_WIDTH - weapon_width - 50
        = 1280 - 200 - 50
        = 1030 pixels from left

start_y = SCREEN_HEIGHT - weapon_height - 20
        = 720 - 160 - 20
        = 540 pixels from top
```

**What this means:**
```
Screen is 1280 × 720

Weapon starts at:
  X = 1030 (near the right edge)
  Y = 540  (near the bottom)

Result: Weapon appears at BOTTOM-RIGHT! ✅
```

---

### **`update_weapon_frame()`** - Updates the Animation Frame

**What it does:**
Decides when to show the next frame of the shooting animation.

**Two situations:**

**Situation 1: Not Shooting**
```
is_shooting = 0
→ Keep showing frame 0 (ready position)
→ Don't animate
```

**Situation 2: Shooting!**
```
is_shooting = 1
→ Check if enough time passed (0.05 seconds)
→ YES? Move to next frame!
→ At last frame (frame 5)? Go back to frame 0 and stop shooting!
```

**Animation Cycle:**
```
Press Shoot Button!
→ is_shooting = 1

Time 0.00s: Frame 0 🔫
Time 0.05s: Frame 1 🔫💥
Time 0.10s: Frame 2 🔫
Time 0.15s: Frame 3 🔫
Time 0.20s: Frame 4 🔫
Time 0.25s: Frame 5 🔫
Time 0.30s: Frame 0 🔫 → is_shooting = 0 (back to ready!)

Animation complete! Ready to shoot again!
```

---

## 🎮 Complete Example - Shooting Your Weapon!

### When Game Starts:

**Initialization:**
```
1. Load 6 weapon frames from PNG files
2. Set current_frame = 0 (ready position)
3. Set is_shooting = 0 (not shooting)
4. Draw weapon at bottom-right of screen
```

**Screen shows:**
```
┌────────────────────────┐
│  GAME VIEW             │
│                        │
│                   🔫   │ ← Frame 0 (ready)
└────────────────────────┘
```

---

### You Press Shoot Button:

**What happens:**
```
1. Game sets: is_shooting = 1
2. Animation starts!
```

**Frame by frame (every 0.05 seconds):**

```
Time 0.00s:
  current_frame = 0 🔫
  "Ready position"

Time 0.05s:
  current_frame = 1 🔫💥
  "BANG! Bullet fires!"

Time 0.10s:
  current_frame = 2 🔫
  "Recoil - gun kicks back!"

Time 0.15s:
  current_frame = 3 🔫
  "Gun moving back to position"

Time 0.20s:
  current_frame = 4 🔫
  "Almost ready..."

Time 0.25s:
  current_frame = 5 🔫
  "Back to ready!"

Time 0.30s:
  current_frame = 0 🔫
  is_shooting = 0
  "Ready to shoot again!"
```

---

## 📝 Important Data Structure

### `t_weapon` - All Information About the Weapon

```c
struct t_weapon {
    mlx_texture_t **frames;  // Array of 6 pictures
    int frame_count;         // Always 6 for this weapon
    int current_frame;       // Which frame now? (0-5)
    int is_shooting;         // Are we shooting? (0=No, 1=Yes)
    double frame_time;       // Time per frame (0.05 seconds)
    double last_update;      // When we last changed frames
}
```

**Think of it like:**
```
📋 Weapon Info Card:
   Pictures: 6 frames loaded
   Current Picture: Frame 0 (ready)
   Status: Not shooting
   Animation Speed: Change frame every 0.05 seconds
   Last Change: 0.25 seconds ago
```

---

## 🎨 How the Weapon Looks Different From Sprites

### Sprites (Enemies, Objects):
- Move around in the 3D world
- Can be far or close
- Size changes based on distance
- Can be hidden behind walls

### Weapon:
- Always stays at bottom-right
- Always same size
- Always visible (drawn on top of everything!)
- Attached to your view

**Think of it like:**
```
Sprites = Things IN the world (like actors on a stage)
Weapon = Part of the camera (like a sticker on your phone screen)
```

---

## 🌟 Summary in Simple Words

**The weapon is your character's gun/tool shown on screen!**

The weapon code:

1. 📸 **Loads** 6 pictures showing the shooting animation
2. 📍 **Positions** weapon at bottom-right corner
3. 📏 **Sizes** weapon to 40% of original (so it fits nicely)
4. 🎬 **Animates** when you shoot:
   - Shows frames 0→1→2→3→4→5→0
   - Takes about 0.3 seconds total
5. 🎨 **Draws** on top of everything else (always visible!)

**Why is this cool?**
- Makes shooting feel real! 💥
- Gives visual feedback when you shoot
- Looks professional and polished
- Makes the game more fun! 🎮

It's like having a real gun in your hands in the game! Bang bang! 🔫✨
